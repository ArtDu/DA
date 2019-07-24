

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

    vector<vector<string >> patterns;

    while(true) {
        vector<string> pattern;
        string str;
        getline(cin, str);

        if(str=="")
            break;


        splitStringInVector(str, pattern);
        patterns.push_back(pattern);
    }

    KeysTree tree;
    tree.BuildTree(patterns);


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

    tree.Search(text);

    return 0;
}
