

#include <iostream>
#include "TLongInt.h"


using namespace std;

int main() {

    std::string str1, str2;
    char op;
    while(std::cin >> str1 && std::cin >> str2) {

        TLongInt bigInt1(str1);
        TLongInt bigInt2(str2);

        std::cin >> op;

        switch (op) {
            case '+':
                bigInt1 += bigInt2;
                std::cout << bigInt1 << std::endl;
                break;
            case '-':
                if(bigInt1 -= bigInt2) {
                    std::cout << bigInt1 << std::endl;
                }
                else {
                    std::cout << "Error" << std::endl;
                }
                break;
            case '*':
                std::cout << (bigInt1 * bigInt2) << std::endl;
                break;
            default:
                std::cout << "Error" << std::endl;
                break;
        }


    }

//    bigInt1 + bigInt2;
//
//
//    std::cout << bigInt1 << std::endl;

    return 0;
}

//456456
//798798987