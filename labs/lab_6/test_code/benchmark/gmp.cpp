#include <iostream>
#include <chrono>
#include <gmpxx.h>


int main ()
{
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    mpz_class bigInt1, bigInt2;

    char op;
    while (std::cin >> bigInt1 && std::cin >> bigInt2) {

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
                if (bigInt1 == 0) {
                    if (bigInt2 == 0) {
                        std::cout << "Error" << std::endl;
                    } else {
                        std::cout << 0 << std::endl;
                    }
                } else if (bigInt1 == 1) {
                    std::cout << 1 << std::endl;
                } else {
                    std::cout << (bigInt1 ^ bigInt2) << std::endl;
                }
                break;
            case '/':
                if (bigInt2 == 0) {
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

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Gsm: " << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;


    return 0;
}
