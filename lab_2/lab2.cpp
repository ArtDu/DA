#include <iostream>
#include <cstring>
#include "TTree.h"
#include <ctime>

char ToLower( char ch ) {
    return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

bool IsLetter( char ch ) {
    return ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' );
}

void GetKey( char key[] );

void GetVal( unsigned long long &val );

int main() {
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );

    TTree tree;

    while ( true ) {

        TData data;
        char key[257];
        char keyForSearch[257];
        unsigned long long val;
        char mod, action;
        int idx;

        do {

            action = getchar();
            if ( !std::cin ) {
                std::cout << "ERROR: input option can not be read " << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }
        } while ( action == '\n' || action == ' ' );


        if ( action == EOF) {
            //std::cout << "runtime = " << clock()/1000.0 << std::endl; // время работы программы
            return 0;
        }

        switch ( action ) {
            case '+':

                getchar();

                GetKey( key );
                GetVal( val );

                data.key = new char[strlen( key ) + 1];
                strcpy( data.key, key );
                data.value = val;

                if ( !tree.Search( data )) {
                    tree.Insert( data );
                    printf( "OK\n" );
                } else {
                    printf( "Exist\n" );
                }

                delete[] data.key;

                break;
            case '-':

                getchar();

                GetKey( key );

                data.key = new char[strlen( key ) + 1];
                strcpy( data.key, key );

                if ( !tree.Search( data )) {
                    printf( "NoSuchWord\n" );
                } else {
                    tree.Delete( data );
                    printf( "OK\n" );
                }
                delete[] data.key;
                break;
            case '!':

                getchar();

                GetKey( key );
                mod = key[0];

                idx = 0;

                while ((action = getchar()) != '\n')
                {
                    key[idx++] = action;
                }

                key[idx] = '\0';

                if ( mod == 'S' ) {

                    if ( tree.Save( key )) {
                        printf( "OK\n" );
                    } else {
                        printf( "ERROR: Couldn't create file\n" );
                    }
                } else {
                    if ( tree.Load( key )) {
                        printf( "OK\n" );
                    } else {
                        printf( "ERROR: Couldn't load file\n" );
                    }
                }

                break;

            default:

                keyForSearch[0] = ToLower(action);
                keyForSearch[1] = '\0';

                GetKey( key );
                strcat( keyForSearch, key );
                data.key = new char[strlen(keyForSearch) + 1];
                strcpy(data.key, keyForSearch);

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


void GetKey( char key[] ) {

    char ch;
    int idx = 0;


    while ( true ) {
        ch = ToLower( getchar());

        if ( !IsLetter( ch )) {
            break;
        }

        key[idx++] = ch;
    }
    key[idx] = '\0';
}

void GetVal( unsigned long long &val ) {
    char ch;
    val = 0;
    while (( ch = getchar()) != '\n' ) {
        val = val * 10 + ch - '0';
    }
}