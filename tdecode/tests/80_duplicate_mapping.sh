echo -e '\x80hello\x80world\n\x80 \x80 \x80' | "$1" >/dev/null 2>&1
echo "$?"
