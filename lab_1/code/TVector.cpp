//
// Created by art on 16.09.18.
//

#include "TVector.h"

const size_t VALUE_LEN = 64;

TVector::TVector(long long size, long long capacity) {
    vec_size = size;
    this->capacity = capacity;
    arr = new TData[capacity];
}

long long TVector::Size() {
    return this->vec_size;
}

void TVector::PushBack(TData elem) {
    if(vec_size == capacity) {
        capacity *= 30;
        arr = (TData *) realloc(arr, capacity * sizeof(TData));
    }
    arr[vec_size] = elem;
    vec_size++;
}

void TVector::Print() {
    for (int var = 0; var < vec_size; ++var) {

        std::cout <<arr[var].key<<"\t";//<<arr[var].val<<"\n";
        for(int i = 0; i < VALUE_LEN; ++i) {
            if(arr[var].val[i]!='\0')
                std::cout<<arr[var].val[i];
        }
        std::cout<<"\n";
    }
}

TData* TVector::First(){
    if (vec_size==0)
        return NULL;
    return &arr[0];
}

TData* TVector::Last(){
    if (vec_size==0)
        return NULL;
    return &arr[vec_size];

}


TData &TVector::operator[](size_t ix) {
    return arr[ix];
}

TVector &TVector::operator= (TVector &vector) {
    delete [] arr;
    arr = nullptr;
    if (vector.arr != nullptr) {
        arr = new TData[vector.capacity];
        for (int ix = 0; ix < vector.Size(); ix++) {
            arr[ix] = vector.arr[ix];
        }
        capacity = vector.capacity;
        vec_size = vector.Size();
    }
    return *this;
}



TVector::~TVector() {

    delete[] arr;
}