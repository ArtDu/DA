#!/usr/bin/env bash

# *.sh <count of tests> <count of V> <count of Edges>

fail=false



if [[ $# -ne 3 ]]	; then
    echo "ERROR: Failed in args."
    exit 1
fi

mkdir -p tests
if ! python3 test_gen.py $1 $2 $3 ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

for test_file in `ls tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"
    if ! python3 ../nlogn.py < ${test_file} > "${answer_file}.my" ; then
       echo "ERROR"
       continue
    fi

    if ! python3 correct_algo.py < ${test_file} > "${answer_file}.a" ; then
       echo "ERROR"
       continue
    fi

    if ! diff "${answer_file}.a"  "${answer_file}.my" > /dev/null ; then
        echo "Failed"
        fail=true
        test=${answer_file}
    else
        echo "OK"
    fi
done


if $fail ; then
    printf "\n"
    echo "ERROR in $test"
fi