#include <iostream>
#include <cstring>
#include "TTree.h"

int main()
{
    TTree tree;
    char key[257];
    char file_name[257];
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
                FILE *fp;
                if( strcmp(mod, "Save") == 0 ) {
                    std::cin >> file_name;
                    fp = fopen(file_name, "w");
                    if ( fp == NULL ) {
                        std::cout << "ERROR: Couldn't create file" << std::endl;
                    }
                    else {
                        std::cout << "OK" << std::endl;
                        tree.Save(fp);
                        fclose (fp);
                    }
                }
                else if ( strcmp(mod, "Load") == 0 ) {
                    std::cin >> file_name;
                    fp = fopen(file_name, "r");
                    if ( fp == NULL ) {
                        std::cout << "ERROR: Couldn't open file" << std::endl;
                    }
                    else {
                        std::cout << "OK" << std::endl;
                        tree.DeleteTree();
                        tree.Load(fp);
                        fclose (fp);
                    }
                }
                break;
            /*case '3':
                tree.Print();
                break;*/
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