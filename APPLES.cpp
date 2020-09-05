#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

struct Data {
    int x, y, pos;

    bool operator < (const Data &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
} P[1000006];

int n;

int main() {
    freopen("APPLES.inp", "r", stdin);
    freopen("APPLES.out", "w", stdout);
    ///
    scanf("%d", &n);
    int pos = 0;
    for(int i=1; i<=n; ++i) {
        scanf("%d%d", &P[i].x, &P[i].y);
        if (pos == 0 || P[i] < P[pos]) pos = i;
        P[i].pos = i;
    }
    ///
    swap(P[pos], P[1]);
    cout << pos << " ";
    ///
    sort(P+2, P+n+1, [] (const Data &A, const Data &B) {
        return (1LL * A.x - P[1].x) * (1LL * B.y - P[1].y) - (1LL * A.y - P[1].y) * (1LL * B.x - P[1].x) < 0;
    });
    ///
    cout << P[n / 2 + 1].pos;
    return 0;
