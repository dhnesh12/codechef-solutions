#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int M = 5e5+1;
const int inf = (1e9) + 1;
int N, A[M], ans, dp_in[M], dp_out[M], DP[M];
vector<int> adj[M];
void dfs1(int v, int p){dp_in[v] = 1; if(p != -1 && A[v] >= A[p]){dp_in[v] += dp_in[p];}
    for(int u : adj[v]){if(u != p) dfs1(u, v);}
	dp_out[v] = 1;for(int u : adj[v]){if(u != p && A[u] >= A[v]){dp_out[v] = max(dp_out[v], dp_out[u]+1);}}}
void dfs2(int v, int p){int j = upper_bound(DP+1, DP+N+1, A[v]) - DP; j--;
	if (j > 0){ans = max(ans, dp_out[v] + j);}
	int index = dp_in[v];int old_val = DP[index];DP[index] = min(DP[index], A[v]);
	for(int u : adj[v]){if(u != p){dfs2(u, v);}}DP[index] = old_val;}
void solve(){cin >> N; ans = 0;
	for (int i = 1; i <= N; i++){cin >> A[i], adj[i].clear(); dp_in[i] = dp_out[i] = 0; DP[i] = inf;} 
	for (int i = 1; i < N; i++){
		int u, v; cin >> u >> v; adj[u].pb(v); adj[v].pb(u); }dfs1(1, -1); dfs2(1, -1); cout << ans << endl;}
int main(){ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0); int t; cin >> t; while(t--){solve();}}