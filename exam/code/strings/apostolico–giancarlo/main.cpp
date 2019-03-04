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

void Z_algo(vector<int32_t> &pattern, vector<int32_t> &z) {
    size_t P_size = pattern.size();
    z.resize(P_size, 0);
    int32_t r = 0, l = 0;
    for (int k = 1; k < P_size; ++k) {

        if (k > r) {
            int32_t i = 0, j = k;
            while (pattern[i] == pattern[j]) {
                i++;
                j++;
            }
            z[k] = i;
            if (z[k] > 0) {
                r = j - 1;
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
                z[k] = i;
                r = j - 1;
                l = k;
            }
        }
    }
}

void N_func(vector<int32_t> &z, vector<int32_t> &N) {
    size_t z_size = z.size();
    N.resize(z_size, 0);
    for (int i = 1; i < z_size; ++i) {
        N[i] = z[(z_size - 1) - i];
    }
}

void L_func(vector<int32_t> &N, vector<int32_t> &L, vector<int32_t> &l) {
    size_t N_size = N.size();
    L.resize(N_size, 0);
    int32_t max_l = 0;
    for (int j = 0; j < N_size - 1; ++j) {
        int32_t i = (int) (N_size) - N[j];
        L[i] = j;
        if (N[j] == j + 1) {
            max_l = max(max_l, N[j]);
        }
    }
    l.resize(N_size, max_l);
}

void apostolico_giancarlo(vector<int32_t> &M, vector<int32_t> &N, vector<int32_t> &L, vector<int32_t> &l,
                          vector<int32_t> &pattern, vector<pair<pair<int32_t, int32_t>, int32_t >> &text) {
    auto n = (int) pattern.size();
    auto m = (int) text.size();
    M.resize(text.size(), 0);
    auto j = n - 1;
    while (j < m) {
        int32_t h = j;
        int32_t i = n - 1;

        while (true) {
            if (M[h] == 0 || N[i] == 0) {

                if (text[h].second == pattern[i] && i == 0) {
                    cout << text[h].first.first << ", " << text[h].first.second << endl;
                    M[j] = n - 1;
                    j = j + (n - 1) - l[2];
                    break;
                } else if (text[h].second == pattern[i] && i > 0) {
                    h--;
                    i--;
                    continue;
                } else {
                    M[j] = j - h;
                    if (i == n - 1) {
                        j++;
                    } else {
                        if (L[i + 1] == 0) {
                            j = j + (n - 1) - l[i + 1];
                        } else {
                            j = j + (n - 1) - L[i + 1];
                        }
                    }
                    break;
                }
            } else if (M[h] < N[i]) {
                i = i - M[h];
                h = h - M[h];
                continue;
            } else if (M[h] >= N[i] && N[i] == i + 1) {
                cout << text[j - n ].first.first << ", " << text[j - n].first.second << endl;
                M[j] = j - h;
                j = j + (n - 1) - l[2];
                break;
            } else if (M[h] > N[i] && N[i] < i + 1) {
                M[j] = j - h;
                if (i - N[i] == n - 1) {
                    j++;
                } else {
                    if (L[i - N[i] + 1] == 0) {
                        j = j + (n - 1) - l[i - N[i] + 1];
                    } else {
                        j = j + (n - 1) - L[i - N[i] + 1];
                    }
                }
                break;
            } else if (M[h] == N[i] && N[i] < i + 1 && N[i] > 0) {
                i = i - M[h];
                h = h - M[h];
            }
        }

    }
}

int main() {
    vector<int32_t> pattern;
    vector<int32_t> z;
    vector<int32_t> N;
    vector<int32_t> M;
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

    apostolico_giancarlo(M, N, L, l, pattern, text);

    return 0;
}

//1 1 2 2 1 2 2 3 4 21 1 1 1 2