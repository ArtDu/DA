#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

void splitStringInVector(string &str, vector<int32_t> &vec) {
    istringstream iss(str);
    string s;
    while (iss >> s) {
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

void classicSP(vector<int32_t> &P, vector<int32_t> &sp) {
    size_t n = P.size();
    sp.resize(n, 0);

    for (int k = 0; k < n - 1; ++k) {
        int32_t x = P[k + 1];     // end of suffix new suffix k + 1
        int32_t v = sp[k] - 1;    // P[0...v] == P[k - (v+1)...k]
        // (v + 1) - count of matched symbols
        //    v    - end of last prefix
        while (P[v + 1] != x && v != -1) {
            v = sp[v] - 1;
        }
        if (P[v + 1] == x) {
            sp[k + 1] = (v + 1) + 1;
        } else {
            sp[k + 1] = 0;
        }
    }

}

void strongSP(vector<int32_t> &sp, vector<int32_t> &P, vector<int32_t> &spStrong) {
    size_t spSize = sp.size();
    spStrong.resize(spSize + 1, 0);
    spStrong[spSize] = -1;

    for (int i = 1; i < spSize; ++i) {
        int32_t v = sp[i] - 1;
        if (P[i + 1] != P[v + 1]) {
            spStrong[i] = v + 1;
        } else {
            spStrong[i] = spStrong[v];
        }
    }

}

void failureFunc(vector<int32_t> &sp, vector<int32_t> &F) {
    size_t spStrongSize = sp.size();
    F.resize(spStrongSize + 1, 0);
    for (int i = 1; i < spStrongSize + 1; ++i) {
        F[i] = sp[i - 1];
    }
}

void kmp(vector<pair<pair<int32_t, int32_t>, int32_t >> &T, vector<int32_t> &P, vector<int32_t> &F) {
    size_t n = P.size();
    size_t m = T.size();
    int32_t c = 0;
    int32_t p = 0;
    while (c < m - n + p) {

        while (T[c].second == P[p] && p < n) {
            c++;
            p++;
        }
        if (p == n) {
            cout << T[c - n].first.first << ", " << T[c - n].first.second << endl;
        }
        if (p == 0)
            c = c + 1;
        p = F[p];
    }


}

int main() {

    vector<int32_t> pattern;
    vector<int32_t> sp;
    vector<int32_t> spStrong;
    vector<int32_t> F;

    string numsInPattern;
    getline(cin, numsInPattern);
    splitStringInVector(numsInPattern, pattern);

    classicSP(pattern, sp);
    strongSP(sp, pattern, spStrong);
    spStrong.erase(spStrong.end() - 1);

    failureFunc(sp, F);

    string vals;
    bool exit = false;
    int32_t row = 1;
    vector<pair<pair<int32_t, int32_t>, int32_t >> text;
    while (getline(cin, vals)) {
        spiltStringBySpaceForText(exit, vals, text, row);
        row++;
        if (exit)
            break;
    }

    kmp(text, pattern, F);

    return 0;
}
