#!/bin/sh
set -ex

raylib_lib="../raylib/src/libraylib.a"
raylib_include="../raylib/src"
CFLAGS="-Wall -Werror"

PYTHON_PATH=/usr/bin


clang -MJ a.o.json -o game main.c -Os $CFLAGS $raylib_lib -I. -I$raylib_include -DPLATFORM_DESKTOP -lm

sed -e '1s/^/[\n/' -e '$s/,$/\n]/' *.o.json > compile_commands.json
