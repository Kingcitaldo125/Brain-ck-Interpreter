#!/bin/bash

build_dir_name="bin"
./build.sh

pushd . &>/dev/null
cd $build_dir_name
make install
popd &>/dev/null
