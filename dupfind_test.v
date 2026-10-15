module main

import os

// make_tree creates dir with the given name->content files for tests.
fn make_tree(files map[string]string) !string {
	dir := os.join_path(os.temp_dir(), 'dupfind_test')
	os.rmdir_all(dir) or {}
	os.mkdir_all(dir)!
	for name, content in files {
		full := os.join_path(dir, name)
		os.mkdir_all(os.dir(full))!
		os.write_file(full, content)!
	}
	return dir
}

fn test_find_dupes_groups_identical_files() ! {
	dir := make_tree({
		'a.txt':     'same'
		'b.txt':     'same'
		'sub/c.txt': 'same'
		'other.txt': 'different!'
	})!
	groups := find_dupes([dir])!
	assert groups.len == 1
	assert groups[0].files.len == 3
	assert groups[0].size == 4
}

fn test_find_dupes_ignores_unique_files() ! {
	dir := make_tree({
		'a.txt': 'one'
		'b.txt': 'two'
	})!
	groups := find_dupes([dir])!
	assert groups.len == 0
}

fn test_find_dupes_same_size_different_content() ! {
	// same size must not imply duplicate: content hash decides.
	dir := make_tree({
		'a.txt': 'abc'
		'b.txt': 'xyz'
	})!
	groups := find_dupes([dir])!
	assert groups.len == 0
}

fn test_find_dupes_empty_files() ! {
	dir := make_tree({
		'a.txt': ''
		'b.txt': ''
		'c.txt': 'x'
	})!
	groups := find_dupes([dir])!
	assert groups.len == 1
	assert groups[0].files.len == 2
	assert groups[0].size == 0
}

fn test_find_dupes_missing_dir_is_an_error() {
	if _ := find_dupes(['/nope_xyz_123']) {
		assert false, 'missing dir must error'
	}
}
