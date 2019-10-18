#include <iostream>
#include <vector>
#include <complex>

using namespace std;

typedef complex<double> cd;

vector<cd> fft(vector<cd> &a) {

    int n = a.size();
    if (n == 1) return a;

    vector<cd> w(n);

    for (int k = 0; k < n; ++k) {
        double alpha = (2 * M_PI * k) / n;
        w[k] = cd(round(cos(alpha)), round(sin(alpha)));
    }

    vector<cd> a_0(n / 2), a_1(n / 2);

    for (int i = 0; i < n / 2; ++i) {
        a_0[i] = a[i * 2];
        a_1[i] = a[i * 2 + 1];
    }


    vector<cd> y_0 = fft(a_0);
    vector<cd> y_1 = fft(a_1);

    vector<cd> y(n);
    for (int k = 0; k < n / 2; ++k) {
        y[k] = y_0[k] + w[k] * y_1[k];
        y[k + n / 2] = y_0[k] - w[k] * y_1[k];
    }

    return y;
}

vector<cd> fft_interpolation(vector<cd> &y) {
    int n = y.size();
    if (n == 1) return vector<cd>(1, y[0]);

    //cout << "w:\n";
    vector<cd> w(n);
    for (int k = 0; k < n; ++k) {
        double alpha = -(2 * M_PI * k) / n;
        w[k] = cd(round(cos(alpha)), round(sin(alpha)));
        //cout << w[k] << " ";
    }
    //cout << "\n";
    vector<cd> y_0(n / 2), y_1(n / 2);

    for (int i = 0; i < n / 2; ++i) {
        y_0[i] = y[i * 2];     // even
        y_1[i] = y[i * 2 + 1]; // odd
    }

    vector<cd> a_0 = fft_interpolation(y_0);
    vector<cd> a_1 = fft_interpolation(y_1);

    vector<cd> a(n);
    for (int k = 0; k < n / 2; ++k) {
        a[k] = a_0[k] + a_1[k] * w[k] ;
        a[k + (n / 2)] = a_0[k] - a_1[k] * w[k] ;
    }

    return a;
}


int main() {

    vector<cd> a{1, 2, 3, 4};
    vector<cd> b = fft(a);
    int n = 4;
    for (int i = 0; i < n; i++)
        cout << b[i] << endl;

    vector<cd> a_ans = fft_interpolation(b);
    for (int i = 0; i < n; i++)
        cout << a_ans[i].real() / n << endl;

    return 0;

}
