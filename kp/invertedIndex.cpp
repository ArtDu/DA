//
// Created by art on 03.05.19.
//

#include <algorithm>
#include "invertedIndex.h"
#include "simple9.h"


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
        spiltAndUpdateDict(row, str, dict);
        row++;
    }
    compress();
    dict.clear();
}

void invertedIndex::spiltAndUpdateDict(int row, std::string &str,
                                       std::map<std::string, std::set<int>> &dict) {

    std::istringstream iss(str);
    for (std::string s; iss >> s;) {

        dict[s].insert(row);

    }
}



void invertedIndex::compress() {
    for (auto word : dict) {
        compressDict[word.first] = simple9_encode(word.second);
    }
}


std::vector<uint32_t > invertedIndex::queryIntersection(std::vector<uint32_t > &lhs, std::vector<uint32_t > &rhs) {

    std::vector<uint32_t > ans;
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

std::vector<uint32_t > invertedIndex::fromCompressToNormal(std::vector<uint32_t> &vec) {
    std::vector<uint32_t > ans;
    for (auto selector : vec) {
        int32_t typeSelector = selector & SELECTOR_MASK;
        uint32_t shift = selectors[typeSelector].nbits;
        uint32_t element;
        int32_t countOfElements = selectors[typeSelector].nitems;
        selector = selector >> SELECTOR_BITS;
        for (int i = 0; i < countOfElements; ++i) {
            element = ( selector & binInDec[typeSelector].decItem );
            if(element) {
                ans.push_back(element);
            }
            selector = selector >> shift;
        }
    }
    return ans;
}


void invertedIndex::query(std::string &str) {
    std::vector<std::string> words = spiltStringBySpaceInVector(str);

    std::vector<uint32_t >::iterator it;
    std::vector<uint32_t > ans = fromCompressToNormal(compressDict[words[0]]);

    for(int i = 1; i < words.size(); ++i) {
        std::vector<uint32_t > tmpVector = fromCompressToNormal(compressDict[words[i]]);
        ans = queryIntersection(ans, tmpVector);
    }


    long long i = 0, sum = 0;
    for (it = ans.begin(); it != ans.end(); ++it, ++i) {
        sum += ((*it) * i) ;
    }

    std::cout << ans.size() << " " << sum % (1000000000 + 7);
    std::cout << '\n';


}