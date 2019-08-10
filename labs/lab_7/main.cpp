#include <iostream>
#include <string>
#include <chrono>

int64_t matrix[10005][10005];

int64_t getCountUp(std::string &str) {

    for (int i = 0; i < str.size(); ++i) {
        matrix[i][i] = 1;
    }

    for (int i = 0, j = 1; j < str.size(); ++i, ++j) {
        if (str[i] == str[j])
            matrix[i][j] = 3;
        else
            matrix[i][j] = 2;
    }

    for (int l = 2; l < str.size(); ++l) {
        for (int i = 0, j = l; j < str.size(); ++i, ++j) {

            if (str[i] == str[j]) {
                matrix[i][j] = matrix[i + 1][j] + matrix[i][j - 1] + 1;
            } else {
                matrix[i][j] = matrix[i + 1][j] + matrix[i][j - 1] - matrix[i + 1][j - 1];
            }

        }
    }


    return matrix[0][str.size()-1];

}


int main() {

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::string str;
    std::cin >> str;

    std::cout << getCountUp(str) << std::endl;


    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "From bottom to up: " << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;

    return 0;
}
