#include <bits/stdc++.h>
#define X first
#define Y second
#define sz(a) (int)a.size()
#define pb push_back

using namespace std;

void solve();

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    int t = 1;
    cin >> t;
    while (t--)
        solve();
    return 0;
}

struct node {
    int pr;
    int l, r;
    int cnt;
    int ss;
};

node v[40000000];

int uk = 0;

struct bor {
    int start;
    void cler() {
        start = uk;
        v[uk] = {-1, -1, -1, 0, 0};
        uk++;
    }
    void add(int x) {
        int ind = start;
        for (int i = 16; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (v[ind].r != -1) {
                    ind = v[ind].r;
                } else {
                    v[ind].r = uk;
                    v[uk] = {ind, -1, -1, 0, 0};
                    ind = v[ind].r;
                    uk++;
                }
            } else {
                if (v[ind].l != -1) {
                    ind = v[ind].l;
                } else {
                    v[ind].l = uk;
                    v[uk] = {ind, -1, -1, 0, 0};
                    ind = v[ind].l;
                    uk++;
                }
            }
        }
        v[ind].cnt++;
        while (ind != -1) {
            v[ind].ss++;
            ind = v[ind].pr;
        }
    }
    int get(int x) {
        int ind = start;
        int ans = 0;
        for (int i = 16; i >= 0; --i) {
            if ((x >> i) & 1) {
                if (v[ind].l == -1 || v[v[ind].l].ss == 0) {
                    ind = v[ind].r;
                    ans += (1 << i);
                } else {
                    ind = v[ind].l;
                }
            } else {
                if (v[ind].r == -1 || v[v[ind].r].ss == 0) {
                    ind = v[ind].l;
                } else {
                    ans += (1 << i);
                    ind = v[ind].r;
                }
            }
        }
        return (ans ^ x);
    }
    void cut(int x) {
        int ind = start;
        for (int i = 16; i >= 0; --i) {
            if ((x >> i) & 1) {
                ind = v[ind].r;
            } else
                ind = v[ind].l;
        }
        v[ind].ss--;
        v[ind].cnt--;
        ind = v[ind].pr;
        while (ind != -1) {
            v[ind].ss--;
            ind = v[ind].pr;
        }
    }
};

int a[30010];
vector <int> g[30010];

int start[30010];
int finish[30010];

vector <int> obh;

void dfs(int v, int pr = -1) {
    start[v] = sz(obh);
    obh.pb(v);
    for (auto i : g[v]) {
        if (i != pr)
            dfs(i, v);
    }
    finish[v] = sz(obh);
    obh.pb(v);
}

bor rmq[300010];

void build(int t, int l, int r) {
    rmq[t].cler();
    for (int i = l; i < r; ++i) {
        rmq[t].add(a[obh[i]]);
    }
    if (r - l == 1)
        return;
    int mid = (r + l) / 2;
    build(t * 2 + 1, l, mid);
    build(t * 2 + 2, mid, r);
}

void update(int t, int l, int r, int x, int y, int z) {
    rmq[t].cut(y);
    rmq[t].add(z);
    if (r - l == 1)
        return;
    int mid = (r + l) / 2;
    if (x < mid)
        update(t * 2 + 1, l, mid, x, y, z);
    else
        update(t * 2 + 2, mid, r, x, y, z);
}

int get_mx(int t, int l, int r, int x, int y, int z) {
    if (r <= x || y <= l)
        return -1;
    if (x <= l && r <= y)
        return rmq[t].get(z);
    int mid = (r + l) / 2;
    return max(get_mx(t * 2 + 1, l, mid, x, y, z), get_mx(t * 2 + 2, mid, r, x, y, z));
}

int up[30010][16];

int tin[30010];
int tout[30010];
int depth[30010];

int tim = 1;

void dfs2(int v, int h, int pr = -1) {
    tin[v] = tim;
    depth[v] = h;
    tim++;
    up[v][0] = max(pr, 0);
    for (int i = 1; i < 16; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (auto i : g[v]) {
        if (i != pr)
            dfs2(i, h + 1, v);
    }
    tout[v] = tim;
    tim++;
}

int get_lca(int x, int y) {
    if (tin[x] <= tin[y] && tout[y] <= tout[x])
        return x;
    if (tin[y] <= tin[x] && tout[x] <= tout[y])
        return y;
    for (int i = 15; i >= 0; --i) {
        if (tin[up[x][i]] < tin[y] && tout[y] < tout[up[x][i]])
            continue;
        x = up[x][i];
    }
    return up[x][0];
}

int pr_nul[30010][17];
int lol[30010][17];
int siz[30010][17];

int get_dsu(int x, int ind) {
    if (pr_nul[x][ind] == x)
        return x;
    return pr_nul[x][ind] = get_dsu(pr_nul[x][ind], ind);
}

void update_dsu(int x, int y, int ind) {
    x = get_dsu(x, ind);
    y = get_dsu(y, ind);
    if (x == y)
        return;
    int ans;
    if (depth[lol[x][ind]]< depth[lol[y][ind]])
        ans = lol[x][ind];
    else
        ans = lol[y][ind];
    lol[x][ind] = ans;
    lol[y][ind] = ans;
    if (siz[x][ind] == siz[y][ind])
        siz[x][ind]++;
    if (siz[x][ind] > siz[y][ind])
        pr_nul[y][ind] = x;
    else
        pr_nul[x][ind] = y;
}

void dfs3(int v, int ind, int pr = -1) {
    if (pr != -1) {
        if ((a[v] >> ind) & 1) {
            update_dsu(pr, v, ind);
        }
    }
    for (auto i : g[v]) {
        if (i != pr)
            dfs3(i, ind, v);
    }
}

void build_bits()  {
    for (int i = 0; i < 17; ++i) {
        dfs3(0, i);
    }
}

vector <int> izm;

void activ(int x, int y, int ind) {
    x = lol[get_dsu(x, ind)][ind];
    while (tin[y] <= tin[x] && tout[x] <= tout[y]) {
        if (!((a[x] >> ind) & 1)) {
            izm.pb(x);
            //a[x] |= (1 << ind);
        }
        if (x == 0)
            break;
        update_dsu(x, up[x][0], ind);
        x = lol[get_dsu(x, ind)][ind];
    }
}

void upd(int x, int y, int z) {
    for (int i = 0; i < 17; ++i) {
        if ((z >> i) & 1) {
            activ(x, y, i);
        }
    }
}

void solve() {
    uk = 0;
    obh.clear();
    int n, q, x, y;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 17; ++j) {
            pr_nul[i][j] = i;
            lol[i][j] = i;
            siz[i][j] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        g[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y;
        x--;
        y--;
        g[x].pb(y);
        g[y].pb(x);
    }
    dfs(0);
    tim = 1;
    dfs2(0, 0);
    build_bits();
    build(0, 0, sz(obh));
    int c, z;
    for (int i = 0; i < q; ++i) {
        cin >> c;
        if (c == 1) {
            cin >> x >> y >> z;
            x--;
            y--;
            int lca = get_lca(x, y);
            upd(x, lca, z);
            upd(y, lca, z);
            for (auto j : izm) {
                if (a[j] | z != a[j]) {
                    update(0, 0, sz(obh), start[j], a[j], a[j] | z);
                    update(0, 0, sz(obh), finish[j], a[j], a[j] | z);
                    a[j] |= z;
                }
            }
            izm.clear();
        } else {
            cin >> x >> y;
            x--;
            cout << get_mx(0, 0, sz(obh), start[x], finish[x] + 1, y) << '\n';
        }
    }
}
