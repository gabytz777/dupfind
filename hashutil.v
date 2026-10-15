module main

import hash.fnv1a
import os

// hash_chunk_size is the streaming read size for hash_file.
const hash_chunk_size = 64 * 1024

// hash_file streams the file at path through FNV-1a and returns the
// hex digest. Pure V, constant memory regardless of file size.
fn hash_file(path string) !string {
	mut h := fnv1a.new_fnv1a64()
	mut f := os.open(path)!
	defer {
		f.close()
	}
	mut buf := []u8{len: hash_chunk_size}
	for {
		// os.File.read returns Eof (not 0) at end of file.
		n := f.read(mut buf) or {
			if err is os.Eof {
				break
			}
			return err
		}
		if n == 0 {
			break
		}
		h.write(buf[..n])!
	}
	return '${h.finish():x}'
}
