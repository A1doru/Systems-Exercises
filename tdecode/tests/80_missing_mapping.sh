echo -e '\x80hello\n\x80\n\x81 \x80 \x81' | "$1" > /dev/null 2>&1
echo "$?"
