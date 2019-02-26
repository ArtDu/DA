

#include "TSuffixTree.h"

#include <chrono>

using namespace std;

int main() {


    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    string text;
    cin >> text;
    TSuffixTree tree(text + "$");

    //tree.TreePrint();


    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Search: " << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;

    return 0;
}

