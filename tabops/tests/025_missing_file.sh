"$1" format='@a -> @b' delim== notexisting

EXIT_CODE="$?"
if test "$EXIT_CODE" -eq '1'; then
    exit 0
else
    exit "$EXIT_CODE"
fi
