module main

import json2
import os

fn main() {
	mut dirs := []string{}
	mut as_json := false
	for arg in os.args[1..] {
		if arg == '--json' {
			as_json = true
		} else if arg.starts_with('--') {
			eprintln('dupfind: unknown flag ${arg}')
			exit(1)
		} else {
			dirs << arg
		}
	}
	if dirs.len == 0 {
		eprintln('usage: dupfind [--json] <dir> [dir...]')
		exit(1)
	}
	groups := find_dupes(dirs) or {
		eprintln('dupfind: ${err.msg()}')
		exit(1)
	}
	if as_json {
		println(json2.encode(groups, escape_unicode: true, time_as_unix: true))
	} else {
		print_groups(groups)
	}
}
