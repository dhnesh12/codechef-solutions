#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
int n, m;
int tst;
const int maxN = 2005;
vector < pair < int, int > > g[maxN];
int l[maxN], r[maxN];
vector < int > cmp;
bool used[maxN];
int x[maxN];
bool all_ok = true;
struct node{
    int nxt[2];
    bool bad[2];
    node() {
        nxt[0] = nxt[1] = -1;
        bad[0] = false;
        bad[1] = false;
    }
};
void dfs(int v) {
    used[v] = true;
    cmp.push_back(v);
    for (auto t : g[v]) {
        int to = t.first;
        int w = t.second;
        if (used[to]) {
            if ((x[to] ^ x[v]) != w) {
                all_ok = false;
            }
        }
        else {
            x[to] = w ^ x[v];
            dfs(to);
        }
    }
}
int a[maxN];
node bor[200 * maxN];
int sz = 2;
void add_bor(int x, int shift, bool gr) {
    int cur = 1;
    for (int i = 29; i >= 0; i--) {
        int bit1 = (x >> i) & 1;
        int bit2 = (shift >> i) & 1;
        int nxt_v = -1;
        for (int j = 0; j < 2; j++) {
            if (bor[cur].nxt[j] == -1) {
                bor[cur].nxt[j] = sz;
                bor[cur].bad[j] = false;
                sz++;
            }
            if ((bit2 ^ j) != bit1) {
                if ((gr == true) && bit1 == 0) {
                    bor[cur].bad[j] = true;
                }
                else if ((gr == false) && bit1 == 1) {
                    bor[cur].bad[j] = true;
                }
            }
            else {
                nxt_v = bor[cur].nxt[j];
            }
        }
        cur = nxt_v;
    }
}
int dfs_bor(int cur, int bt) {
    if (cur == -1 || bt == -1) {
        return 0;
    }
    int mx = -1;
    for (int bit = 0; bit < 2; bit++) {
        if (bor[cur].bad[bit]) continue;
        int val = dfs_bor(bor[cur].nxt[bit], bt - 1);
        if (val != -1) {
            mx = val + ((1 << bt) * bit);
        }
    }
    return mx;
}
void go(vector < int >& cmp) {
    for (int i = 1; i <= 2 * sz; i++) {
        for (int bit = 0; bit < 2; bit++) {
            bor[i].nxt[bit] = -1;
            bor[i].bad[bit] = false;
        }
    }
    sz = 2;
    for (int v : cmp) {
        add_bor(l[v], x[v], false);
        add_bor(r[v], x[v], true);
    }
    int t = dfs_bor(1, 29);
    if (t == -1) {
        all_ok = false;
    }
    else {
        for (int v : cmp) {
            a[v] = t ^ x[v];
        }
    }
}
void solve() {
    cin >> n >> m;
    all_ok = true;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    for (int i = n + 1; i <= n + m; i++) {
        cin >> l[i] >> r[i];
    }
    for (int i = 1; i <= n + m; i++) {
        g[i].clear();
        x[i] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int x;
            cin >> x;
            if (x == -1) continue;
            g[i].push_back(make_pair(j + n, x));
            g[j + n].push_back(make_pair(i, x));
        }
    }
    memset(used, 0, sizeof used);
    for (int i = 1; i <= n + m; i++) {
        if (!all_ok) {
            cout << "NO" << '\n';
            return ;
        }
        if (!used[i]) {
            cmp.clear();
            x[i] = 0;
            dfs(i);
            go(cmp);
        }
    }
    if (all_ok) {
        cout << "YES" << '\n';
        for (int i = 1; i <= n; i++) {
            cout << a[i] << " ";
        }
        cout << '\n';
        for (int j = 1; j <= m; j++) {
            cout << a[n + j] << " ";
        }
        cout << '\n';
    }
    else {
        cout << "NO" << '\n';
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    //freopen("input.txt", "r", stdin);
    cin >> tst;
    while (tst--) solve();
    return 0;
}
