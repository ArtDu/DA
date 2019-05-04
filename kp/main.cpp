#include "invertedIndex.h"



int main() {

    std::cout << "Введите текста через <enter>(для конца ввода нажмите 0):\n";
    invertedIndex iv(std::cin);
    std::string str;
    while(true) {
        std::cout << "Сделайте запрос(для выхода введите 0)" <<std::endl;
        std::cout << "Доступны запросы word1 <&,|> word2 или ~ word1" <<std::endl;
        getline(std::cin, str);
        if(str=="0") {
            break;
        }
        iv.query(str);
    }



    return 0;
}