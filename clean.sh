#!/bin/bash

build_dir_name="bin"
rm -rf $build_dir_name

# Clean compiled binaries
if [ -f "out" ];
then
    rm out.c &>/dev/null
    rm out.s &>/dev/null
    rm out &>/dev/null
fi
