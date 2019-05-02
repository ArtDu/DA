//
// Created by art on 20.03.19.
//

#include <iostream>
#include <iomanip>
#include "TLongInt.h"


TLongInt::TLongInt(std::string &strNum) {
    std::string tmpStr;
    int onePiece = 0;
    int i = strNum.size() - 1;
    for (; i - 6 >= 0; i -= 6) {

        tmpStr = strNum.substr(i - 5, 6);
        std::cout << tmpStr << std::endl;
        int j;
        for (j = tmpStr.size() - 1; j >= 0; --j) {
            onePiece = onePiece * 10 + (tmpStr[j] - '0');
        }
        number.push_back(onePiece);
        onePiece = 0;
    }
    if (i >= -6 && i < 6) {
        tmpStr = strNum.substr(0, i + 1);
        std::cout << tmpStr << std::endl;
        int j;
        for (j = tmpStr.size() - 1; j >= 0; --j) {
            onePiece = onePiece * 10 + (tmpStr[j] - '0');
        }
        number.push_back(onePiece);
    }
}


TLongInt &TLongInt::operator+(TLongInt &rhs) {
    int i = 0;
    int remainder = 0;
    while (i < number.size() && i < rhs.number.size()) {
        number[i] = number[i] + rhs.number[i] + remainder;
        remainder = number[i] / 1000000;
        number[i] = number[i] % 1000000;
    }
    if (i < number.size()) {
        number[i] = number[i] + remainder;
    }

    while (i < rhs.number.size()) {
        number.push_back(rhs.number[i] + remainder);
        remainder = 0;
        i++;
    }

    return *this;
}

size_t TLongInt::Size() {
    return number.size();
}

std::ostream &
operator<<(std::ostream &stream, TLongInt &number) {
    if (number.Size() == 0) {
        return stream;
    }

    stream << number.number[number.Size() - 1];
    for (int i = number.Size() - 2; i >= 0; --i) {
        stream << std::setfill('0') << std::setw(6) << number.number[i];
    }
    return stream;
}