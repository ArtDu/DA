source=main.cpp
bin=${source%.*}

#if ! g++ -std=c++11 ${source} -o ${bin}; then
#    echo "ERROR: Failed to compile file."
#    exit 1
#fi

mkdir -p tests
if ! python3 test_generator.py 10 ; then
    echo "ERROR: Failed to python generate tests."
    exit 1
fi

for test_file in `ls tests/*.t`; do
    answer_file="${test_file%.*}"
    echo "Execute ${test_file}"
    if !  ./main < $test_file > "${answer_file}.pl" ; then
        echo "ERROR"
        continue
    fi

    if ! diff -u "${answer_file}.txt"  "${answer_file}.pl" > /dev/null ; then
        echo "Failed"
    else
        echo "OK"
    fi 
done  
