#!/bin/bash

# Build
./build.sh

# Run
main_target="main"
mainexe=$(find ./build -name $main_target)
./$mainexe
