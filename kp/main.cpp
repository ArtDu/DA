#include "invertedIndex.h"



int main() {




    int n, m;
    std::cin >> n >> m;

    invertedIndex iv(std::cin, n);
    std::string str;
    for(int i = 0; i < m; ++i) {

        getline(std::cin, str);
        iv.query(str);
    }



    return 0;
}