# dupfind

Find duplicate files by content. Pure V, zero dependencies.

## How it works

1. Walk the given directories and group files by size (cheap pre-filter —
   files with a unique size are never read).
2. Stream-hash same-size candidates with FNV-1a in constant memory.
3. Report groups of byte-identical files, sorted by size.

## Install

One command (Linux x64, needs `curl` or `wget`):

```sh
curl -sL https://raw.githubusercontent.com/gabytz777/dupfind/master/install.sh | sh
```

This downloads the latest release binary to `~/.local/bin/dupfind`. If that
directory is not on your `PATH`, the installer tells you the line to add
to `~/.bashrc`.

## Build

```sh
v -o dupfind .
```

Needs a [V](https://vlang.io) toolchain, nothing else.

## Usage

```sh
dupfind <dir> [dir...]               # human-readable report
dupfind --preview [dir...]           # also show first 5 lines of each group
dupfind --preview=2 [dir...]         # also show first 2 lines of each group
dupfind --json <dir>...              # JSON array of {size, hash, files}
dupfind --similar-images [dir...]    # group visually similar images (<=5 bits)
dupfind --similar-images=10 [dir...] # ...with a looser bit threshold
dupfind --version
```

`--similar-images` decodes PNG/JPEG with the pure-V stdlib decoders,
hashes each image to 64 bits (difference hash over a 9x8 luma grid),
and groups images within the threshold Hamming distance — so a
re-encoded or slightly edited copy still matches, where byte hashing
would miss it. Undecodable files are reported and skipped.

Example:

```
$ dupfind ~/photos
4823040 bytes  9f2c11aa04d77e1
    /home/gab/photos/img_01.png
    /home/gab/photos/backup/img_01_copy.png
1 group(s), 4823040 bytes recoverable
```

Exit codes: `0` on success (even with no duplicates), `1` on bad flags,
missing directories, or unreadable files.

## Tests

```sh
v test .
```

## License

MIT
