#!/bin/bash

main_target="main"

if [ ! -d ./build ];
then
    ./build.sh
fi

mainexe=$(find ./build -name $main_target)
./$mainexe
