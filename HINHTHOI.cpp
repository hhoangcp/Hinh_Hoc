include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define llong long long

using namespace std;

struct Point {
    int x, y;
} P[1506];

struct Segment {
    int a, b;

    bool operator < (const Segment &other) const {
        if (a != other.a) return a < other.a;
        return b < other.b;
    }

    void negative() {
        if (a >= 0) return;
        a = -a, b = -b;
    }
};

vector<Segment> A[206][206];
int n;
llong res = 0;

Segment creat(Point tmp1, Point tmp2) {
    int P1 = tmp1.y - tmp2.y;
    int P2 = tmp2.x - tmp1.x;
    ///
    int GCD = __gcd(P1, P2);
    ///
    P1 /= GCD, P2 /= GCD;
    if (P1 < 0) P1 = -P1, P2 = -P2;
    return {P1, P2};
}

int main() {
    freopen("HINHTHOI.inp", "r", stdin);
    freopen("HINHTHOI.out", "w", stdout);
    ///
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) {
        scanf("%d%d", &P[i].x, &P[i].y);
        P[i].x += 50, P[i].y += 50;
    }
    ///
    for(int i=1; i<=n; ++i)
    for(int j=i+1; j<=n; ++j)
    if (P[i].x != P[j].x || P[i].y != P[j].y) A[P[i].x+P[j].x][P[i].y+P[j].y].push_back(creat(P[i], P[j]));
    ///
    for(int i=0; i<=200; ++i)
    for(int j=0; j<=200; ++j)
    if (A[i][j].size() > 0) {
        vector<Segment> &b = A[i][j];
        int sz = b.size();
        ///
        sort(b.begin(), b.end());
        vector<int> d;
        ///
        int n_b = 0; d.push_back(1);
        for(int i=1; i<sz; ++i) {
            if (b[i-1].a != b[i].a || b[i-1].b != b[i].b) b[++n_b] = b[i], d.push_back(0);
            ++d[n_b];
        }
        ///
        sz = n_b + 1;
        while ((int) b.size() > sz) b.pop_back();
        ///
        for(int i=0; i<sz; ++i) {
            Segment Z = {-b[i].b, b[i].a};
            if (Z.a < 0) Z.negative();
            int pos = lower_bound(b.begin(), b.end(), Z) - b.begin();
            if (pos < sz && Z.a == b[pos].a && Z.b == b[pos].b) res += 1LL * d[i] * d[pos];
        }
    }
    ///
    cout << (res >> 1);
    return 0;
}
