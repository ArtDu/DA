//
// Created by art on 20.03.19.
//

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include "TLongInt.h"


TLongInt::TLongInt(std::string &strNum) {
    std::string tmpStr;
    int numeral = 0;
    for (int i = static_cast<int>(strNum.size()); i > 0; i -= BASE_SIZE) {

        if (i < BASE_SIZE) {
            tmpStr = strNum.substr(0, i);
        } else {
            tmpStr = strNum.substr(i - BASE_SIZE, BASE_SIZE);
        }
        for (int j = 0; j < tmpStr.size(); ++j) {
            numeral = numeral * 10 + (tmpStr[j] - '0');
        }
        number.push_back(numeral);
        numeral = 0;
        //std::cout << tmpStr << " ";
    }
    while (number.size() > 1 && number.back() == 0)
        number.pop_back();
    //std::cout << std::endl;
}

TLongInt::TLongInt(size_t size) : number(size) {}
TLongInt::TLongInt() {}


void TLongInt::operator+=(TLongInt &rhs) {
    int i = 0;
    int remainder = 0;
    while ((i < std::max(number.size(), rhs.number.size())) || remainder) {
        if (i == number.size()) {
            number.push_back(0);
        }
        number[i] += (i < rhs.number.size() ? rhs.number[i] : 0) + remainder;
        remainder = number[i] >= BASE;
        if (remainder)
            number[i] -= BASE;
        ++i;
    }
}

bool TLongInt::operator-=(TLongInt &rhs) {
    int i = 0;
    int remainder = 0;
    while ((i < std::max(number.size(), rhs.number.size())) || remainder) {
        if (i == number.size()) {
            return false;
        }
        number[i] -= ((i < rhs.number.size() ? rhs.number[i] : 0) + remainder);
        remainder = number[i] < 0;
        if (remainder)
            number[i] += BASE;
        ++i;
    }

    return true;
}

TLongInt TLongInt::operator*(TLongInt &rhs) {
    TLongInt ans(this->Size() + rhs.Size());
    int remainder = 0;

    for (size_t i = 0; i < this->Size(); ++i) {
        for (size_t j = 0; j < rhs.Size() || remainder; ++j) {
            long long cur = ans.number[i + j] + static_cast<long long>(this->number[i]) * (j < rhs.Size() ? static_cast<long long>(rhs.number[j]) : 0) + remainder;
            ans.number[i + j] = static_cast<int> (cur % BASE);
            remainder = static_cast<int> (cur / BASE);
        }
    }
    while (ans.number.size() > 1 && ans.number.back() == 0)
        ans.number.pop_back();
    return ans;
}

TLongInt TLongInt::operator/(TLongInt &rhs) {
    TLongInt ans;
        
    return ans;
}

size_t TLongInt::Size() {
    return number.size();
}

std::ostream &
operator<<(std::ostream &stream, TLongInt &number) {
    if (number.Size() == 0) {
        stream << 0;
        return stream;
    }

    while (number.number.size() > 1 && number.number.back() == 0)
        number.number.pop_back();
    stream << number.number[number.Size() - 1];
    for (int i = static_cast<int>(number.Size()) - 2; i >= 0; --i) {
        stream << std::setfill('0') << std::setw(TLongInt::BASE_SIZE) << number.number[i];
    }
    return stream;
}

std::ostream &
operator<<(std::ostream &stream, TLongInt &&number) {
    if (number.Size() == 0) {
        stream << 0;
        return stream;
    }

    while (number.number.size() > 1 && number.number.back() == 0)
        number.number.pop_back();
    stream << number.number[number.Size() - 1];
    for (int i = static_cast<int>(number.Size()) - 2; i >= 0; --i) {
        stream << std::setfill('0') << std::setw(TLongInt::BASE_SIZE) << number.number[i];
    }
    return stream;
}