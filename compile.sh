#!/bin/bash

showhelp(){
   echo ""
   echo "Usage: $0 -f file [-a optionally show assembly output]"
   echo -e "\t-a show assembly of compiled code"
   echo -e "\t-f relative path to file to compile"
   echo -e "\t--help show help"
   exit 1 # Exit script after printing help
}

if [ "$1" == "--help" ];
then
    showhelp
    exit 1
fi

show_assembly="false"

while getopts ":af:" opt
do
   case "$opt" in
      a ) show_assembly="true" ;;
      f ) xfile="$OPTARG" ;;
      ? ) showhelp ;; # Print helpFunction in case parameter is non-existent
   esac
done

# Check compiler
compiler="gcc"

if [ `which $compiler` == "" ];
then
    echo "Cannot find C compiler '$compiler' -- exiting"
    exit 1
fi

# Clean the targets and inject the macro to the build invocation
if [ $show_assembly == "true" ];
then
    ./clean.sh
fi

# Build
build_dir_name="bin"
#debug="debug"
if [ ! -d "$build_dir_name" ];
then
    if [ "$show_assembly" == "true" ];
    then
        ./build.sh assembly
    else
        ./build.sh
    fi
fi

# Run
main_target="ccbf_comp"
mainexe=$(find ./$build_dir_name -name $main_target)

if [ -z "$mainexe" ];
then
    echo "Cannot find main bf compiler executable -- exiting"
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
