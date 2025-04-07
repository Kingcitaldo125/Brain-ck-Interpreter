#!/bin/bash

image_name="bfck_interpreter"
image_tag="latest"
build_dir_name="bin"

./clean.sh
docker build -t ${image_name}:${image_tag} --network host .
