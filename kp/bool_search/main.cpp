#include "TInvertedIndex.h"
#include <ctime>
#include <cstring>


int main(int argc, char **argv) {
    //unsigned int start_time =  clock();

    std::locale::global(std::locale("en_US.UTF-8"));


    if (argc < 2) {
        std::cout << "Arguments error: missing name of action\n";
        return 0;
    }

    if (strcmp(argv[1], "index") == 0) {

        if (argc < 6) {
            std::cout << "Arguments error: wrong input or output arguments\n";
            return 0;
        }

        std::wifstream input_file;
        std::wofstream output_file;

        for (int i = 2; i < argc; i += 2) {
            if (strcmp(argv[i], "--input") == 0) {
                if (argc - 1 == i) {
                    std::cout << "Argument error\n";
                    return 1;
                }
                std::string input_file_name(argv[i + 1]);
                input_file.open(input_file_name);
                if (!input_file.is_open()) {
                    std::cout << "File error: file doesn't exist\n";
                    return 1;
                }
            } else {
                if (argc - 1 == i) {
                    std::cout << "Argument error\n";
                    return 1;
                }
                std::string output_file_name(argv[i + 1]);
                output_file.open(output_file_name);
                if (!output_file.is_open()) {
                    std::cout << "File error: output file error\n";
                }
            }
        }

        TInvertedIndex iv;
        iv.Read(input_file);
        iv.Save(output_file);

    } else if (strcmp(argv[1], "search") == 0) {

        if (argc < 8) {
            std::cout << "Arguments error: wrong input or output arguments\n";
            return 0;
        }

        TInvertedIndex iv;

        std::wifstream index_file;
        std::wifstream input_file;
        std::wofstream output_file;



        for (int i = 2; i < argc; ++i) {
            if (strcmp(argv[i], "--index") == 0) {
                if (argc - 1 == i) {
                    std::cout << "Argument error\n";
                    return 1;
                }
                ++i;
                std::string index_file_name(argv[i]);
                index_file.open(index_file_name);
                if (!index_file.is_open()) {
                    std::cout << "File error: file doesn't exist\n";
                }
            }
            else if (strcmp(argv[i], "--input") == 0) {
                if (argc - 1 == i) {
                    std::cout << "Argument error\n";
                    return 1;
                }
                ++i;
                std::string input_file_name(argv[i]);
                input_file.open(input_file_name);
                if (!input_file.is_open()) {
                    std::cout << "File error: file doesn't exist\n";
                }
            }
            else if (strcmp(argv[i], "--output") == 0) {
                if (argc - 1 == i) {
                    std::cout << "Argument error\n";
                    return 1;
                }
                ++i;
                std::string output_file_name(argv[i]);
                output_file.open(output_file_name);
                if (!output_file.is_open()) {
                    std::cout << "File error: output file error\n";
                }
            }
            else if (strcmp(argv[i], "--full-output") == 0) {
                iv.full_output = true;
            }
        }

        iv.Load(index_file);
        iv.ReadQueries(input_file, output_file);


    } else {
        std::cout << "Arguments error: wrong action\n";
        return 0;
    }


//    unsigned int end_time = clock(); // конечное время
//    unsigned int search_time = end_time - start_time; // искомое время
//    std::cout << search_time << "\n";
    return 0;
}