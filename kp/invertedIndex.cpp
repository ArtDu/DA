//
// Created by art on 03.05.19.
//

#include <algorithm>
#include "invertedIndex.h"


/*
bool mycomp(const std::pair<int, int> &lhs, const std::pair<int, int> &rhs) {
    return lhs.first < rhs.first;
}
*/


std::vector<std::string> spiltStringBySpaceInVector(std::string &str) {
    std::vector<std::string> vec;
    std::istringstream iss(str);
    for (std::string s; iss >> s;) {
        vec.push_back(s);
    }
    return vec;
}

invertedIndex::invertedIndex(std::istream &in, int n) {
    std::string str;

    getchar();
    int row = 1;
    for (int i = 0; i < n; ++i) {
        getline(in, str);
//        allRows.insert(row);
        spiltAndUpdateDict(row, str, dict);
        row++;
    }
}

void invertedIndex::spiltAndUpdateDict(int row, std::string &str,
                                       std::map<std::string, std::set<int>> &dict) {

    std::istringstream iss(str);
    for (std::string s; iss >> s;) {

        dict[s].insert(row);

    }
}

std::set<int> invertedIndex::queryIntersection(std::set<int> &lhs, std::set<int> &rhs) {

    std::set<int> ans;
    std::set_intersection(lhs.begin(), lhs.end(),
                          rhs.begin(), rhs.end(), std::inserter(ans, ans.begin()));

    return ans;
}

std::set<int> invertedIndex::queryUnion(std::set<int> &lhs, std::set<int> &rhs) {

    std::set<int> ans;
    std::set_union(lhs.begin(), lhs.end(),
                   rhs.begin(), rhs.end(), std::inserter(ans, ans.begin()));

    return ans;
}

std::set<int> invertedIndex::queryNot(std::set<int> &word) {
    std::set<int> ans;
    std::set_difference(allRows.begin(), allRows.end(),
                   word.begin(), word.end(), std::inserter(ans, ans.begin()));

    return ans;
}

void invertedIndex::query(std::string &str) {

    std::set<int> ans;
    std::set<int>::iterator it;
    std::vector<std::string> words = spiltStringBySpaceInVector(str);


    if (words.size() == 1) {
        ans = dict[words[0]];
    } else if (words[1] == "&") {
        ans = queryIntersection(dict[words[0]], dict[words[2]]);
    } else if (words[1] == "|") {
        ans = queryUnion(dict[words[0]], dict[words[2]]);
    } else if (words[0] == "~") {
        ans = queryNot(dict[words[1]]);
    }
    else {
        std::cout << "wrong query" << std::endl;
        return;
    }

        std::cout << "Match in text: (" << (ans.size()) << " matches):\n";
    for (it = ans.begin(); it != ans.end(); ++it)
        std::cout << ' ' << *it << "\n";
    std::cout << '\n';


}