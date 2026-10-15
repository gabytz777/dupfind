module main

import json2
import os

// version is printed by --version.
const version = '0.1.1'

fn main() {
	mut dirs := []string{}
	mut as_json := false
	mut preview_n := 0
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
		} else if arg == '--version' {
			println('dupfind ${version}')
			return
		} else if arg.starts_with('--') {
			eprintln('dupfind: unknown flag ${arg}')
			exit(1)
		} else {
			dirs << arg
		}
	}
	if dirs.len == 0 {
		eprintln('usage: dupfind [--json] [--preview[=N]] [--version] <dir> [dir...]')
		exit(1)
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
