// CPP program to implement run length encoding
#include <bits/stdc++.h>
using namespace std;

void printRLE(string str)
{
    int n = str.length();
    for (int i = 0; i < n; i++) {

        char c = str[i];
        cout << c;
        int count = 1;
        int j;
        for ( j = i + 1; j < n; ++j) {
            if (str[j] == c) {
                count++;
            }
            else break;
        }
        i = j;
        cout << count;
    }
}

int main()
{
    string str = "wwwwaaadexxxxxxywww";
    printRLE(str);
    return 0;
}
