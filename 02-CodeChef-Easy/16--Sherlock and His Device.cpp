
#include <bits/stdc++.h>
using namespace std;
// #define int long long
#define ii pair<int, int>
#define vi vector<int>
#define pb emplace_back
#define sz(x) (int)x.size()
#define all(v) v.begin(), v.end()
#define x first
#define y second
#define rep(i, j, k) for(i=j; i<k; i++)
#define sep(i, j, k) for(i=j; i>k; i--)
const int N = 2e3+5, inf = 1e9+7;
int n, k, i, j;
int A[N], par[N], dp[N][N];
vi v[N][N], adj[N];

void dfs1(int id, int p){
    par[id] = p;
    for(auto i:adj[id]) if(i!=p){
        dfs1(i, id);
        v[id][0].pb(i);
        rep(j, 0, n) for(auto k:v[i][j]) v[id][j+1].pb(k);
    }
}

int dfs(int id, int mask){
    if(dp[id][mask] != -1) return dp[id][mask];
    int& sol = dp[id][mask];
    sol=A[id]; 
    mask^=A[id];
    for(auto i:v[id][mask]) sol += dfs(i, mask);
    mask^=A[id];
    int ans=0;
    for(auto i:adj[id]) if(i!=par[id]) ans+= dfs(i, mask);
    return sol = max(sol, ans);
}

signed main()
{
    ios_base::sync_with_stdio(false); cin.tie(0);
    int i, j, a, b, ans = 0;
    cin>>n;
    rep(i, 1, n+1) cin>>A[i];
    memset(dp, -1, sizeof dp);
    rep(i, 1, n){
        cin>>a>>b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    dfs1(1, 0);
    cout<<dfs(1, 0);
}