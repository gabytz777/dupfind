module main

import image
import image.color
import image.jpeg
import image.png
import os

// make_gradient builds a w x h test image. tweak shifts brightness.
fn make_gradient(w int, h int, tweak int) image.RGBA {
	mut img := image.new_rgba(image.Rectangle{image.Point{0, 0}, image.Point{w, h}})
	for y in 0 .. h {
		for x in 0 .. w {
			v := u8((x * 255 / w + y * 255 / h + tweak) / 2)
			img.set(x, y, color.RGBA{v, u8(255 - v), 128, 255})
		}
	}
	return img
}

// make_image_tree writes gw-identical, modified, different and corrupt
// images for tests. Returns the dir.
fn make_image_tree() !string {
	dir := os.join_path(os.temp_dir(), 'dupfind_img_test')
	os.rmdir_all(dir) or {}
	os.mkdir_all(dir)!
	a := make_gradient(64, 64, 0)
	os.write_file_array('${dir}/a.png', png.encode_to_bytes(a)!)!
	os.write_file_array('${dir}/a_copy.png', png.encode_to_bytes(a)!)!
	os.write_file_array('${dir}/a.jpg', jpeg.encode_to_bytes(a, jpeg.Options{ quality: 90 })!)!
	mut c := make_gradient(64, 64, 0)
	for y in 0 .. 16 {
		for x in 0 .. 16 {
			c.set(x, y, color.RGBA{0, 0, 0, 255})
		}
	}
	os.write_file_array('${dir}/c.png', png.encode_to_bytes(c)!)!
	d := make_gradient(64, 64, 200)
	os.write_file_array('${dir}/d.png', png.encode_to_bytes(d)!)!
	os.write_file('${dir}/bogus.png', 'not a png')!
	return dir
}

fn test_hamming_counts_bits() {
	assert hamming(0, 0) == 0
	assert hamming(0xFF, 0x00) == 8
	assert hamming(u64(0xFFFF_FFFF_FFFF_FFFF), 0) == 64
	assert hamming(0b1010, 0b0101) == 4
}

fn test_dhash_identical_images_match() {
	dir := make_image_tree()!
	assert dhash_file('${dir}/a.png')! == dhash_file('${dir}/a_copy.png')!
}

fn test_similar_images_threshold_zero_is_exact() {
	dir := make_image_tree()!
	groups := find_similar_images([dir], 0)!
	assert groups.len == 1
	assert groups[0].files.len == 3 // a.png, a_copy.png, a.jpg
}

fn test_similar_images_skips_corrupt_and_loners() {
	dir := make_image_tree()!
	// threshold 2 must not pull in c.png (6 bits away) or d.png
	groups := find_similar_images([dir], 2)!
	for g in groups {
		for f in g.files {
			assert !f.ends_with('c.png')
			assert !f.ends_with('d.png')
			assert !f.ends_with('bogus.png')
		}
	}
}

fn test_is_image_file_matches_extensions() {
	assert is_image_file('a.png')
	assert is_image_file('A.JPG')
	assert is_image_file('x.jpeg')
	assert !is_image_file('a.txt')
	assert !is_image_file('png')
}
