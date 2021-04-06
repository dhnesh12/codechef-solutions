#include<bits/stdc++.h>
using namespace std;
using ll = long long;

const int N = 5000005;

struct Edge {
	int u, v;
} edge[N];
int n, m;
vector<int> adj[N];
int now, num[N], low[N];
int vis[N], bridge[N];
ll ans[N];

void dfs(int u, int p) {
	vis[u] = 1;
	num[u] = low[u] = ++now;
	for (int e : adj[u]) {
		int v = (edge[e].u == u ? edge[e].v : edge[e].u);
		if (vis[v] == 0) {
			dfs(v, u);
			low[u] = min(low[u], low[v]);
			if (low[v] > num[u]) bridge[e] = 1;
		} else if (v != p) {
			low[u] = min(low[u], num[v]);
		}
	}
}

int nComp, Sz[N];
int root[N], comp[N];
int par[N], child[N];
int tin[N], tout[N];
ll sum[N];

void dfs1(int u, int p) {
	Sz[nComp]++; comp[u] = nComp;
	child[u] = vis[u] = 1;
	tin[u] = ++now;
	for (int v : adj[u]) {
		if (v != p) {
			par[v] = u;
			dfs1(v, u);
			child[u] += child[v];
		}
	}
	tout[u] = now;
} 

int main() {
	ios_base::sync_with_stdio(0); cin.tie(0);
		
	int tc; cin >> tc;
	while (tc--) {
		cin >> n >> m;
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			num[i] = low[i] = vis[i] = 0;
		}
		for (int i = 1; i <= m; i++) {
			cin >> edge[i].u >> edge[i].v;
			adj[edge[i].u].push_back(i);
			adj[edge[i].v].push_back(i);
			bridge[i] = ans[i] = 0;
		}
		for (int i = 1; i <= n; i++) {
			if (vis[i] == 0) {
				now = 0; dfs(i, i);
			}
		}
		for (int i = 1; i <= n; i++) {
			adj[i].clear();
			vis[i] = Sz[i] = par[i] = 0;
		}
		for (int i = 1; i <= m; i++) {
			if (bridge[i] == 1) {
				adj[edge[i].u].push_back(edge[i].v);
				adj[edge[i].v].push_back(edge[i].u);
			}
		}
		nComp = 0; now = 0;
		for (int i = 1; i <= n; i++) {
			if (vis[i] == 0) {
				nComp++; dfs1(i, i);
				root[nComp] = i;
			}
		}
		for (int i = 1; i <= n; i++) sum[i] = 0;
		for (int i = 1; i <= m; i++) {
			if (bridge[i] == 0) {
				sum[tin[edge[i].u]] += Sz[comp[edge[i].v]];
				sum[tin[edge[i].v]] += Sz[comp[edge[i].u]];
			}
		}
		for (int i = 1; i <= n; i++) sum[i] += sum[i - 1];
		for (int i = 1; i <= m; i++) {
			if (bridge[i] == 0) {
				cout << 1LL * Sz[comp[edge[i].u]] * Sz[comp[edge[i].v]] << "\n";
			} else {
				int u = edge[i].u, v = edge[i].v;
				if (v == par[u]) swap(u, v);
				ll ans = 1LL * child[v] * (Sz[comp[v]] - child[v]);
				ans += 1LL * (Sz[comp[v]] - child[v]) * (sum[tout[v]] - sum[tin[v] - 1]);
				int rt = root[comp[v]];
				ans += 1LL * child[v] * (sum[tout[rt]] - sum[tin[rt] - 1] - sum[tout[v]] + sum[tin[v] - 1]);
				cout << ans << "\n";			
			}
		}
	}
}

