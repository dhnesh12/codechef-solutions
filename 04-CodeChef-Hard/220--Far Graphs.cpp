// a good post: https://blog.csdn.net/qq_39972971/article/details/89338233
#include <bits/stdc++.h>

#define reg register
#define fi first
#define se second
#define FIN(s) freopen(s, "r", stdin)
#define FOUT(s) freopen(s, "w", stdout)
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define lep(i, l, r) for (int i = l; i < r; ++i)
#define irep(i, r, l) for (int i = r; i >= l; --i)
#define ilep(i, r, l) for (int i = r; i > l; --i)
#define Rep(i, n) rep(i, 1, n)
#define Lep(i, n) lep(i, 1, n)
#define IRep(i, n) irep(i, n, 1)
#define ILep(i, n) ilep(i, n, 1)
typedef long long ll;
typedef long double ld;

namespace modular {
    const int MOD = 1000000007;
    inline int add(int x, int y) { return (x += y) >= MOD ? x -= MOD : x; }
    inline void inc(int &x, int y) { (x += y) >= MOD ? x -= MOD : 0; }
    inline int mul(int x, int y) { return 1LL * x * y % MOD; }
    inline int qpow(int x, int y) {
        int ans = 1;
        for (; y; y >>= 1, x = mul(x, x))
            if (y & 1)
                ans = mul(ans, x);
        return ans;
    }
}; // namespace modular

namespace Base {
    template <typename Tp> inline Tp input() {
        Tp x = 0, y = 1;
        char c = getchar();
        while ((c < '0' || '9' < c) && c != EOF) {
            if (c == '-')
                y = -1;
            c = getchar();
        }
        if (c == EOF)
            return 0;
        while ('0' <= c && c <= '9')
            x = x * 10 + c - '0', c = getchar();
        return x *= y;
    }
    template <typename Tp> inline void read(Tp &x) { x = input<Tp>(); }
    template <typename Tp> inline void chmax(Tp &x, Tp y) { x < y ? x = y : 0; }
    template <typename Tp> inline void chmin(Tp &x, Tp y) { x > y ? x = y : 0; }
}; // namespace Base
using namespace Base;
/*----------------------------------------------------------------------------*/

#define MAX_N 3007
const int len = 10000000;

int N, M, L, R;
int con[MAX_N][MAX_N], p[MAX_N], rk[MAX_N], col[MAX_N];
int mx[MAX_N], ans[MAX_N];
std::vector<int>G[MAX_N];
bool vis[MAX_N];

bool cmp(int x, int y) {
    return col[x] == col[y] ?
        (col[x] ? G[x].size() < G[y].size() : G[x].size() > G[y].size()) : col[x] < col[y];
}

bool dfs(int x) {
    vis[x] = true;
    for (int y : G[x])
        if (vis[y]) {
            if (col[x] == col[y]) return false;
        } else {
            col[y] = 2 - col[x];
            if (!dfs(y)) return false;
        }
    return true;
}

void solve() {
    read(N), read(M);
    Rep(i, N) Rep(j, N) con[i][j] = false;
    Rep(i, N) G[i].clear(), vis[i] = false;
    int u, v;
    Rep(i, M) {
        read(u), read(v);
        con[u][v] = con[v][u] = true;
        G[u].push_back(v), G[v].push_back(u);
    }
    int mid = 0, md = 0, flg = false;
    Rep(i, N) if (G[i].size() == 2) {
        if (con[G[i][0]][G[i][1]]) { mid = i, md = 1; break; }
    }
    vis[mid] = true, col[mid] = 1;
    Rep(i, N) if (!vis[i]) {
        col[i] = 0;
        if (!dfs(i)) return puts("No"), void();
    }
    L = R = 0;
    Rep(i, N) col[i] == 0 ? L++ : (col[i] == 2 ? R++ : 0), p[i] = i;
    std::sort(p + 1, p + N + 1, cmp);
    Rep(i, N) rk[p[i]] = i;
    int mxx = 0;
    Rep(i, N) if (col[p[i]] > 1) {
        for (int j : G[p[i]]) chmax(mxx, rk[j]);
        mx[i] = mxx;
        if (mxx != G[p[i]].size()) return puts("No"), void();
    }
    int pl = 1, pr = 1, cur = 1;
    if (!md) {
        while (pl <= L || pr <= R) {
            if (pl > L) ans[p[L + pr++]] = len + cur++;
            else if (pr > R) ans[p[pl++]] = cur++;
            else if (pl <= mx[L + pr]) ans[p[pl++]] = cur++;
            else ans[p[L + pr++]] = len + cur++;
        }
    } else {
        while (pl <= L || pr < R) {
            if (pl > L) ans[p[L + 1 + pr++]] = len + cur++;
            else if (pr >= R) ans[p[pl++]] = cur++;
            else if (pl <= mx[L + 1 + pr]) ans[p[pl++]] = cur++;
            else ans[p[L + 1 + pr++]] = len + cur++;
        }
        ans[mid] = len + 1, ans[p[N]] = len * 2 + 1;
    }
    puts("Yes");
    printf("%d ", len * 2);
    Rep(i, N) printf("%d ", ans[i]); puts("");
}

int main() {
#ifndef ONLINE_JUDGE
    FIN("graph.in");
    FOUT("graph.out");
#endif
    int T = input<int>();
    while (T--) solve();
    return 0;
}
