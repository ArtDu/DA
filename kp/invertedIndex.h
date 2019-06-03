//
// Created by art on 03.05.19.
//

#ifndef KP_INVERTEDINDEX_H
#define KP_INVERTEDINDEX_H

#include <iostream>
#include <unordered_map>

#include <string>
#include <vector>
#include <sstream>


class Enc{
public:
    Enc() = default;
    void Push(uint32_t &numOfText);
    std::vector<uint32_t > Decode();
private:
    std::vector<uint32_t > encoded;
    std::vector<uint32_t > delay;
    uint32_t lastNum = 0;
};

class invertedIndex {
public:


    invertedIndex(std::istream &in, uint32_t &n);

    void readRow(uint32_t &numOfText, std::string &str);

    void query(std::string &str);

    std::vector<uint32_t> queryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs);

private:
    std::unordered_map<std::string, Enc> words;


};


#endif //KP_INVERTEDINDEX_H
