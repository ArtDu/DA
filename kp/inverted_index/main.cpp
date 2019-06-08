#include "invertedIndex.h"
#include <ctime>
int main() {



    //unsigned int start_time =  clock();

    uint32_t n, m; // count of texts, count of queries
    std::cin >> n >> m;
    invertedIndex iv(std::cin, n);




    //queries
    std::string str;
    for(uint32_t i = 0; i < m; ++i) {

        getline(std::cin, str);
        iv.query(str);
    }
//    unsigned int end_time = clock(); // конечное время
//    unsigned int search_time = end_time - start_time; // искомое время
//    std::cout << search_time << "\n";
    return 0;
}