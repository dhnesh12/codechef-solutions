#include<bits/stdc++.h>
using namespace std;
#define ff first
#define ss second
#define int long long
#define pb push_back
#define pii pair <int,int>
const int nax = 1e5+10;
vector<int> g[nax] , par(nax) , vis(nax) , deg(nax) , lvl(nax) , g1[nax] , sb(nax);
void dfs(int v,int p){par[v] = p; if (p) g1[p].pb(v); vis[v] = 1; vector<pii>temp;
    for (auto &i : g[v]){if (i != p){temp.pb({deg[i],i});}} sort (temp.begin(),temp.end(),greater<pii>());
    for (auto &i : temp){if (!vis[i.ss]){dfs(i.ss,v);}} return;}
void dfs_work(int v,int p){lvl[v] = lvl[p] + 1; sb[v] = 1;
    for (auto &i : g1[v]){dfs_work(i, v);sb[v] += sb[i];}return;}
signed main(){ios::sync_with_stdio(0), cin.tie(0), cout.tie(0); int t; cin >> t;
    while (t--){int n, m; cin >> n >> m;
        for (int i = 1; i <= n; i++){g[i].clear();vis[i] = 0;deg[i] = 0;lvl[i] = 0; sb[i] = 0; g1[i].clear();}
        pii e[m]; int root = 1, mx = 0;
        for (int i = 0; i < m; i++){cin >> e[i].ff >> e[i].ss; deg[e[i].ff]++,deg[e[i].ss]++;
            g[e[i].ff].pb(e[i].ss); g[e[i].ss].pb(e[i].ff);}
        for (int i = 1; i <= n ; i++){if (mx < deg[i]){mx = deg[i]; root = i;}}
        dfs(root,0); lvl[0] = -1; dfs_work (root,0); bool f = 0; if (mx != n-1){f = 1;}
        for (int i = 1; i <= n; i++){if (deg[i]-lvl[i] !=  sb[i]-1) f=1;} if (f){cout << "NO" << endl;}
        else{cout << "YES" << endl; for (int i = 1; i <= n; i++){cout << par[i] << " ";} cout << endl;}}}