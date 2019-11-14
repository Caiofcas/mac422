#!/bin/sh
set -e

ORIG_DIR=$(pwd)

cd /usr/local/src
make memorymap
mv memorymap ../bin
cd $ORIG_DIR