#!/bin/bash

debug_opt="$1"

# Build
build_dir_name="bin"
if [ ! -d "$build_dir_name" ];
then
    if [ "$debug_opt" == "debug" ];
    then
        ./build.sh debug
    else
        ./build.sh
    fi
fi

# Run
main_target="ccbf"
mainexe=$(find ./$build_dir_name -name $main_target)
./$mainexe
