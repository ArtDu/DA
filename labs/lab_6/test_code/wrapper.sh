#!/usr/bin/env bash
source=lab5.cpp
bin=${source%.*}

fail=false

if ! make -C ../; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

if ! make; then
    echo "ERROR: Failed to compile file."
    exit 1
fi


mkdir -p tests
if ! python3 test_gen.py ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

for test_file in `ls tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"
    if !  ./lab5 < ${test_file} > "${answer_file}.ans" ; then
        echo "ERROR"
        continue
    fi
     if !  ../main < ${test_file} > "${answer_file}.my" ; then
         echo "ERROR"
         continue
     fi

    if ! diff -u "${answer_file}.ans"  "${answer_file}.my" > /dev/null ; then
        echo "Failed"
        fail=true
        test=${answer_file}
    else
        echo "OK"
    fi 
done


if $fail ; then
    echo "ERROR in $test"
fi