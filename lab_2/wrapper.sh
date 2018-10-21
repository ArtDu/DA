source="lab2.cpp TNode.cpp TTree.cpp"
bin="main"

if ! g++ -std=c++11 -g -pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm ${source} -o ${bin}; then
    echo "ERROR: Failed to compile file."
    exit 1
fi

mkdir -p tests
if ! python3 test_generator.py 10 ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

for test_file in `ls tests/*.t`; do
    echo "Execute ./${bin} <  ${test_file} > tmp"
    if ! ./${bin} < $test_file > tmp ; then
        echo "ERROR"
        continue
    fi
    answer_file="${test_file%.*}"

    if ! diff  "${answer_file}.a" tmp ; then
        echo "Failed"
    else
        echo "OK"
    fi 
done
