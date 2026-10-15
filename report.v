module main

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

// print_groups writes groups in human-readable form.
fn print_groups(groups []DupeGroup) {
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
		wasted += g.size * u64(g.files.len - 1)
	}
	println('${groups.len} group(s), ${wasted} bytes recoverable')
}
