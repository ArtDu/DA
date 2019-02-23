

#include "TSuffixTree.h"

using namespace std;

int main() {

    string text;
    cin >> text;
    TSuffixTree tree(text + "$");

    tree.TreePrint();

    return 0;
}

