#!/bin/bash

cli_passed=0
cli_failed=0
failed_arr=()

tests=$(find ./test/scripts -type f)

echo "Running CLI tests..."
for tst in $tests
do
    echo "Running '$tst'..."
    ./run.sh -f $tst
    echo "Done."
    echo ""
    res=`echo $?`
    if [ $res -ne 0 ];
    then
        failed=$(( $failed + 1 ))
        failed_arr+=("$tst")
    else
        passed=$(( $passed + 1 ))
    fi
done

ctest_file=$(find -name CTestTestfile.cmake)
unit_passed=0
unit_failed=0

# Only run unit tests if a test file is present
# This should be made by cmake automatically
# The 'BUILD_TEST' option should be 'true' for this to exist
if [ ! -z "$ctest_file" ];
then
    echo "Running unit tests..."
    cd `dirname $ctest_file` && ctest -V
fi

passed=$(( cli_passed + unit_passed ))
failed=$(( cli_failed + unit_failed ))

echo "$passed tests passed"
echo "$failed tests failed"

if [ $failed -ge 1 ];
then
    echo "Failed Tests:"
    for tst in $failed_arr
    do
        echo "$tst"
    done
fi
