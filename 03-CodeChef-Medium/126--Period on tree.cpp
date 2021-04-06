// Why am I so dumb? :c
// chrono::system_clock::now().time_since_epoch().count()
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define pb push_back
#define mp make_pair

#define all(x) (x).begin(), (x).end()

#define fi first
#define se second

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;   
typedef pair<int, int> pii;
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int MOD = (int)1e9 + 7;
const int P = 31;
const int MAXN = 150000 + 5;
const int L = 18;

int tin[MAXN], tout[MAXN];

pair<pii, char> e[MAXN];

vector<int> adj[MAXN];

int fenw[2][MAXN];

int par[L][MAXN];

char let[MAXN];

int revP[MAXN];

int dep[MAXN];

int pwP[MAXN];

int timer;

int n, q;

int addMod(int a, int b, int m = MOD) {
    a += b;

    if (m <= a) {
        a -= m;
    }

    return a;
}

int mulMod(int a, int b, int m = MOD) {
    return a * 1ll * b % m;
}

int binPow(int a, int b) {
    int ret = 1;

    while (b > 0) {
        if (b & 1) {
            ret = mulMod(ret, a);
        }

        a = mulMod(a, a);
        b >>= 1;
    }

    return ret;
}

int rev(int x) {
    return binPow(x, MOD - 2);
}

void pre() {
    pwP[0] = 1;
    revP[0] = 1;

    for (int i = 1; i < MAXN; ++i) {
        pwP[i] = mulMod(pwP[i - 1], P);
        revP[i] = rev(pwP[i]);
    }
}

bool bit(int x, int p) {
    return x & (1 << p);
}

void dfs(int v, int pr) {
    par[0][v] = pr;
    tin[v] = ++timer;

    for (int to : adj[v]) {
        if (to != pr) {
            dep[to] = dep[v] + 1;
            dfs(to, v);
        }
    }    

    tout[v] = timer;
}

void fenwUpd(int id, int p, int val) {
    for (; p <= n; p |= (p + 1)) {
        fenw[id][p] = addMod(fenw[id][p], val);
    }
}

int prefSum(int id, int p) {
    int ret = 0;

    for (; p > 0; --p) {
        ret = addMod(ret, fenw[id][p]);
        p &= (p + 1);
    }

    return ret;
}

int kthPar(int u, int k) {
    for (int i = 0; i < L; ++i) {
        if (bit(k, i)) {
            u = par[i][u];
        }
    }

    return u;
}

int getLca(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }

    u = kthPar(u, dep[u] - dep[v]);    

    if (u == v) {
        return u;
    }

    for (int i = L - 1; i >= 0; --i) {
        if (par[i][u] != par[i][v]) {
            u = par[i][u];
            v = par[i][v];
        }
    }

    return par[0][u];
}

void update(int u, int c) {
    fenwUpd(0, tin[u], mulMod(c, pwP[dep[u] - 1]));
    fenwUpd(0, tout[u] + 1, MOD - mulMod(c, pwP[dep[u] - 1]));
    fenwUpd(1, tin[u], mulMod(c, revP[dep[u]]));
    fenwUpd(1, tout[u] + 1, MOD - mulMod(c, revP[dep[u]]));        
}

void update(int u, int v, char c) {
    if (dep[u] > dep[v]) {
        swap(u, v);
    }

    update(v, MOD - (let[v] - 'a' + 1));
    let[v] = c;
    update(v, let[v] - 'a' + 1);
}

int hshD(int u) {
    return prefSum(0, tin[u]);
}

int hshU(int u) {
    return mulMod(prefSum(1, tin[u]), pwP[dep[u]]);
}

int getHashUp(int u, int v) {
    // v is ancestor of u
    int ret = addMod(hshU(u), MOD - mulMod(hshU(v), pwP[dep[u] - dep[v]]));
    //printf("HASH UP (%d %d) - %d\n", u, v, ret);
    return ret;
}

int getHashDown(int u, int v) {
    // v is ancestor of u
    int ret = mulMod(addMod(hshD(u), MOD - hshD(v)), revP[dep[v]]);
    //printf("HASH DOWN (%d %d) - %d\n", u, v, ret);
    return ret;
}   

int getHash(int u, int v, int lca = -1) {
    if (lca == -1) {
        lca = getLca(u, v);
    }

    int a = getHashUp(u, lca);
    int b = getHashDown(v, lca);      
    int ret = addMod(a, mulMod(b, pwP[dep[u] - dep[lca]]));
    //printf("HASH PATH (%d %d) - %d\n", u, v, ret);
    return ret;
}

int getDist(int u, int v, int lca = -1) {
    if (lca == -1) {
        lca = getLca(u, v);
    }

    return dep[u] + dep[v] - 2 * dep[lca];
}

bool isPeriod(int a, int lenA, int b, int lenB) {
    b = mulMod(b, addMod(pwP[lenA], MOD - 1));
    a = mulMod(a, addMod(pwP[lenB], MOD - 1));
    return a == b;
}

int query(int u, int v) {
    if (dep[u] < dep[v]) {
        swap(u, v);
    }

    int lca = getLca(u, v);    
    int tot = getHash(u, v, lca);
    int len = getDist(u, v, lca);
    int ret = len;

    if (isPeriod(tot, len, getHashUp(u, kthPar(u, 1)), 1)) {
        return 1;
    }

    vector<int> pri;
    int _len = len;

    for (int i = 2; i * i <= _len; ++i) {
        if (_len % i == 0) {
            pri.pb(i);
            _len /= i;

            while (_len % i == 0) {
                _len /= i;
            }
        }
    }

    if (_len > 1) {
        pri.pb(_len);
    }

    for (int d : pri) {
        while (ret % d == 0 && isPeriod(tot, len, getHashUp(u, kthPar(u, ret / d)), ret / d)) {
            ret /= d;
        }        
    }        

    return ret;          
}

void solve() {
    scanf("%d", &n);

    for (int i = 1; i < n; ++i) {
        int u, v;
        char c;
        scanf("%d %d %c", &u, &v, &c);
        e[i] = mp(mp(u, v), c);
        adj[u].pb(v);
        adj[v].pb(u);                                    
    }

    dep[1] = 0;
    dfs(1, 1);

    for (int i = 1; i < L; ++i) {
        for (int j = 1; j <= n; ++j) {
            par[i][j] = par[i - 1][par[i - 1][j]];
        }
    }

    for (int i = 1; i < n; ++i) {
        int u = e[i].fi.fi;
        int v = e[i].fi.se;

        if (dep[u] > dep[v]) {
            swap(u, v);
        }

        let[v] = e[i].se;
    }

    for (int i = 2; i <= n; ++i) {
        update(i, let[i] - 'a' + 1);
    }

    scanf("%d", &q);

    for (int i = 1; i <= q; ++i) {
        int tp;
        scanf("%d", &tp);

        if (tp == 1) {
            int u, v;
            scanf("%d %d", &u, &v);
            printf("%d\n", query(u, v));
        }
        else {
            int u, v;
            char c;
            scanf("%d %d %c", &u, &v, &c);
            update(u, v, c);                       
        }
    }

    for (int i = 1; i <= n; ++i) {
        fenw[0][i] = fenw[1][i] = 0;
        e[i] = mp(mp(0, 0), 0);
        tin[i] = tout[i] = 0;
        adj[i].clear();
        let[i] = 0;
        dep[i] = 0;
    }

    timer = 0;
}

int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int tt;
    scanf("%d", &tt);

    pre();

    while (tt--) {
        solve();
    }

    return 0;
}