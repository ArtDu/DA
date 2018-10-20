#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include "TVector.h"

const size_t VALUE_LEN = 64;
const size_t PHONES_BITS = 45; // Количество бит в номере

int Log(size_t a, size_t b) {
    return (int)(log(b) / log(a));
}

int GetDigit(long n, int r, int numSys, int i) { // получить разряд по r
    return (n >> (r * i)) & (numSys - 1);
}

int GetSortPar(long n) {                         //кол-во бит каждого разряда
    if (PHONES_BITS < Log(2, n)) {
        return PHONES_BITS;
    } else {
        return (int)Log(2, n);
    }
}

void CountingSort(TVector &vec, int index, int r, int numSys) {
    long *tmp_array = new long[numSys];

    //vector of result
    TVector result(vec.Size(), vec.Size());

    for(int i=0; i<numSys; ++i) {
        tmp_array[i] = 0;
    }

    //run of data array
    for (int indexI = 0; indexI < vec.Size(); ++indexI) {
        tmp_array[GetDigit(vec[indexI].keyInNum,r,numSys,index)]++;
    }

    //adding priviously
    for(int i=1; i<=numSys; ++i) {
        tmp_array[i] += tmp_array[i-1];
    }

    for (int j = vec.Size()-1; j >= 0 ; --j) {
        TData tmp_data = vec[j];
        result[tmp_array[GetDigit(vec[j].keyInNum,r,numSys,index)]-1] = tmp_data;
        tmp_array[GetDigit(vec[j].keyInNum,r,numSys,index)]--;
    }

    vec = result;

    delete[] tmp_array;

}

void RadixSort(TVector &vec) {

    if (vec.Size() < 2) {
        return;
    }

    int r = GetSortPar(vec.Size());                 //количество бит одного разряда
    int numSys = pow(2, r);                          //система счисления
    int phoneDigits = ceil((float)PHONES_BITS / r);  //количество разрядов


    for (int index = 0; index < phoneDigits ; ++index) {
        CountingSort(vec,index, r, numSys);

    }

}

bool Compare(const TData arg1, const TData arg2) {
    return (arg1.keyInNum < arg2.keyInNum);
}

void RunSort(TVector &vec, std::string s) {
    time_t start = clock();
    if (s=="radix") {
        RadixSort(vec);
    }
    else if (s=="std::stable_sort") {
        std::stable_sort(vec.First(), vec.Last(), Compare);
    }
    else {
        std::cerr << "Unknown type of sorting" << std::endl;
        return;
    }
    time_t end = clock();

    std::cout << "Sorting: " << s << std::endl;
    std::cout << "Time of working "
              << ((double) (end - start) / (double) CLOCKS_PER_SEC) * 1000
              << "ms." << std::endl << std::endl;
}

int main()
{

    TVector vec1(0,100);
    TVector vec2(0,100);
    TData elem;

    //scan the key
    elem.key = new char[17];
    while(scanf("%s",elem.key) != EOF) {

        if(strcmp(elem.key,"*")==0) {
            break;
        }

        //scan the value
        elem.val = new char[VALUE_LEN + 1];
        char* tmp = new char[VALUE_LEN + 1];
        scanf("%s",tmp);
        size_t tmp_size = strlen(tmp);
        for (int j = 0; j < (VALUE_LEN)-tmp_size; ++j) {
            elem.val[j] = '\0';
        }
        for (size_t j = VALUE_LEN-tmp_size, val_j = 0; j < VALUE_LEN+1; ++j, ++val_j) {
            elem.val[j] = tmp[val_j];
        }


        //record key into the number
        elem.keyInNum = 0;
        tmp_size = strlen(elem.key);
        for (size_t j = 0; j < tmp_size;  ++j) {
            if(elem.key[j] != '+' && elem.key[j]!= '-') {
                elem.keyInNum = elem.keyInNum * 10 + elem.key[j] - '0';
            }
        }


        vec1.PushBack(elem);
        vec2.PushBack(elem);

        elem.key = new char[17];
    }



    RunSort(vec1, "radix");
    RunSort(vec2, "std::stable_sort");

    return 0;
}

