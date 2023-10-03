#!/bin/sh
set -ex

raylib_lib="../raylib/src/libraylib.a"
raylib_include="../raylib/src"
CFLAGS="-Wall -Werror"

EMSDK_PATH=/home/cmte/r/emsdk
EMSCRIPTEN_PATH=$EMSDK_PATH/upstream/emscripten
CLANG_PATH=$EMSDK_PATH/upstream/bin
PYTHON_PATH=/usr/bin
NODE_PATH=$EMSDK_PATH/node/12.9.1_64bit/bin
PATH=`printenv PATH`:$EMSDK_PATH:$EMSCRIPTEN_PATH:$CLANG_PATH:$NODE_PATH:$PYTHON_PATH


emcc -MJ a.o.json -o game.html main.c -Os $CFLAGS $raylib_lib -I. -I$raylib_include -s USE_GLFW=3 --preload-file resources -s TOTAL_MEMORY=67108864 -s ALLOW_MEMORY_GROWTH=1 -s FORCE_FILESYSTEM=1 -s ASSERTIONS=1 --profiling --shell-file=shell.html -DPLATFORM_WEB

sed -e '1s/^/[\n/' -e '$s/,$/\n]/' *.o.json > compile_commands.json
