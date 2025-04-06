#!/bin/bash

debug_opt="$1"

# Build
build_dir_name="bin"
if [ "$debug_opt" == "clean" ];
then
    echo "cleaning..."
    ./clean.sh
fi

if [ "$debug_opt" == "debug" ];
then
    cmake -S . -B $build_dir_name/ -DDEBUG=true
else
    cmake -S . -B $build_dir_name/
fi

cmake --build $build_dir_name/ --parallel $(nproc)
