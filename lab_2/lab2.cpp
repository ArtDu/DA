#include <iostream>
#include <cstring>
#include "TTree.h"

int main()
{
    TTree tree;
    char key[257];
    char mod[8];
    unsigned long long val;
    char action[257];
    while( std::cin >> action )
    {
        switch (action[0]) {
            case '+':
                std::cin >> key >> val;
                for(int i = 0; key[i]; i++){
                    key[i] = tolower(key[i]);
                }
                tree.Insert(key, val);
                break;
            case '-':
                std::cin >> key;
                for(int i = 0; key[i]; i++){
                    key[i] = tolower(key[i]);
                }
                tree.Delete(key);
                break;
            case '!':
                std::cin >> mod;

                break;
            default:
                strcpy(key, action);
                for(int i = 0; key[i]; i++){
                    key[i] = tolower(key[i]);
                }
                tree.Search(key);
                break;
        }
    }

    return 0;
}