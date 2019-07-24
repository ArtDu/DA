#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
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

void R_function(const string &pattern, map<char, int64_t> &R) {
    for (int64_t i = pattern.size() - 1; i > 0; --i) {
        R[pattern[i]] = max(R[pattern[i]], (int64_t) i);
    }
}

void Z_algo(const vector<int32_t> &pattern, vector<int32_t> &z) {
    size_t pattern_size = pattern.size();
    z.resize(pattern_size, 0);
    int32_t r = 0, l = 0;
    for (int k = 1; k < pattern_size; ++k) {
        if (k > r) {
            int32_t i = 0, j = k;
            while (pattern[i] == pattern[j]) {
                i++;
                j++;
            }
            z[k] = i;
            if (z[k] > 0) {
                r = k + z[k] - 1;
                l = k;
            }
        } else {
            int32_t k_ = k - l;
            if (z[k_] < r - k + 1) {
                z[k] = z[k_];
            } else {
                int32_t i = r - k + 1, j = r + 1;
                while (pattern[i] == pattern[j]) {
                    i++;
                    j++;
                }
                z[k] = j - k;
                r = j - 1;
                l = k;
            }
        }
    }
}

void N_func(vector<int32_t> &z, vector<int32_t> &N) {
    size_t z_size = z.size();
    N.resize(z_size, 0);
    for (int j = 1; j < z_size; ++j) {
        N[j] = z[z_size - j - 1];
    }
}

void L_func(vector<int32_t> &N, vector<int32_t> &L, vector<int32_t> &l) {
    size_t N_size = N.size();
    L.resize(N_size, 0);
    int32_t l_max = 0;
    for (int j = 0; j < N_size - 1; ++j) {
        int32_t i = (int) (N_size) - N[j];
        L[i] = j;
        if (N[j] == j + 1) {
            l_max = max(l_max, j);
        }
    }
    l.resize(N_size, l_max);
}

void boyer_moore(vector<int32_t> &L, vector<int32_t> &l, vector<int32_t> &pattern, vector<pair<pair<int32_t, int32_t>, int32_t >> text) {
    int32_t count = 0;
    int32_t n = (int) pattern.size();
    int32_t m = (int) text.size();
    int32_t k = n - 1;
    while (k < m) {
        int32_t i = n - 1;
        int32_t h = k;
        while (i >= 0 && pattern[i] == text[h].second) {
            i--;
            h--;
        }
        if (i == -1) {
            cout << text[h+1].first.first << ", " << text[h+1].first.second << endl;
            k = k + (n - 1) - l[2];
            count++;
        } else if (i == n - 1) {
            k++;
        } else {
            if (L[i + 1] == 0) {
                k = k + (n - 1) - l[i + 1];
            } else {
                k = k + (n - 1) - L[i + 1];
            }
        }
    }


}

int main() {
    vector<int32_t> pattern;
    vector<int32_t> z;
    vector<int32_t> N;
    vector<int32_t> L;
    vector<int32_t> l;

    string keys;
    getline(cin, keys);
    spiltStringBySpace(keys, pattern);

    vector<int32_t> pattern_rev(pattern);
    reverse(pattern_rev.begin(), pattern_rev.end());
    Z_algo(pattern_rev, z);

    N_func(z, N);
    L_func(N, L, l);

    string vals;
    bool exit = false;
    int32_t num;
    int32_t row = 1;
    vector<pair<pair<int32_t, int32_t>, int32_t >> text;
    while (getline(cin, vals)) {
        spiltStringBySpaceForText(exit, vals, text, row);
        row++;
        if (exit)
            break;
    }

    boyer_moore(L, l, pattern, text);

    return 0;
}

//1 1 2 2 1 2 2 3 4 21 1 1 1 2