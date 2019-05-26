//
// Created by art on 20.03.19.
//

#ifndef LAB_6_TLONGINT_H
#define LAB_6_TLONGINT_H

#include <vector>
#include <algorithm>
#include <string>

class TLongInt {
public:

    TLongInt(std::string &strNum);

    TLongInt(size_t size);


    TLongInt(size_t size, int num);

    TLongInt();

    void operator+=(TLongInt &rhs);
    void operator+=(TLongInt &&rhs);

    void operator-=(TLongInt &rhs);
    void operator-=(TLongInt &&rhs);

    bool operator<(TLongInt &&rhs);
    bool operator<=(TLongInt &&rhs);
    bool operator>(TLongInt &&rhs);
    bool operator>=(TLongInt &&rhs);
    bool operator!=(TLongInt &&rhs);
    bool operator==(TLongInt &&rhs);

    bool operator<(TLongInt &rhs);
    bool operator<=(TLongInt &rhs);
    bool operator>(TLongInt &rhs);
    bool operator>=(TLongInt &rhs);
    bool operator!=(TLongInt &rhs);
    bool operator==(TLongInt &rhs);

    TLongInt operator+(TLongInt &rhs);
    TLongInt operator+(TLongInt &&rhs);

    TLongInt operator-(TLongInt &rhs);
    TLongInt operator-(TLongInt &&rhs);

    TLongInt operator*(TLongInt &rhs);
    TLongInt operator*(TLongInt &&rhs);

    TLongInt operator/(TLongInt &rhs);

    TLongInt operator^(int num);

    size_t Size() const;


    friend std::ostream &operator<<(std::ostream &stream, TLongInt &number);
    friend std::ostream &operator<<(std::ostream &stream, TLongInt &&number);

    static const int BASE = 1000000000;
    static const int BASE_SIZE = 9;
private:

    std::vector<int> number;


};


#endif //LAB_6_TLONGINT_H
