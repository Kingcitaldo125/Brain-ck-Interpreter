#!/bin/bash

opt="$1"

CMAKE_TOOLCHAIN_FILE="$CMAKE_TOOLCHAIN_FILE"

# Build
build_dir_name="bin"
if [ "$opt" == "clean" ];
then
    echo "cleaning..."
    ./clean.sh
fi

if [ "$opt" == "debug" ];
then
    cmake -S . -B $build_dir_name/ -DDEBUG=true
elif [ "$opt" == "test" ];
then
    if [ -z "$CMAKE_TOOLCHAIN_FILE" ];
    then
        echo "Cannot recognize toolchain file -- trying without it"
        cmake -S . -B $build_dir_name/ -DBUILD_TEST=true
    else
        echo "Using toolchain file '$CMAKE_TOOLCHAIN_FILE'"
        cmake -S . -B $build_dir_name/ -DBUILD_TEST=true -DCMAKE_TOOLCHAIN_FILE=$CMAKE_TOOLCHAIN_FILE
    fi
elif [ "$opt" == "assembly" ];
then
    cmake -S . -B $build_dir_name/ -DSHOW_ASM=true
else
    cmake -S . -B $build_dir_name/
fi

cmake --build $build_dir_name/ --parallel $(nproc)
