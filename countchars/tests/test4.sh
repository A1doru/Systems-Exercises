#!/bin/sh
exec "$1" abc <<EOF
some good charachters here.
only some!
EOF
