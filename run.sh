#!/bin/bash

debug_opt="$1"

# Build
build_dir_name="bin"
if [ "$debug_opt" == "debug" ];
then
    ./build.sh debug
else
    ./build.sh
fi

# Run
main_target="main"
mainexe=$(find ./$build_dir_name -name $main_target)
./$mainexe
