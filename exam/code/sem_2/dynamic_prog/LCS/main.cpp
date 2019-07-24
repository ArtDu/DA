#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*test

abcbdab
bdcaba

 */


string lcs_aux(string &s1, string &s2, vector<vector<string>> &c,
        int i, int j) {


    if(i == -1 || j == -1) {
        return "";
    }

    if(c[i][j] != "") {
        return c[i][j];
    }


    string ans;

    if(s1[i] == s2[j]){
        ans = (lcs_aux(s1, s2, c, i - 1, j - 1) + s1[i]);
    }
    else {
        string fst = lcs_aux(s1, s2, c, i - 1, j);
        string snd = lcs_aux(s1, s2, c, i, j - 1);
        if (fst.size() >= snd.size())
            ans = fst;
        else
            ans = snd;
    }
    c[i][j] = ans;
    return ans;

}

string lcs(string &s1, string &s2) {

    vector<vector<string>> c(s1.size(), vector<string>(s2.size(), ""));

    int i = s1.size();
    int j = s2.size();
    return lcs_aux(s1, s2, c, i - 1, j - 1);
}

int main() {


    string s1, s2;
    cin >> s1 >> s2;

    cout << lcs(s1, s2) << "\n";

    return 0;
}