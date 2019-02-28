//naive algo
#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <sstream>

using namespace std;

void spiltStringBySpace(string &str, vector<int32_t> &vec) {
    istringstream iss(str);
    for (string s; iss >> s;) {
        int32_t num = stoi(s);
        vec.push_back(num);
    }
}

void
spiltStringBySpaceForText(bool &exit, string &str, vector<pair<pair<int32_t, int32_t>, int32_t >> &vec, int32_t &row) {
    istringstream iss(str);
    int32_t x = 1;
    for (string s; iss >> s; x++) {
        int32_t num = stoi(s);
        auto xy = make_pair(row, x);
        auto tmp_pair = make_pair(xy, num);
        if (num == -1) {
            exit = true;
            break;
        }
        vec.push_back(tmp_pair);
    }
}


void NaiveSearch(std::vector<int32_t> &pattern, vector<pair<pair<int32_t, int32_t>, int32_t >> &text) {

    for (int k = 0; k < text.size() - pattern.size(); ++k) {
        int i = k;
        int j = 0;
        while (text[i].second == pattern[j] && j < pattern.size()) {
            i++;
            j++;
        }
        if (j == pattern.size()) {
            cout << text[k].first.first << ", " << text[k].first.second << endl;
        }
    }

}


int main() {

    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    vector<int32_t> pattern;

    string keys;
    getline(cin, keys);
    spiltStringBySpace(keys, pattern);

    bool exit = false;
    string vals;
    int32_t row = 1;
    vector<pair<pair<int32_t, int32_t>, int32_t >> text;
    while (getline(cin, vals)) {
        spiltStringBySpaceForText(exit, vals, text, row);
        row++;
        if (exit)
            break;
    }

    NaiveSearch(pattern, text);

    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::cout << "Search: Naive" << std::endl;
    std::cout << "Time of working ";
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>( end - start ).count();
    std::cout << " ms." << std::endl;

    return 0;
}
