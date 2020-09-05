#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#define ldouble long double

using namespace std;

struct Point {
    double x, y;
    ///
    bool operator < (const Point &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
    ///
    Point operator + (const Point &other) const {
        return {x + other.x, y + other.y};
    }
    ///
    Point operator - (const Point &other) const {
        return {x - other.x, y - other.y};
    }
} P[100006], Q[100006];

int n, m;

void Again(int sz, Point *arr) {
    vector<Point> tmp(arr+1, arr+sz+1);
    ///
    int min_pos = 0;
    for(int i=1; i<=sz; ++i)
    if (min_pos == 0 || arr[i] < arr[min_pos]) min_pos = i;
    ///
    for(int i=min_pos; i <= sz; ++i) arr[i-min_pos+1] = tmp[i-1];
    for(int i=1; i<min_pos; ++i) arr[i + sz - min_pos + 1] = tmp[i-1];
    arr[sz+1] = arr[1];
}

void enter() {
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%lf%lf", &P[i].x, &P[i].y);
    ///
    scanf("%d", &m);
    for(int i=1; i<=m; ++i) {
        scanf("%lf%lf", &Q[i].x, &Q[i].y);
        Q[i].x = -Q[i].x;
        Q[i].y = -Q[i].y;
    }
    ///
    Again(n, P);
    Again(m, Q);
}

int minkowski;
Point Minkowski[200006];

ldouble area(Point A, Point B, Point C) {
    return (1.0L * B.x - A.x) * (1.0L * C.y - A.y) - (1.0L * C.x - A.x) * (1.0L * B.y - A.y);
}

void init() {
    minkowski = 0;
    Minkowski[++minkowski] = P[1] + Q[1];
    ///
    int cur_P = 1, cur_Q = 1;
    while (cur_P <= n && cur_Q <= m)
        if (area(P[cur_P+1] - P[cur_P], Q[cur_Q+1] - Q[cur_Q], {0.0, 0.0}) >= 0)
            Minkowski[++minkowski] = P[++cur_P] + Q[cur_Q];
        else Minkowski[++minkowski] = P[cur_P] + Q[++cur_Q];
    ///
    while (cur_P <= n) Minkowski[++minkowski] = P[++cur_P] + Q[cur_Q];
    while (cur_Q <= m) Minkowski[++minkowski] = P[cur_P] + Q[++cur_Q];
}

void process() {
    ldouble area_polygon = 0, area_point = 0;
    for(int i=1; i<minkowski; ++i) {
        area_polygon += (1.0L * Minkowski[i+1].x - Minkowski[i].x) * (1.0L * Minkowski[i+1].y + Minkowski[i].y);
        ldouble S = abs(area(Minkowski[i], Minkowski[i+1], {0, 0}));
        if (S == 0) {
            cout << "NO\n";
            return;
        }
        ///
        area_point += S;
    }
    ///
    area_polygon = abs(area_polygon);
    if (area_point == area_polygon) cout << "YES\n"; else cout << "NO\n";
}

int main() {
    freopen("NKLAND.inp", "r", stdin);
    freopen("NKLAND.out", "w", stdout);
    ///
    int test = 0; scanf("%d", &test);
    while (test--) {
        enter();
        init();
        process();
    }
    return 0;
}
