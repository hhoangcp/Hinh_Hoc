#include <cstdio>
#include <iostream>
#include <algorithm>
#define llong long long

using namespace std;

struct Point {
    int x, y;
} P[100006];

int n, m;

llong get_area(Point A, Point B, Point C) {
    return (1LL * B.x - A.x) * (1LL * C.y - A.y) - (1LL * B.y - A.y) * (1LL * C.x - A.x);
}

int main() {
    freopen("METERAIN.inp", "r", stdin);
    freopen("METERAIN.out", "w", stdout);
    ///
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d%d", &P[i].x, &P[i].y);
    P[n+1] = P[1], P[n+2] = P[2];
    for(int i=1; i<=n; ++i)
    if (get_area(P[i], P[i+1], P[i+2]) < 0) break;
    else if (get_area(P[i], P[i+1], P[i+2]) > 0) {
        reverse(P+1, P+n+1);
        break;
    }
    ///
    scanf("%d", &m);
    while (m--) {
        Point cur; scanf("%d%d", &cur.x, &cur.y);
        ///
        if (get_area(P[n], P[1], cur) >= 0 || get_area(P[1], P[2], cur) >= 0) {
            cout << "NO\n";
            continue;
        }
        ///
        int l = 2, r = n;
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            if (get_area(P[1], P[mid], cur) <= 0) l = mid; else r = mid;
        }
        ///
        if (l == r) {
            if (get_area(P[l-1], P[l], cur) < 0 && get_area(P[r], P[r+1], cur) < 0) cout << "YES\n";
            else cout << "NO\n";
        } else {
            if (get_area(P[l], P[r], cur) < 0) cout << "YES\n";
            else cout << "NO\n";
        }
    }
    return 0;
}
