#!/bin/bash

passed=0
failed=0
failed_arr=()

tests=$(find ./test/scripts -type f)

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
