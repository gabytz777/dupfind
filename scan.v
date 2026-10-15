module main

import os

// ScannedFile is one regular file found during a directory walk.
struct ScannedFile {
	path string
	size u64
}

// walk_files collects every regular file under dirs. Unreadable entries
// below the top level are skipped, never fatal; a missing top-level dir
// is an error.
fn walk_files(dirs []string) ![]ScannedFile {
	mut out := []ScannedFile{}
	for dir in dirs {
		if !os.exists(dir) {
			return error('no such directory: ${dir}')
		}
		walk_dir(dir, mut out)
	}
	return out
}

// walk_dir appends the regular files under dir (recursively) to out.
fn walk_dir(dir string, mut out []ScannedFile) {
	entries := os.ls(dir) or { return }
	for entry in entries {
		full := os.join_path(dir, entry)
		if os.is_dir(full) {
			if os.is_link(full) {
				continue
			}
			walk_dir(full, mut out)
		} else if os.is_file(full) {
			size := u64(os.file_size(full))
			out << ScannedFile{full, size}
		}
	}
}

// group_by_size buckets files by byte size. Only buckets with 2+ files
// can contain duplicates.
fn group_by_size(files []ScannedFile) map[u64][]ScannedFile {
	mut groups := map[u64][]ScannedFile{}
	for f in files {
		groups[f.size] << f
	}
	return groups
}
