#include <iostream>
#include <algorithm>
#include <vector>
#define ldouble long double

using namespace std;

struct Point {
    double x, y;

    bool operator > (const Point &other) const {
        return x > other.x || (x == other.x && y > other.y);
    }
};

vector<Point> P, Stack;
ldouble best = 0;

bool ccw(Point A, Point B, Point C) {
    return 1.0L*A.x*(B.y - C.y)
            + 1.0L*B.x*(C.y - A.y)
            + 1.0L*C.x*(A.y - B.y) > 0;
}

void enter() {
    int n = 0; Point tmp;
    scanf("%d", &n); ++n;
    ///
    while (n--) {
        scanf("%lf%lf", &tmp.x, &tmp.y);
        P.push_back(tmp);
    }
}

void init() {
    Stack.clear();
    sort(P.begin(), P.end(), greater<Point>());
    ///
    while (P.size() > 1)
        if (P[P.size() - 1].y == P[P.size() - 2].y) P.pop_back(); else break;
    ///
    Stack.push_back(P.back()); P.pop_back();
    while (!P.empty()) {
        if (P.back().x > Stack.back().x) {
            if (P.back().x <= 0) {
                while ((int) Stack.size() >= 2 && !ccw(Stack[Stack.size()-2], Stack[Stack.size()-1], P.back()))
                    Stack.pop_back();
                Stack.push_back(P.back());
            } else {
                while (Stack.back().x != 0.0 && !ccw(Stack[Stack.size()-2], Stack[Stack.size()-1], P.back()))
                    Stack.pop_back();
                Stack.push_back(P.back());
            }
        }
        P.pop_back();
    }
    ///
    while (Stack.size() >= 2 && Stack[Stack.size()-2].y == Stack[Stack.size()-1].y) Stack.pop_back();
}

void process() {
    init();
    P.clear();
    int sz = Stack.size();
    for(int i=0; i<sz; ++i) {
        P.push_back(Stack[i]);
        Point t = Stack[i];
        t.x = -t.x;
        P.push_back(t);
    }
    init();
    ///
    for(int i=1; i<(int) Stack.size(); ++i) {
        ldouble P1 = Stack[i-1].y - Stack[i].y;
        ldouble P2 = Stack[i].x - Stack[i-1].x;
        ldouble P3 = P1*Stack[i].x + P2*Stack[i].y;
        ldouble area = (P3 / P1) * (P3 / P2);
        best = max(best, area);
    }
}

int main() {
    freopen("SAW.inp", "r", stdin);
    freopen("SAW.out", "w", stdout);
    ///
    int test = 0; scanf("%d", &test);
    while (test--) enter();
    ///
    process();
    (cout << fixed).precision(6);
    cout << best;
    return 0;
}
