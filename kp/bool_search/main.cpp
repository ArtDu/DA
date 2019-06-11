#include "invertedIndex.h"
#include <ctime>
#include <cstring>





int main(int argc, char **argv) {
    //unsigned int start_time =  clock();

    if (argc < 2) {
        std::cout << "Arguments error: missing name of action\n";
        return 0;
    }

    if (strcmp(argv[1], "index") == 0) {

        if (argc < 6) {
            std::cout << "Arguments error: wrong input or output arguments\n";
            return 0;
        }

        if (strcmp(argv[2], "--input") != 0) {
            std::cout << "Arguments error: input error\n";
            return 0;
        }

        std::string input_file_name (argv[3]);
        std::ifstream input_file;
        input_file.open (input_file_name);
        if (!input_file.is_open())
        {
            std::cout << "File error: file doesn't exist\n";
        }

        if (strcmp(argv[4], "--output") != 0) {
            std::cout << "Arguments error: input error\n";
            return 0;
        }

        std::string output_file_name (argv[5]);
        std::ofstream output_file;
        output_file.open (output_file_name);
        if (!output_file.is_open())
        {
            std::cout << "File error: output file error\n";
        }

        invertedIndex iv(input_file);



    } else if (strcmp(argv[1], "search") == 0) {






    }
    else {
        std::cout << "Arguments error: wrong action\n";
        return 0;
    }









        /*uint32_t n, m; // count of texts, count of queries
        std::cin >> n >> m;
        invertedIndex iv(std::cin, n);




        //queries
        std::string str;
        for(uint32_t i = 0; i < m; ++i) {

            getline(std::cin, str);
            iv.query(str);
        }*/



//    unsigned int end_time = clock(); // конечное время
//    unsigned int search_time = end_time - start_time; // искомое время
//    std::cout << search_time << "\n";
        return 0;
}