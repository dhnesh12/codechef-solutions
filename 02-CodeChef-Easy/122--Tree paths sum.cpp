// Company Queries I
#if !defined(ONLINE_JUDGE)
    #include "prettyprint.hpp" 
    #include "debug.h"
#else
    #include <bits/stdc++.h>
    using namespace std;
    #define deb(...) 1729
    #define dbg(...) 29
    #define cer(x) 13
#endif
const bool testcase =  1;
typedef long long int ll;
const ll mod1 = 1000000007;
const ll mod2 = 998244353;

#define fast ios_base::sync_with_stdio(0);cin.tie(NULL) 
#define test int T_T = 1; if(testcase){cin>>T_T;}while(T_T--)
#define all(ve) ve.begin(),ve.end()

// SOLVE
using graph = vector<vector<pair<ll,ll>>>;
std::vector<vector<ll>> lca;
std::vector<ll> height;
std::vector<ll> pathSum;
ll mxH;
void dfs(ll cur, ll p, ll lvl, ll dist, graph& g) {
    height[cur] = lvl;
    pathSum[cur] = dist;
    for(int i = 0; i < g[cur].size(); i++) {
        int it = g[cur][i].first;
        int w = g[cur][i].second;
        if(it != p) {
            lca[it][0] = cur;
            dfs(it,cur,lvl+1,dist+w,g);
        }
    }
}
void initLCA(ll n, ll root, graph& g) {
    mxH = log2(n);
    height.assign(n+1,0);
    pathSum.assign(n+1,0);
    lca.assign(n+1,vector<ll>(mxH+1,-1));
    dfs(root,-1,0,0,g);
    for (int l = 1; l <= mxH; ++l) {
        for (int i = 1; i <= n; ++i) {
            ll p = lca[i][l-1];
            if(p != -1) {
                lca[i][l] = lca[p][l-1]; 
            }
        }
    }
}
ll findKth(ll x, ll k) {
    while(k > 0) {
        ll jump = log2(k);
        x = lca[x][jump];
        k -= (1 << jump);
        if(x == -1) {
            return x;
        }
    }
    return x;
}
ll findLCA(ll x, ll y) {
    if(height[x] < height[y]) {
        swap(x,y);
    }
    ll diff = height[x] - height[y];
    while(height[x] != height[y]) {
        ll jump = log2(diff);
        x = lca[x][jump];
        diff -= (1 << jump);
    }
    if(x == y) return x;
    for (int i = mxH; i >= 0; --i) {
        if(lca[x][i] != -1 && lca[x][i] != lca[y][i]) {
            x = lca[x][i];
            y = lca[y][i];
        }
    }
    return lca[x][0];
}
void solve(ll& kes) {
    ll n, q, root;
    cin >> n >> q >> root;
    graph g(n+1);
    for (int i = 1; i < n; ++i) {
        ll u, v, w;
        cin >> u >> v >> w;
        g[u].push_back({v,w});
        g[v].push_back({u,w});
    }
    initLCA(n,root,g);
    while(q--) {
        ll x, y;
        cin >> x >> y;
        dbg(x,y);
        ll ans = findLCA(x,y);
        ll fans = pathSum[x] + pathSum[y] - (2*pathSum[ans]);
        cout << fans << '\n';
    }
}

//MAIN
int main(){

    fast;
    #ifndef ONLINE_JUDGE
        // for getting input from input.txt
        freopen("input.txt", "r", stdin);
        // for writing output to output.txt
        freopen("output.txt", "w", stdout);
        // for debug in error.txt
        freopen("error.txt", "w", stderr);
    #endif

    ll i = 1;
    test {
        solve(i);
        i++;
    }
    return 0;
}
