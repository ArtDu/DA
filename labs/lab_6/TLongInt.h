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

    TLongInt &operator+(TLongInt &rhs);

    size_t Size();


    friend std::ostream& operator<< (std::ostream& stream, TLongInt & number);


private:

    std::vector<int> number;


};


#endif //LAB_6_TLONGINT_H
