TAB="$(printf '\t')"

exec "$1" 'format=@b @a' delim="${TAB}" <<EOF
Peach${TAB}3${TAB}1
Mango${TAB}4${TAB}2
EOF
