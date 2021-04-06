#define __LOCAL_DEBUG__
#include<bits/stdc++.h>
using namespace std;
#ifdef __LOCAL_DEBUG__
# define _debug(x) { cerr << "\033[94m" << __func__ << " " << #x << ": " << (x) << "\n\033[0m"; }
#else
# define _debug(...) {((void) 0);}
#endif
#define REP(i, n) for (int i = (0); i < (n); i++)
#define REPP(i, a, b) for (int i = (a); i < (b); i++)
#define EACH(x, arr) for (auto& x : arr) 
#define ITR(i, c) for (__typeof((c).begin()) i = (c).begin(); i != (c).end(); i++)
#define CLR(x, v) memset(x, v, sizeof (x))
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int) x.size()
template<class T> inline void amin(T &x, const T &y) { if (y<x) x=y; }
template<class T> inline void amax(T &x, const T &y) { if (x<y) x=y; }
using LL = long long;
using PII = pair<int, int>;
using VI = vector<int>;
using VVI = vector<VI>;
const int INF = 0x3f3f3f3f;
const int MOD = 1e9 + 7;
const int MAXN = 1e7 + 10;
int n, m, k;
int dp[1 << 13][2];
int ok[1 << 13];
int g[13][13];
int tot;
int mv(int mask, int take) {
    if (~mask >> take & 1) return 0;
    int nmask = mask ^ (1 << take);
    return ok[nmask];
}
VI get(int mask) {
    VI res;
    REP(i, 1 << n) {
        if ((mask | i) != mask) continue;
        if (__builtin_popcount(i) > k) continue;
        if (ok[mask ^ i]) res.push_back(i);
    }
    return res;
}
void MAIN() {
    cin >> n >> m >> k;
    CLR(dp, INF);
    CLR(g, 0);
    REP(i, m) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u][v] = g[v][u] = 1;
    }
    CLR(ok, 0);
    REP(i, 1 << n) {
        VI has;
        REP(j, n) if (i >> j & 1) has.push_back(j);
        bool flag = true;
        REP(j, SZ(has)) REPP(k, j + 1, SZ(has)) flag &= !g[has[j]][has[k]];
        ok[i] = flag;
    }
    tot = (1 << n) - 1;
    queue<PII> que;
    que.push(PII(tot, 0));
    dp[tot][0] = 0;
    while (SZ(que)) {
        PII cur = que.front();
        que.pop();
        int mask = cur.first, side = cur.second;
        VI nxt = get(mask);
        EACH(take, nxt) {
            int nmask = tot - (mask ^ take);
            int nside = 1 - side;
            if (dp[nmask][nside] == INF) {
                dp[nmask][nside] = dp[mask][side] + 1;
                que.push(PII(nmask, nside));
            }
        }
    }
    cout << min(dp[tot][1], dp[0][0]) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int TC = 1;
    cin >> TC;
    REP(tc, TC) {
    // while (cin >> n, n) {
        // cout << "Case " << tc + 1 << ": ";
        MAIN();
    }
    return 0;
}
