#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, int> piipi;
typedef pair<pii, pii> piipii;
typedef pair<ll, ll> pll;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

int w[50005];
vector<int> g[50005];
bool vis[50005];
int sub[50005];
int par2[50005];
int n2 = 0;
ll ans = -2e18;
bool Q;
struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const {
        return Q ? p < o.p : k < o.k;
    }
};
 
struct LineContainer : multiset<Line> {
    const ll inf = LLONG_MAX;
    void init(){
        clear();
    }
    ll div(ll a, ll b) {
        return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return false; }
        if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
        else x->p = div(y->m - x->m, x->k - y->k);
        return x->p >= y->p;
    }
    void add(ll k, ll m) {
        auto z = insert({k, m, 0}), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p)
            isect(x, erase(y));
    }
    ll query(ll x) {
        assert(!empty());
        Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
        if(l.k*1.0*x + l.m >= 4e18) return 4e18;
        return l.k * x + l.m;
    }
}dp;
void dfs1(int u, int p){
    sub[u] = 1;
    n2++;
    for(int i=0;i<g[u].size();i++){
        int v = g[u][i];
        if(v == p || vis[v]) continue;
        dfs1(v, u);
        sub[u] += sub[v];
    }
}

int dfs2(int u, int p){
    for(int i=0;i<g[u].size();i++){
        int v = g[u][i];
        if(v == p || vis[v]) continue;
        if(sub[v] > n2/2) return dfs2(v, u);
    }
    return u;
}

vector<pll> add;
void dfs4(int u, int p, int d, ll sum1, ll res1, ll sum2, ll res2){
    sum1 += w[u];
    sum2 += w[u];
    res1 += d*1ll*w[u];
    res2 += sum2;
    ans = max(ans, res1);
    ans = max(ans, res2);
    ans = max(ans, dp.query(sum1) + res1);
    add.eb(mp(d*1ll+1, res2));
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i];
        if(v == p || vis[v]) continue;
        dfs4(v, u, d+1, sum1, res1, sum2, res2);
    }
}

void dfs3(int u, int p){
    n2 = 0;
    dfs1(u, 0);
    int u2 = dfs2(u, 0);
    vis[u2] = 1;
    par2[u2] = p;

    ans = max(ans, w[u2]*1ll);
    dp.init();
    dp.add(1, w[u2]);
    for(int i=0;i<sz(g[u2]);i++){
        int v = g[u2][i];
        if(v == p || vis[v]) continue;
        add.clear();
        dfs4(v, u2, 1, 0, 0, w[u2], w[u2]);
        for(int j=0;j<sz(add);j++){
            ll k = add[j].fi, m = add[j].se;
            dp.add(k, m);
        }
    }

    dp.init();
    dp.add(1, w[u2]);
    for(int i=sz(g[u2])-1;i>=0;i--){
        int v = g[u2][i];
        if(v == p || vis[v]) continue;
        add.clear();
        dfs4(v, u2, 1, 0, 0, w[u2], w[u2]);
        for(int j=0;j<sz(add);j++){
            ll k = add[j].fi, m = add[j].se;
            dp.add(k, m);
        }
    }

    for(int i=0;i<g[u2].size();i++){
        int v = g[u2][i];
        if(v == p || vis[v]) continue;
        dfs3(v, u2);
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            scanf("%d", &w[i]);
            g[i].clear();
            vis[i] = 0;
        }
        for(int i=1;i<=n-1;i++){
            int a, b;
            scanf("%d%d", &a, &b);
            g[a].eb(b);
            g[b].eb(a);
        }
        ans = -2e18;
        dfs3(1, 0);
        printf("%lld\n", ans);
    }
}