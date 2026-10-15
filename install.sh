#!/bin/sh
# Installs dupfind to ~/.local/bin from the latest GitHub release.
# Usage: sh install.sh
set -e

BIN_DIR="${HOME}/.local/bin"
URL='https://github.com/gabytz777/dupfind/releases/latest/download/dupfind-linux-x64'

mkdir -p "${BIN_DIR}"

if command -v curl >/dev/null 2>&1; then
	curl -sL "${URL}" -o "${BIN_DIR}/dupfind"
elif command -v wget >/dev/null 2>&1; then
	wget -q "${URL}" -O "${BIN_DIR}/dupfind"
else
	echo 'install: need curl or wget' >&2
	exit 1
fi

chmod +x "${BIN_DIR}/dupfind"
"${BIN_DIR}/dupfind" --version

case ":${PATH}:" in
	*":${BIN_DIR}:"*) ;;
	*)
		echo "install: ${BIN_DIR} is not on your PATH." >&2
		echo "install: add this line to ~/.bashrc and restart your terminal:" >&2
		echo "install:   export PATH=\"\$HOME/.local/bin:\$PATH\"" >&2
		;;
esac
echo 'install: done. Try: dupfind --preview ~/Pictures'
