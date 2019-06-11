//
// Created by art on 03.05.19.
//

#ifndef KP_INVERTEDINDEX_H
#define KP_INVERTEDINDEX_H

#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>


class invertedIndex {
public:


    invertedIndex(std::ifstream &in);

    void readDocument(std::ifstream &in, std::string &nameOfDocument);
    void readInner(std::ifstream &in, std::string &nameOfDocument, std::string &element);

    void query(std::string &str);

    // intersection between normal and encoded vector
    std::vector<uint32_t> queryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs);

private:
    // <word> <text's name>
    std::unordered_map<std::string, std::string> words;


};


#endif //KP_INVERTEDINDEX_H
