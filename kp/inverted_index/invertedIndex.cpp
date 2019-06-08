//
// Created by art on 03.05.19.
//

#include <algorithm>
#include "invertedIndex.h"
#include "simple9.h"

void Enc::Push(uint32_t &numOfText) {
    if(lastNum != 0) { // not empty
        if (lastNum != numOfText) { // no repeat
            delay.push_back(numOfText - lastNum); // push delta
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

void Enc::PushDelay() {
    if (!delay.empty()) {
        simple9_encode(delay,encoded);
        delay.clear();
    }
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
    std::string str;
    for (uint32_t numOfText = 1; numOfText <= n; ++numOfText) {
        getline(std::cin, str);
        readRow(numOfText, str);
    }
    for (auto &i : words) {
        i.second.PushDelay();
    }
}

void invertedIndex::readRow(uint32_t &numOfText, std::string& str) {

    std::istringstream iss(str);
    for (std::string s; iss >> s;) {

        words[s].Push(numOfText);

    }
}


std::vector<uint32_t> invertedIndex::queryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs) {

    std::vector<uint32_t> ans;

    int i = 0; // index in not decoded vector
    int j = 0; // index in encoded vector
    int k = 0; // index in selector

    uint32_t lastElement = 0;
    uint32_t element;
    while ( i < lhs.size() && j < rhs.size()) {
        uint32_t selector = rhs[j];

        uint32_t typeSelector = selector & SELECTOR_MASK;

        uint32_t  countOfElements = selectors[typeSelector].nitems; // count of elements in one selector

        uint32_t shift = selectors[typeSelector].nbits;

        uint32_t mask = (1u << selectors[typeSelector].nbits) - 1;

        selector = selector >> SELECTOR_BITS; // skip control bits

        k = 0;
        element = (selector & mask);
        if (lastElement != 0) {
            lastElement += element;
        } else {
            lastElement = element;
        }
        while ( k < countOfElements && i < lhs.size() ) {

            if (element) {

                if (lastElement == lhs[i]) {
                    ans.push_back(lastElement);
                    i++;
                    k++;
                    selector = selector >> shift;
                    element = (selector & mask);
                    lastElement += element;
                }
                else if (lhs[i] > lastElement) {
                    k++;
                    selector = selector >> shift;
                    element = (selector & mask);
                    lastElement += element;
                }
                else {
                    i++;
                }

            }
            else {
                k++;
                selector = selector >> shift;
            }
        }
        j++;

    }

    return ans;
}


void invertedIndex::query(std::string &str) {
    std::vector<std::string> QueryWords = splitStringBySpaceInVector(str);

    std::vector<uint32_t>::iterator it;
    std::vector<uint32_t> ans = words[QueryWords[0]].Decode();

    for (int i = 1; i < QueryWords.size(); ++i) {
        ans = queryIntersection(ans, words[QueryWords[i]].encoded);
    }

    long long i = 0, sum = 0;
    for (it = ans.begin(); it != ans.end(); ++it, ++i) {
        sum = (sum + i * (*it)) % 1000000007;
    }

    std::cout << ans.size() << " " << sum << std::endl;

}