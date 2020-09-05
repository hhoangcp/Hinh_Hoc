#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#define llong long long
#define ldouble long double

using namespace std;

struct Point {
    int x, y;
} P[100006];

typedef vector<Point> V_point;
int n;

bool CW(Point A, Point B, Point C) {
    return (1LL * B.x - A.x) * (1LL * C.y - A.y) - (1LL * B.y - A.y) * (1LL * C.x - A.x) < 0;
}

bool CCW(Point A, Point B, Point C) {
    return (1LL * B.x - A.x) * (1LL * C.y - A.y) - (1LL * B.y - A.y) * (1LL * C.x - A.x) > 0;
}

V_point Find_convex(Point *arr) {
    V_point Top, Down; Top.clear(); Down.clear();
    Top.push_back(arr[1]);
    Down.push_back(arr[1]);
    ///
    for(int i=2; i<=n; ++i) {
        if (i == n || CW(arr[1], arr[i], arr[n])) {
            while (Top.size() > 1 && !CW(Top[Top.size()-2], Top[Top.size()-1], arr[i])) Top.pop_back();
            Top.push_back(arr[i]);
        }
        ///
        if (i == n || CCW(arr[1], arr[i], arr[n])) {
            while (Down.size() > 1 && !CCW(Down[Down.size()-2], Down[Down.size()-1], arr[i])) Down.pop_back();
            Down.push_back(arr[i]);
        }
    }
    ///
    V_point Convex; Convex.clear();
    for(int i=0; i<(int) Down.size(); ++i) Convex.push_back(Down[i]);
    for(int i=Top.size()-2; i>0; --i) Convex.push_back(Top[i]);
    ///
    return Convex;
}

ldouble Cal_area(V_point Convex) {
    ldouble S = 0;
    for(int i=1; i < (int) Convex.size(); ++i) S += (1LL * Convex[i-1].x - Convex[i].x) * (1LL * Convex[i-1].y + Convex[i].y);
    S += (1LL * Convex[Convex.size()-1].x - Convex[0].x) * (1LL * Convex[Convex.size()-1].y + Convex[0].y);
    return S / 2.0;
}

int main() {
    freopen("CONVEXHULL.inp", "r", stdin);
    freopen("CONVEXHULL.out", "w", stdout);
    ///
    scanf("%d", &n);
    for(int i=1; i<=n; ++i) scanf("%d%d", &P[i].x, &P[i].y);
    sort(P+1, P+n+1, [] (const Point &A, const Point &B) {
        return A.y < B.y || (A.y == B.y && A.x < B.x);
    });
    ///
    V_point Convex = Find_convex(P);
    cout << Convex.size() << "\n";
    ///
    (cout << fixed).precision(1);
    cout << Cal_area(Convex) << "\n";
    ///
    cout << defaultfloat;
    for(int i=0; i<(int) Convex.size(); ++i) cout << Convex[i].x << " " << Convex[i].y << "\n";
    ///
    return 0;
}
