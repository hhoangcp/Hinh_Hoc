#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

int n;
double x[2006], y[2006];
llong res = 0;

void process(int p) {
    vector<double> A(p);
    ///
    for(int i=0; i<p; ++i) {
        double Dy = y[i] - y[p];
        if (Dy == 0) A[i] = 1e16;
        else A[i] = (x[i] - x[p]) / Dy;
    }
    ///
    sort(A.begin(), A.end());
    for(int i=0, num = 0; i<p; ++i) {
        ++num;
        if (i == p-1 || A[i] != A[i+1]) {
            res += num * (num - 1) / 2;
            num = 0;
        }
    }
}

int main() {
    freopen("QBPOINT.inp", "r", stdin);
    freopen("QBPOINT.out", "w", stdout);
    ///
    scanf("%d", &n);
    for(int i=0; i<n; ++i) {
        scanf("%lf%lf", &x[i], &y[i]);
        if (i > 1) process(i);
    }
    cout << res;
    return 0;
}
