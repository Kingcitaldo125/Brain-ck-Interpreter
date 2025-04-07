#!/bin/bash

showhelp(){
   echo ""
   echo "Usage: $0 [-f file]"
   echo -e "\t-f relative path to file to interpret"
   echo -e "\t--help show help"
   exit 1 # Exit script after printing help
}

if [ "$1" == "--help" ];
then
    showhelp
    exit 1
fi

while getopts ":f:" opt
do
   case "$opt" in
      f ) xfile="$OPTARG" ;;
      ? ) showhelp ;; # Print helpFunction in case parameter is non-existent
   esac
done

# Build
build_dir_name="bin"
#debug="debug"
if [ ! -d "$build_dir_name" ];
then
    if [ ! -z "$debug" == "debug" ];
    then
        ./build.sh debug
    else
        ./build.sh
    fi
fi

# Run
main_target="ccbf"
mainexe=$(find ./$build_dir_name -name $main_target)

if [ -z "$mainexe" ];
then
    echo "Cannot find main interpreter executable -- exiting"
    exit 1
fi

if [ ! -z "$xfile" ];
then
    ./$mainexe $xfile
    exit $?
else
    ./$mainexe
    exit $?
fi
