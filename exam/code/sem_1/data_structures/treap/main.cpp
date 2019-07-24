#include <iostream>
#include <cstring>
#include <vector>
#include "TTree.h"
#include <ctime>


int main() {

    srand(time(NULL));
    vector<int64_t > randInts(101,0);

    TTree tree;

    string plus;
    uint64_t key;
    uint64_t pr;

    while(cin >>plus) {
        if(plus == "0")
            break;
        else if (plus == "+") {
            cin >> key;
            while (true) {
                pr = (rand() % 100) + 1;
                if (randInts[pr] == 0) {
                    randInts[pr] = 1;
                    break;
                }
            }
            tree.InsertMS(key, pr);
        }
        else {

        }

    }

    tree.PrintTree();
    cout << "*********\n";

    tree.DeleteMS(5);

    tree.PrintTree();


   /*
    TTree t1, t2;
    split(tree, t1, t2, 7);
    merge(tree, t1, t2);

    cout << "tree:\n";
    tree.PrintTree();
    cout << "*********\n";
    cout << "t1:\n";
    t1.PrintTree();
    cout << "*********\n";
    cout << "t2:\n";
    t2.PrintTree();*/



    return 0;
}

