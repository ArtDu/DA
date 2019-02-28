

#include "TSuffixTree.h"

#include <chrono>

using namespace std;

int main() {



    string text;
    cin >> text;
    TSuffixTree tree(text + "$");

    //tree.TreePrint();

    int count = 1;
    std::vector<int> res;
    while (std::cin >> text){
        res = tree.Search(text);
        if (!res.empty()) {
            std::cout << count << ": ";
            for (int i = 0; i < res.size()-1; ++i)
                std::cout << res[i] << ", ";
            std::cout << res[res.size()-1] << std::endl;
        }
        ++count;
    }


    return 0;
}

