

#include <iostream>
#include "TLongInt.h"


using namespace std;

int main() {


    std::string str;

    std::cin >> str;
    TLongInt bigInt1(str);


    std::cin >> str;
    TLongInt bigInt2(str);

    bigInt1 + bigInt2;


    std::cout << bigInt1 << std::endl;

    return 0;
}

//456456
//798798987