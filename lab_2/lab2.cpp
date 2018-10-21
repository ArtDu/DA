#include <iostream>
#include <cstring>
#include "TTree.h"

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    TTree* tree = new TTree();
    char key[257];
    char fileName[257];
    char mod[8];
    unsigned long long val;
    char action[257];
    while( std::cin >> action )
    {
        if (!std::cin) {
            std::cout << "ERROR: input option can not be read " << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }

        switch (action[0]) {
            case '+':
                std::cin >> key >> val;
                for(int i = 0; key[i]; i++){
                    key[i] = tolower(key[i]);
                }
                tree->Insert(key, val);
                break;
            case '-':
                std::cin >> key;
                for(int i = 0; key[i]; i++){
                    key[i] = tolower(key[i]);
                }
                tree->Delete(key);
                break;
            case '!':
                std::cin >> mod;

                if( strcmp(mod, "Save") == 0 ) {
                    std::cin >> fileName;
                    tree->Save( fileName );
                }
                else if ( strcmp(mod, "Load") == 0 ) {
                    std::cin >> fileName;
                    tree->Load( fileName );
                }
                break;
            case '3':
                tree->Print();
                break;
            default:
                strcpy(key, action);
                for(int i = 0; key[i]; i++){
                    key[i] = tolower(key[i]);
                }
                tree->Search(key);
                break;
        }
    }
    delete tree;
    return 0;
}