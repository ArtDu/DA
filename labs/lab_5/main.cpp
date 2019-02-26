

#include "TSuffixTree.h"

#include <chrono>

using namespace std;

int main() {


    //std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

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


    /*std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Search: " << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;*/

    return 0;
}

