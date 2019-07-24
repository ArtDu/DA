#include <iostream>
#include <vector>

using namespace std;

/*
test nums

7
30 35 15 5 10 20 25

4
10 100 5 50

*/



void print_solution(vector<vector<int>> &s, int l, int r) {
    if(l == r) {
        cout << " A" <<l << " ";
    }
    else {
        cout << "(";
        print_solution(s, l, s[l][r]);
        print_solution(s, s[l][r]+1, r);
        cout << ")";
    }
}

int matrix_chain_order(vector<int> &p, vector<vector<int>> &s) { //восходящая с восстановлением решения

    size_t n = p.size() - 1;
    vector<vector<int>> m(p.size(), std::vector<int>(p.size(), INT32_MAX));
    s.resize(p.size(), std::vector<int>(p.size()));

    for (int i = 1; i <= n; ++i) {
        m[i][i] = 0;
    }

    for (int l = 2; l <= n; ++l) { // choose a len


        for (int i = 1; i <= n - l + 1; ++i) { // расставить скобки во всех цепочках длины l
            int j = i + l - 1;
            for (int k = i; k <= j - 1; ++k) {
                // выбрать разбиение, где k номер правой границы левой части разбиения
                if(m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j] < m[i][j]) {
                    m[i][j] =  m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                    s[i][j] = k;
                }
            }
        }
    }

    return m[1][n];

}

int matrix_chain_order_recursive_aux(vector<int> &p,
                                     vector<vector<int>> &m, int l, int r) {

    if (m[l][r] >= 0) {
        return m[l][r];
    }

    int q = INT32_MAX;
    if (l == r) {
        q = 0;
    } else {
        for (int k = l; k <= r - 1; ++k) {

            q = min(q, matrix_chain_order_recursive_aux(p, m, 1, k)
                       + matrix_chain_order_recursive_aux(p, m, k + 1, r)
                       + p[0] * p[k] * p[r]);
        }
    }

    m[l][r] = q;
    return m[l][r];


}

int matrix_chain_order_recursive(vector<int> &p) {

    vector<vector<int>> m(p.size(), vector<int>(p.size(), -1));

    int n = static_cast<int>(p.size()) - 1;

    return matrix_chain_order_recursive_aux(p, m, 1, n);
}


int main() {


    int n;
    cin >> n;
    vector<int> p(n);

    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }

    vector<vector<int>> s;
    cout << matrix_chain_order(p, s) << "\n";
    print_solution(s, 1, n - 1);


    return 0;
}