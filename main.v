module main

import json2
import os

// version is printed by --version.
const version = '0.3.0'

// default_bin_dir is where a bare run installs the binary.
fn default_bin_dir() !string {
	home := os.user_home_dir()!
	return os.join_path(home, '.local', 'bin')
}

// install_self copies the running binary to dest_dir/dupfind and marks
// it executable. Returns the installed path.
fn install_self(dest_dir string) !string {
	exe := os.executable()
	dest := os.join_path(dest_dir, 'dupfind')
	if exe == dest {
		return error('already installed at ${dest}')
	}
	os.mkdir_all(dest_dir)!
	os.cp(exe, dest)!
	os.chmod(dest, 0o755)!
	return dest
}

// print_usage writes the help text to stderr.
fn print_usage() {
	eprintln('usage: dupfind [--json] [--preview[=N]] [--similar-images[=bits]] [--version] [--help] <dir> [dir...]')
}

fn main() {
	// A bare run (double-clicking the download) installs instead of
	// erroring: copy this binary to ~/.local/bin/dupfind. An installed
	// copy run bare shows usage instead.
	if os.args.len == 1 {
		bin_dir := default_bin_dir() or {
			eprintln('dupfind: ${err.msg()}')
			exit(1)
		}
		if os.executable() == os.join_path(bin_dir, 'dupfind') {
			print_usage()
			exit(1)
		}
		dest := install_self(bin_dir) or {
			eprintln('dupfind: ${err.msg()}')
			exit(1)
		}
		println('dupfind: installed to ${dest}')
		if bin_dir !in os.getenv('PATH').split(':') {
			println('dupfind: ${bin_dir} is not on your PATH.')
			println('dupfind: add this line to ~/.bashrc and restart your terminal:')
			println('dupfind:   export PATH="\$HOME/.local/bin:\$PATH"')
		}
		println('dupfind: try: dupfind --preview ~/Pictures')
		return
	}
	mut dirs := []string{}
	mut as_json := false
	mut preview_n := 0
	mut similar := -1
	for arg in os.args[1..] {
		if arg == '--json' {
			as_json = true
		} else if arg == '--preview' {
			preview_n = 5
		} else if arg.starts_with('--preview=') {
			preview_n = arg.all_after('=').int()
			if preview_n < 1 {
				eprintln('dupfind: --preview needs a positive line count')
				exit(1)
			}
		} else if arg == '--similar-images' {
			similar = 5
		} else if arg.starts_with('--similar-images=') {
			similar = arg.all_after('=').int()
			if similar < 0 {
				eprintln('dupfind: --similar-images needs a non-negative bit threshold')
				exit(1)
			}
		} else if arg == '--version' {
			println('dupfind ${version}')
			return
		} else if arg == '--help' || arg == '-h' {
			print_usage()
			return
		} else if arg.starts_with('--') {
			eprintln('dupfind: unknown flag ${arg}')
			exit(1)
		} else {
			dirs << arg
		}
	}
	if dirs.len == 0 {
		print_usage()
		exit(1)
	}
	if similar >= 0 {
		if as_json {
			eprintln('dupfind: --json is not supported with --similar-images yet')
			exit(1)
		}
		groups := find_similar_images(dirs, similar) or {
			eprintln('dupfind: ${err.msg()}')
			exit(1)
		}
		print_similar(groups, similar)
		return
	}
	groups := find_dupes(dirs) or {
		eprintln('dupfind: ${err.msg()}')
		exit(1)
	}
	if as_json {
		println(json2.encode(groups, escape_unicode: true, time_as_unix: true))
	} else {
		print_groups(groups, preview_n)
	}
}
