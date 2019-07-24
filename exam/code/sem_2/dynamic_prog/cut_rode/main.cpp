#include <iostream>
#include <vector>

using namespace std;

/*test numbers

10
1 5 8 9 10 17 17 20 24 30
 */

int cut_rode(vector<int> &p, size_t n) { // without memoization

    if (n == 0)
        return 0;

    int q = -1;
    for (int i = 1; i <= n; ++i) {
        q = max(q, p[i] + cut_rode(p, n - i));
    }


    return q;
}



int mem_cut_rode_aux(vector<int> &p, size_t n, vector<int> &r) {

    if (r[n] >= 0)
        return r[n];

    int q = -1;
    if (n == 0) {
        q = 0;
    } else {
        for (int i = 1; i <= n; ++i) { // сделать выбор
            q = max(q, p[i] + mem_cut_rode_aux(p, n - i, r));
        }
    }

    r[n] = q;
    return r[n];
}
int mem_cut_rode(vector<int> &p, size_t n) { //нисходящая
    static vector<int> r(p.size(), -1);

    return mem_cut_rode_aux(p, n, r);

}



int mem_cut_rode_to_up(vector<int> &p, vector<int> &s, size_t n) { // восходящая с востановлением решения

    vector<int> r(p.size(), -1);

    s.resize(n + 1, -1); // первый разрез
    int q;

    r[0] = 0;
    for (int l = 1; l <= n; ++l) { // выбрать длину

        q = -1;
        for (int j = 1; j <= l; ++j) { // сделать выбор
            if (p[j] + r[l-j] > q) {
                s[l] = j;
                q = p[j] + r[l-j];
            }
        }
        r[l] = q;
    }
    return r[n];
}




int main() {


    size_t n;
    cin >> n;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
    }


    while (cin >> n) {
        vector<int> s;
        cout << mem_cut_rode_to_up(p, s, n) << "\n";
        while(n > 0) {
            cout << s[n] << " ";
            n = n - s[n];
        }
        cout << "\n";
    }
    return 0;
}