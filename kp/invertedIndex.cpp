//
// Created by art on 03.05.19.
//

#include "invertedIndex.h"


invertedIndex::invertedIndex(std::istream& in) {
    std::string str;

    int row = 1;
    while(getline(in, str)) {
        if(str=="0")
            break;
        spiltAndUpdateDict(row, str, dict);
        row++;
    }
}

void invertedIndex::spiltAndUpdateDict(int row, std::string &str,
                                      std::map<std::string, std::vector<std::pair<int, int>>> &dict) {

    std::istringstream iss(str);
    int column = 1;
    for (std::string s; iss >> s;) {


        auto tmp_pair_nums = std::make_pair(row, column);

        dict[s].push_back(tmp_pair_nums);

        column++;
    }
}