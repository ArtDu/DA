

#include <iostream>
#include "TLongInt.h"


using namespace std;

int main() {

    std::string str1, str2;
    char op;
    while (std::cin >> str1 && std::cin >> str2) {

        TLongInt bigInt1(str1);
        TLongInt bigInt2(str2);

        std::cin >> op;

        switch (op) {
            case '+':
                std::cout << bigInt1 + bigInt2 << std::endl;
                break;
            case '>':
                std::cout << (bigInt1 > bigInt2 ? "true" : "false") << std::endl;
                break;
            case '<':
                std::cout << (bigInt1 < bigInt2 ? "true" : "false") << std::endl;
                break;
            case '=':
                std::cout << (bigInt1 == bigInt2 ? "true" : "false") << std::endl;
                break;
            case '-':
                if (bigInt1 >= bigInt2) {
                    std::cout << bigInt1 - bigInt2 << std::endl;
                } else {
                    std::cout << "Error" << std::endl;
                }
                break;
            case '*':
                std::cout << bigInt1 * bigInt2 << std::endl;
                break;
            case '^':
                if (bigInt1 == TLongInt(1, 0)) {
                    if (bigInt2 == TLongInt(1, 0)) {
                        std::cout << "Error" << std::endl;
                    } else {
                        std::cout << 0 << std::endl;
                    }
                } else if (bigInt1 == TLongInt(1, 1)) {
                    std::cout << 1 << std::endl;
                } else {
                    int numPow = std::stoi(str2);
                    std::cout << (bigInt1 ^ numPow) << std::endl;
                }
                break;
            case '/':
                if (bigInt2 == TLongInt(1, 0)) {
                    std::cout << "Error" << std::endl;
                } else {
                    std::cout << bigInt1 / bigInt2 << std::endl;
                }
                break;
            default:
                std::cout << "Error" << std::endl;
                break;
        }


    }

    return 0;
}
