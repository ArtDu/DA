#!/usr/bin/env bash


if ! make -C ../.. > /dev/null; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

if ! g++ -std=c++11 find.cpp -o find > /dev/null; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

cd ../
mkdir -p tests
if ! python3 test_gen.py ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi
cd benchmark/

for test_file in `ls ../tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"
    if !  ./find < ${test_file} > "${answer_file}.ans" ; then
        echo "ERROR"
        continue
    fi
     if !  ../../main < ${test_file} > "${answer_file}.my" ; then
         echo "ERROR"
         continue
     fi

    diff "${answer_file}.ans"  "${answer_file}.my"

done

