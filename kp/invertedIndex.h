//
// Created by art on 03.05.19.
//

#ifndef KP_INVERTEDINDEX_H
#define KP_INVERTEDINDEX_H
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <sstream>

class invertedIndex {
public:


    void query(std::string &str);
    std::set<int> queryIntersection(std::set<int> &lhs, std::set<int> &rhs);
    std::set<int> queryUnion(std::set<int> &lhs, std::set<int> &rhs);
    std::set<int> queryNot(std::set<int> &word);
    invertedIndex(std::istream& in, int n);
    void spiltAndUpdateDict(int row, std::string &str, std::map<std::string, std::set<int>> &dict);
private:
    std::map<std::string, std::set<int>> dict;
    std::set<int> allRows;

};


#endif //KP_INVERTEDINDEX_H
