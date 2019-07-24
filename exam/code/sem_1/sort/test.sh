#!/usr/bin/env bash

#for test_file in `ls sort/*.py`; do
#    answer_file="${test_file%.*}";
#    echo "Execute ${test_file}"
#    if python
#done

if ! diff -u test_1 test_2 > /dev/null ; then
    echo "Failed"
else
    echo "OK"
fi