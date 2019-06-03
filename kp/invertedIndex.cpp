//
// Created by art on 03.05.19.
//

#include <algorithm>
#include "invertedIndex.h"
#include "simple9.h"

void Enc::Push(uint32_t &numOfText) {
    if(lastNum != 0) {
        if (lastNum != numOfText) {
            delay.push_back(numOfText - lastNum);
            lastNum = numOfText;
        }
        else {
            return;
        }
    }
    else {
        delay.push_back(numOfText);
        lastNum = numOfText;
    }


    if(delay.size() == 28) {
        simple9_encode(delay, encoded);
        delay.clear();
    }
}

std::vector<uint32_t > Enc::Decode() {
    if(!delay.empty()) {
        simple9_encode(delay, encoded);
        delay.clear();
    }
    return simple9_decode(encoded);
}


std::vector<std::string> splitStringBySpaceInVector(std::string &str) {
    std::vector<std::string> vec;
    std::istringstream iss(str);
    for (std::string s; iss >> s;) {
        vec.push_back(s);
    }
    return vec;
}

invertedIndex::invertedIndex(std::istream &in, uint32_t &n) {
    getchar(); //\n
    for (uint32_t numOfText = 1; numOfText <= n; ++numOfText) {
        readRow(numOfText);
    }
}

void invertedIndex::readRow(uint32_t numOfText) {

    std::string str;
    char c;
    while(true) {
        c = (char)getchar();
        if (c == ' ') {
            words[str].Push(numOfText);
            str.clear();
        }
        else if (c == '\n') {
            words[str].Push(numOfText);
            break;
        }
        else {
            str += c;
        }
    }





}


std::vector<uint32_t> invertedIndex::queryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs) {

    std::vector<uint32_t> ans;
    std::set_intersection(lhs.begin(), lhs.end(),
                          rhs.begin(), rhs.end(), std::back_inserter(ans));

    return ans;
}


void invertedIndex::query(std::string &str) {
    std::vector<std::string> QueryWords = splitStringBySpaceInVector(str);

    std::vector<uint32_t>::iterator it;
    std::vector<uint32_t> ans = words[QueryWords[0]].Decode();

    for (int i = 1; i < QueryWords.size(); ++i) {
        std::vector<uint32_t> tmpVector = words[QueryWords[i]].Decode();
        ans = queryIntersection(ans, tmpVector);
    }


    long long i = 0, sum = 0;
    for (it = ans.begin(); it != ans.end(); ++it, ++i) {
        sum = (sum + i * (*it)) % 1000000007;
    }

    printf("%lu %lld\n", ans.size(), sum);

}