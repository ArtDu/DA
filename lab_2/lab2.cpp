#include <iostream>
#include <cstring>
#include "TTree.h"
#include <ctime>

char ToLower(char ch) {
    return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

bool IsLetter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}


int main()
{
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );
    TTree tree;


    while( true ) {
        TData data;
        char key[257];
        char mod;
        unsigned long long val;
        char action;
        size_t idx = 0;

        do{

            action = getchar();
            if (!std::cin) {
                std::cout << "ERROR: input option can not be read " << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }
        }
        while( action == '\n' || action == ' ' );
        if (!std::cin) {
            std::cout << "ERROR: input option can not be read " << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }


        if (action == EOF) {
            //std::cout << "runtime = " << clock()/1000.0 << std::endl; // время работы программы
            return 0;
        }

        switch (action) {
            case '+':
                /*clock_t start, end;
                double cpu_time_used;
                start = clock();
                end = clock();
                cpu_time_used = ((double) ((end - start))) / 1000;
                std::cout << cpu_time_used << std::endl;*/

                getchar();

                while (true) {
                    action = ToLower(getchar());

                    if (!IsLetter(action)) {
                        break;
                    }

                    key[idx++] = action;
                }
                key[idx] = '\0';
                val = 0;
                while ((action = getchar()) != '\n') {
                    val = val * 10 + action - '0';
                }

                data.key = new char[strlen(key) + 1];
                strcpy(data.key, key);
                data.value = val;

                if (!tree.Search(data)) {

                    tree.Insert(data);
                    printf("OK\n");

                }
                else {
                    printf("Exist\n");
                }

                delete[] data.key;

                break;
            case '-':

                getchar();

                while (true) {
                    action = ToLower(getchar());

                    if (!IsLetter(action)) {
                        break;
                    }

                    key[idx++] = action;
                }
                key[idx] = '\0';

                data.key = new char[strlen(key) + 1];
                strcpy(data.key, key);

                if (!tree.Search(data)) {
                    printf("NoSuchWord\n");
                }
                else {
                    tree.Delete(data);

                    printf("OK\n");
                }
                delete[] data.key;
                break;
            case '!':

                getchar();

                key[0] = action;

                while ((action = getchar()) != ' ')
                {
                    key[idx++] = action;
                }

                key[idx] = '\0';
                mod = key[0];

                idx = 0;

                while ((action = getchar()) != '\n')
                {
                    key[idx++] = action;
                }

                key[idx] = '\0';

                if( mod == 'S') {

                    if (tree.Save(key)) {
                        printf("OK\n");
                    }
                    else {
                        printf("ERROR: Couldn't create file\n");
                    }
                }
                else {
                    if (tree.Load(key)) {
                        printf("OK\n");
                    }
                    else {
                        printf("ERROR: Couldn't load file\n");
                    }
                }

                break;
            case '3':
                //tree.Print();
                break;
            default:

                key[0] = ToLower(action);
                ++idx;

                while (true) {
                    action = ToLower(getchar());

                    if (!IsLetter(action)) {
                        break;
                    }

                    key[idx++] = action;
                }

                key[idx] = '\0';

                data.key = new char[strlen(key) + 1];
                strcpy(data.key, key);
                if (!tree.Search(data)) {
                    printf("NoSuchWord\n");
                }
                else {
                    printf("OK: %llu\n",data.value);
                }
                delete[] data.key;
                break;
        }
    }

}