echo -e '\x80hello.\n\x80\n\x80' | "$1" > /dev/null 2>&1
echo "$?"
