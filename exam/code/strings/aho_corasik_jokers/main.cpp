

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

#include "KeysTree.h"

using namespace std;

void splitStringInVector(string &str, vector<string> &vec) {
    istringstream iss(str);
    string s;
    while (iss >> s) {
        vec.push_back(s);
    }
}

void
spiltStringBySpaceForText(bool &exit, string &str, vector<pair<pair<int32_t, int32_t>, string >> &vec, int32_t &row) {
    istringstream iss(str);
    int32_t x = 1;
    for (string s; iss >> s; x++) {

        auto xy = make_pair(row, x);
        auto tmp_pair = make_pair(xy, s);
        if (s == "-") {
            exit = true;
            break;
        }
        vec.push_back(tmp_pair);
    }
}


int main() {

    vector<pair<vector<string>, int32_t >> patterns;
    vector<string> pattern;

    string str;
    getline(cin, str);
    splitStringInVector(str, pattern);


    int32_t pos = 0;
    int i;
    for (i = 0; i < pattern.size(); ++i) {

        if (pattern[i] == "?") {
            if (i != 0) {
                vector<string> patternTmp(pattern.begin() + pos, pattern.begin() + i);
                auto tmpPair = make_pair(patternTmp, pos);
                patterns.push_back(tmpPair);
            }
            while (pattern[i] == "?" && i < pattern.size()) {
                i++;
            }
            pos = i;
        }

    }
    if (pos != i) {
        vector<string> patternTmp(pattern.begin() + pos, pattern.begin() + i);
        auto tmpPair = make_pair(patternTmp, pos);
        patterns.push_back(tmpPair);
    }

    KeysTree* tree = new KeysTree;
    tree->BuildTree(patterns);


    string vals;
    bool exit = false;
    int32_t row = 1;
    vector<pair<pair<int32_t, int32_t>, string >> text;
    while (getline(cin, vals)) {
        spiltStringBySpaceForText(exit, vals, text, row);
        row++;
        if (exit)
            break;
    }

    tree->Search(text);

    return 0;
}
