//
// Created by art on 03.05.19.
//

#ifndef KP_INVERTEDINDEX_H
#define KP_INVERTEDINDEX_H
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

class invertedIndex {
public:


    invertedIndex(std::istream& in);
    void spiltAndUpdateDict(int row, std::string &str, std::map<std::string, std::vector<std::pair<int, int>>> &dict);
    std::map<std::string, std::vector<std::pair<int, int>>> dict;
private:

};


#endif //KP_INVERTEDINDEX_H
