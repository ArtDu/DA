#include <iostream>
#include <string>

int64_t matrix[101][101];

int64_t getCount(std::string &str, int i, int j) {

    if (i == j)
        return 1;

    if (i > j)
        return 0;

    if(matrix[i][j] == 0) {
        if (str[i] == str[j]) {
            matrix[i][j] = getCount(str, i + 1, j) + getCount(str, i, j - 1) + 1;
        } else {
            matrix[i][j] = getCount(str, i + 1, j) + getCount(str, i, j - 1) - getCount(str, i + 1, j - 1);
        }
        return matrix[i][j];
    }

    return matrix[i][j];

}


int main() {

    std::string str;
    std::cin >> str;

    std::cout << getCount(str, 0, str.size() - 1) << std::endl;

    return 0;
}
