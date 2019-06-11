//
// Created by art on 03.05.19.
//


#include "invertedIndex.h"


std::vector<std::string> splitStringBySpaceInVector(std::string &str) {
    std::vector<std::string> vec;
    std::istringstream iss(str);
    for (std::string s; iss >> s;) {
        vec.push_back(s);
    }
    return vec;
}

invertedIndex::invertedIndex(std::ifstream &in) {
    //find document

    std::string str;
    std::string nameOfDoc;

    while (getline(in, str)) {
        std::istringstream iss(str);
        iss >> str;
        if (str == "<page>") {
            in >> str;

            if (str.substr(0, 7) == "<title>") {

                if (str.substr(str.size() - 8, 8) == "</title>") {
                    nameOfDoc = str.substr(7, str.size() - 7 - 8);
                } else {
                    nameOfDoc = str.substr(7);
                    getline(in, str);
                    nameOfDoc += str.substr(0, str.size() - 8);
                }


                std::cout << nameOfDoc << "\n";
                readDocument(in, nameOfDoc);
            }
        }

    }


}

void invertedIndex::readInner(std::ifstream &in, std::string &nameOfDocument, std::string &element) {
    // delete all control text

    size_t pos;
    int32_t count;

    // ignore [[File ... ]]
    pos = element.find("[[File:");
    if (pos != std::string::npos) {
        std::string tmp = element;
        count = 1;
        // if text[File:...]
        element.erase(0,pos);

        while (true) {
            pos = tmp.find("]]"); //
            if (count == 1 && pos != std::string::npos) {
                break;
            }
            pos = tmp.find("]]");
            if (pos != std::string::npos) count--;

            in >> tmp;
            pos = tmp.find("[[");
            if (pos != std::string::npos) count++;
        }
        tmp.erase(0,pos+2);
        // if [File:...]text
        readInner(in, nameOfDocument, tmp);

    }

    // delete headers
    if (element == "="
             || element == "=="
             || element == "==="
             || element == "===="
             || element == "====="
             || element == "======"
            ) {
        return;
    }
        // delete {{ .. }}
    else if (element.size() >= 2 && element.substr(0, 2) == "{{") {
        // if one word without whitespace {...}
        if (element.substr(element.size() - 2, 2) == "}}") {
            return;
        } else {
            //
        }
    }



    // delete [[
    pos = element.find("[[");
    while (pos != std::string::npos) {
        element.erase(pos, 2);
        pos = element.find("{{");
    }

    else if (element.size() >= 2 && element.substr(0, 2) == "[[") {
        element.erase(0, 2);
        readInner(in, nameOfDocument, element);
    } else if (element.size() >= 3 && element.substr(0, 3) == "'''") {
        element.erase(0, 3);
        readInner(in, nameOfDocument, element);
    } else {
        words[element] = nameOfDocument;
    }
}

void invertedIndex::readDocument(std::ifstream &in, std::string &nameOfDocument) {

    std::string str;
    while (in >> str) {

        if (str == "<text") {
            in >> str;
            str.erase(0, 21);


        }
    }
}


std::vector<uint32_t> invertedIndex::queryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs) {
/*
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

    return ans;*/
}


void invertedIndex::query(std::string &str) {
    /*std::vector<std::string> QueryWords = splitStringBySpaceInVector(str);

    std::vector<uint32_t>::iterator it;
    std::vector<uint32_t> ans = words[QueryWords[0]].Decode();

    for (int i = 1; i < QueryWords.size(); ++i) {
        ans = queryIntersection(ans, words[QueryWords[i]].encoded);
    }

    long long i = 0, sum = 0;
    for (it = ans.begin(); it != ans.end(); ++it, ++i) {
        sum = (sum + i * (*it)) % 1000000007;
    }

    std::cout << ans.size() << " " << sum << std::endl;*/

}