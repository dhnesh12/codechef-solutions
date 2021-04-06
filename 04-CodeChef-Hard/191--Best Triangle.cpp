
#include <bits/stdc++.h>

using namespace std;
#define PB push_back
#define MP make_pair
#define LL long long
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define REP(i, n) FOR(i, 0, (int)(n)-1)
#define RE(i, n) FOR(i, 1, n)
#define R(i, n) REP(i, n)
#define FI first
#define SE second
#define st FI
#define nd SE
#define ALL(x) (x).begin(), (x).end()
#define SZ(x) ((int)(x).size())
#define VI vector<int>
#define PII pair<int, int>
#define LD long double
template<class T>inline void umax(T &x, T y) {x = x < y ? y : x;}

struct Point {
    int x, y;
    Point operator+(const Point &P) const { return {x + P.x, y + P.y}; }
    Point operator-(const Point &P) const { return {x - P.x, y - P.y}; }
    LL crossProd(const Point &P) const { return (LL)x * P.y - (LL)y * P.x; }
    bool operator<(const Point &P) const { /*return tie(x, y) < tie(P.x, P.y);*/
        return x < P.x || (x == P.x && y < P.y);
    }
};
const int MaxN = 3600;
int N;
LL K;
int curOrder[MaxN];
int pointRank[MaxN];
Point pts[MaxN];
vector<PII> swapOrder;
LL maxArea;

LL twoAreas(int i, int j, int k) {
    return abs((pts[k] - pts[i]).crossProd(pts[j] - pts[i]));
}

int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << fixed << setprecision(11);
    cerr << fixed << setprecision(6);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> pts[i].x >> pts[i].y;
    }
    iota(curOrder, curOrder + N, 0);
    sort(curOrder, curOrder + N, [&](int lhs, int rhs) { return pts[lhs] < pts[rhs]; });
    for (int i = 0; i < N; i++) {
        pointRank[curOrder[i]] = i;
    }
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            swapOrder.emplace_back(curOrder[i], curOrder[j]);
        }
    }
    sort(ALL(swapOrder), [&](const PII &lhs, const PII &rhs) {
        Point lvec = pts[lhs.nd] - pts[lhs.st], rvec = pts[rhs.nd] - pts[rhs.st];
        return lvec.crossProd(rvec) > 0;
    });
    for (auto &swapInfo : swapOrder) {
        int u = swapInfo.st, v = swapInfo.nd;
        assert(pointRank[u] == pointRank[v] - 1);
        int posU = pointRank[u];
        // binary search through points on the right side of [uv]
        {
            int left = -1, right = posU;
            while (left < right - 1) {
                int mid = (left + right) / 2;
                if (twoAreas(u, v, curOrder[mid]) <= K) {
                    right = mid;
                } else {
                    left = mid;
                }
            }
            umax(maxArea, twoAreas(u, v, curOrder[right]));
        }
        // the same for the points on the left side of [uv]
        {
            int left = posU + 1, right = N;
            while (left < right - 1) {
                int mid = (left + right) / 2;
                if (twoAreas(u, v, curOrder[mid]) <= K) {
                    left = mid;
                } else {
                    right = mid;
                }
            }
            umax(maxArea, twoAreas(u, v, curOrder[left]));
        }

        swap(pointRank[u], pointRank[v]);
        swap(curOrder[posU], curOrder[posU + 1]);
    }

    if (maxArea == 0) {
        cout << "-1\n";
    } else {
        cout << maxArea << "\n";
    }
}