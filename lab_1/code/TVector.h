#ifndef LAB_1_TVECTOR_H
#define LAB_1_TVECTOR_H

#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>

struct TData{
    long keyInNum;
    char *key;
    char *val;
};

class TVector {
private:
    TData* arr;
    long long vec_size;
    long long capacity;
public:
    TVector(long long size, long long capacity);
    long long Size();
    void Print();
    void PushBack(TData elem);
    TData* First();
    TData* Last();
    TData &operator[](size_t ix);
    TVector &operator= (TVector &vector);
    ~TVector();
};


#endif //LAB_1_TVECTOR_H
