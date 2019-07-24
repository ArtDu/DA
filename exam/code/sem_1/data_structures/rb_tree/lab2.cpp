#include <iostream>
#include <cstring>
#include "TTree.h"
#include <ctime>

int main() {

    TTree tree;

    string plus;
    string key;
    uint64_t val;

    while(cin >>plus) {
        if(plus == "0")
            break;
        else if (plus == "+") {
            cin >> key;
            cin >> val;
            tree.Insert(key, val);
        }
        else {
            cin >> key;
            tree.DeleteNode(key);
        }
        /*tree.PrintTree();
        cout << "**\n";*/
    }
    tree.PrintTree();


    return 0;
}

