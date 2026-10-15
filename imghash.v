module main

import image
import image.color
import image.jpeg
import image.png
import os

// image_exts are the file extensions scanned in similar-image mode.
const image_exts = ['.png', '.jpg', '.jpeg']

// SimilarGroup is one set of visually similar images.
struct SimilarGroup {
	hash  u64
	files []string
	maxd  int
}

// is_image_file reports whether path looks like a supported image.
fn is_image_file(path string) bool {
	lower := path.to_lower()
	for ext in image_exts {
		if lower.ends_with(ext) {
			return true
		}
	}
	return false
}

// decode_image decodes path with the pure-V PNG/JPEG decoders.
fn decode_image(path string) !image.Image {
	mut f := os.open(path)!
	defer {
		f.close()
	}
	if path.to_lower().ends_with('.png') {
		return png.decode(f)
	}
	return jpeg.decode(f)
}

// gray_of returns the Rec.601 luma of c in 0..65535.
fn gray_of(c color.Color) u64 {
	r, g, b, _ := c.rgba()
	return (u64(299) * r + u64(587) * g + u64(114) * b) / 1000
}

// dhash computes the 64-bit difference hash of img: shrink to a 9x8
// luma grid, set one bit per cell where the left pixel is brighter
// than its right neighbour.
fn dhash(img image.Image) u64 {
	b := img.bounds()
	iw := b.max.x - b.min.x
	ih := b.max.y - b.min.y
	if iw < 2 || ih < 1 {
		return 0
	}
	mut grid := [72]u64{}
	for y in 0 .. 8 {
		for x in 0 .. 9 {
			px := b.min.x + x * (iw - 1) / 8
			py := b.min.y + y * (ih - 1) / 7
			grid[y * 9 + x] = gray_of(img.at(px, py))
		}
	}
	mut h := u64(0)
	for y in 0 .. 8 {
		for x in 0 .. 8 {
			if grid[y * 9 + x] > grid[y * 9 + x + 1] {
				h |= u64(1) << u64(y * 8 + x)
			}
		}
	}
	return h
}

// dhash_file decodes path and returns its difference hash.
fn dhash_file(path string) !u64 {
	img := decode_image(path)!
	return dhash(img)
}

// hamming returns the bit distance between two hashes.
fn hamming(a u64, b u64) int {
	mut x := a ^ b
	mut n := 0
	for x != 0 {
		n += int(x & 1)
		x >>= 1
	}
	return n
}

// find_similar_images groups visually similar images under dirs.
// Hashes within threshold bits of a group's first member join it.
// Undecodable files are skipped, never fatal.
fn find_similar_images(dirs []string, threshold int) ![]SimilarGroup {
	files := walk_files(dirs)!
	mut hashes := map[string]u64{}
	for f in files {
		if !is_image_file(f.path) {
			continue
		}
		hashes[f.path] = dhash_file(f.path) or {
			eprintln('dupfind: skipping undecodable image ${f.path}')
			continue
		}
	}
	mut groups := []SimilarGroup{}
	mut assigned := map[string]bool{}
	mut paths := hashes.keys()
	paths.sort()
	for path in paths {
		if path in assigned {
			continue
		}
		mut members := [path]
		mut maxd := 0
		assigned[path] = true
		for other in paths {
			if other in assigned {
				continue
			}
			d := hamming(hashes[path], hashes[other])
			if d <= threshold {
				members << other
				assigned[other] = true
				if d > maxd {
					maxd = d
				}
			}
		}
		if members.len > 1 {
			groups << SimilarGroup{hashes[path], members, maxd}
		}
	}
	return groups
}

// print_similar writes similar-image groups in human-readable form.
fn print_similar(groups []SimilarGroup, threshold int) {
	if groups.len == 0 {
		println('no similar images found')
		return
	}
	for g in groups {
		println('dhash ${g.hash:x} (<=${threshold} bits, worst ${g.maxd})')
		for f in g.files {
			println('    ${f}')
		}
	}
	println('${groups.len} group(s) within ${threshold} bits')
}
