#!/usr/bin/env bash

# *.sh <count of tests>

fail=false

if ! make -C ../; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

if ! make ; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

if [[ $# -ne 1 ]]	; then
    echo "ERROR: Failed in args."
    exit 1
fi

mkdir -p tests
if ! python3 test_gen.py $1 ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

for test_file in `ls tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"

    if !  ../main < ${test_file} > "${answer_file}.my" ; then
     echo "ERROR"
     continue
    fi

    if !  ./main < ${test_file} > "${answer_file}.a" ; then
         echo "ERROR"
         continue
    fi

    diff "${answer_file}.a"  "${answer_file}.my"
done

