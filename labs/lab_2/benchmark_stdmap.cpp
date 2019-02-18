#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include <ctime>


char NODE = 'y';
char END = 'n';

char ToLower( char ch ) {
    return ch >= 'A' && ch <= 'Z' ? ch - 'A' + 'a' : ch;
}

bool IsLetter( char ch ) {
    return ( ch >= 'a' && ch <= 'z' ) || ( ch >= 'A' && ch <= 'Z' );
}

bool Save( std::map<std::string, unsigned long long> &map, const char* filename ) {

    FILE* f = fopen( filename, "wb" );

    if ( f == nullptr ) {
        return false;
    }

    if ( map.empty() ) {
        if (fwrite(&END, sizeof(char), 1, f) != 1) {
            return false;
        }
        return true;
    }


    for ( auto it : map ) {

        fwrite(&NODE, sizeof(char), 1, f);

        size_t length = it.first.size();
        char* key = (char *)malloc(sizeof(char) * (length + 1));;
        strcpy(key ,it.first.c_str());
        unsigned long long val = it.second;

        int res = fwrite(&length, sizeof(length), 1, f);
        res = fwrite(key, sizeof(char), length, f);
        res = fwrite(&val, sizeof( val ), 1, f);

    }

    fwrite(&END, sizeof(char), 1, f);
    fclose(f);
    return true;
}

bool Load( std::map<std::string, unsigned long long> &map, const char* filename ) {

    FILE* f = fopen( filename, "rb" );

    if ( f == nullptr ) {
        return false;
    }

    map.clear();

    while( true ) {
        char mark;
        fread(&mark, sizeof(char), 1, f) != 1;

        if (mark == END) {
            fclose(f);
            return true;
        }
        if (mark == NODE) {

            std::string _key;
            size_t length;
            fread(&length, sizeof(length), 1, f);

            char* key;
            key = (char *)malloc(sizeof(char) * (length + 1));
            fread(key, sizeof(char), length, f);
            key[length] = '\0';


            unsigned long long val;
            fread(&val, sizeof(val), 1, f);

            _key.assign( key );

            map.insert( std::pair<std::string, unsigned long long>( _key, val ));
        }
        else {
            fclose(f);
            return false;
        }



    }



}


int main() {
    std::ios_base::sync_with_stdio( false );
    std::cin.tie( nullptr );
    std::map<std::string, unsigned long long> tree;


    while ( true ) {
        std::string str_key;
        std::map<std::string, unsigned long long>::iterator it;
        char key[257];
        char mod;
        unsigned long long val;
        char action;
        size_t idx = 0;

        do {

            action = getchar();
            if ( !std::cin ) {
                std::cout << "ERROR: input option can not be read " << std::endl;
                std::cin.clear();
                std::cin.ignore();
                continue;
            }
        } while ( action == '\n' || action == ' ' );
        if ( !std::cin ) {
            std::cout << "ERROR: input option can not be read " << std::endl;
            std::cin.clear();
            std::cin.ignore();
            continue;
        }


        if ( action == EOF) {
            std::cout << std::endl << "Container: map" << std::endl;
            std::cout << "runtime = " << clock() / 1000.0 << std::endl; // время работы программы
            return 0;
        }

        switch ( action ) {
            case '+':
                /*clock_t start, end;
                double cpu_time_used;
                start = clock();
                end = clock();
                cpu_time_used = ((double) ((end - start))) / 1000;
                std::cout << cpu_time_used << std::endl;*/

                getchar();

                while ( true ) {
                    action = ToLower( getchar());

                    if ( !IsLetter( action )) {
                        break;
                    }

                    key[idx++] = action;
                }
                key[idx] = '\0';
                val = 0;
                while (( action = getchar()) != '\n' ) {
                    val = val * 10 + action - '0';
                }


                str_key.assign( key );

                if ( tree.find( str_key ) == tree.end()) {

                    tree.insert( std::pair<std::string, unsigned long long>( str_key, val ));
                    printf( "OK\n" );

                } else {
                    printf( "Exist\n" );
                }


                break;
            case '-':

                getchar();

                while ( true ) {
                    action = ToLower( getchar());

                    if ( !IsLetter( action )) {
                        break;
                    }

                    key[idx++] = action;
                }
                key[idx] = '\0';

                str_key.assign( key );

                if ( tree.find( str_key ) == tree.end()) {
                    printf( "NoSuchWord\n" );
                } else {
                    tree.erase( str_key );
                    printf( "OK\n" );
                }

                break;
            case '!':

                getchar();

                key[0] = action;

                while (( action = getchar()) != ' ' ) {
                    key[idx++] = action;
                }

                key[idx] = '\0';
                mod = key[0];

                idx = 0;

                while (( action = getchar()) != '\n' ) {
                    key[idx++] = action;
                }

                key[idx] = '\0';

                if ( mod == 'S' ) {

                    if ( Save( tree, key )) {
                        printf( "OK\n" );
                    } else {
                        printf( "ERROR: Couldn't create file\n" );
                    }
                } else {
                    if ( Load( tree, key )) {
                        printf( "OK\n" );
                    } else {
                        printf( "ERROR: Couldn't load file\n" );
                    }
                }

                break;
            case '3':
                //tree.Print();
                break;
            default:

                key[0] = ToLower( action );
                ++idx;

                while ( true ) {
                    action = ToLower( getchar());

                    if ( !IsLetter( action )) {
                        break;
                    }

                    key[idx++] = action;
                }

                key[idx] = '\0';

                str_key.assign( key );
                if ( tree.find( str_key ) == tree.end()) {
                    printf( "NoSuchWord\n" );
                } else {
                    it = tree.find( str_key );
                    printf( "OK: %llu\n", it->second );
                }

                break;
        }
    }

}