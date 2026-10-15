module main

import os

// DupeGroup is one set of files with identical content.
pub struct DupeGroup {
pub:
	size  u64
	hash  string
	files []string
}

// find_dupes returns every duplicate group found under dirs.
fn find_dupes(dirs []string) ![]DupeGroup {
	files := walk_files(dirs)!
	size_groups := group_by_size(files)
	mut dupes := []DupeGroup{}
	for size, bucket in size_groups {
		if bucket.len < 2 {
			continue
		}
		mut by_hash := map[string][]string{}
		for f in bucket {
			digest := hash_file(f.path)!
			by_hash[digest] << f.path
		}
		for hash, paths in by_hash {
			if paths.len < 2 {
				continue
			}
			mut sorted := paths.clone()
			sorted.sort()
			dupes << DupeGroup{size, hash, sorted}
		}
	}
	dupes.sort(a.size > b.size)
	return dupes
}

// print_groups writes groups in human-readable form. When preview_n > 0,
// the first preview_n lines of each group's content are shown under it.
fn print_groups(groups []DupeGroup, preview_n int) {
	if groups.len == 0 {
		println('no duplicates found')
		return
	}
	mut wasted := u64(0)
	for g in groups {
		println('${g.size} bytes  ${g.hash}')
		for f in g.files {
			println('    ${f}')
		}
		if preview_n > 0 && g.files.len > 0 {
			for line in preview_lines(g.files[0], preview_n) {
				println('    | ${line}')
			}
		}
		wasted += g.size * u64(g.files.len - 1)
	}
	println('${groups.len} group(s), ${wasted} bytes recoverable')
}

// preview_lines returns up to n displayable lines from the head of path.
fn preview_lines(path string, n int) []string {
	content := os.read_file(path) or { return ['<unreadable>'] }
	if content.len == 0 {
		return ['<empty file>']
	}
	if u8(0) in content.bytes() {
		return ['<binary file, preview skipped>']
	}
	mut out := []string{}
	for line in content.split_into_lines() {
		if out.len >= n {
			break
		}
		out << truncate_runes(line, 120)
	}
	return out
}

// truncate_runes shortens s to max runes without splitting UTF-8.
fn truncate_runes(s string, max int) string {
	runes := s.runes()
	if runes.len <= max {
		return s
	}
	return runes[..max].string() + '…'
}
