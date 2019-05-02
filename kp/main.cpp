#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

void spiltAndUpdateDict(int row, std::string &str, std::map<std::string, std::vector<std::pair<int, int>>> &dict) {
    std::istringstream iss(str);
    int column = 1;
    for (std::string s; iss >> s;) {


        auto tmp_pair_nums = std::make_pair(row, column);

        dict[s].push_back(tmp_pair_nums);

        column++;
    }
}



int main() {
    std::string str;

    std::map<std::string, std::vector<std::pair<int, int>>> dict;


    int row = 1;
    while(getline(std::cin, str)) {
        if(str=="0")
            break;
        spiltAndUpdateDict(row, str, dict);
        row++;
    }





    return 0;
}