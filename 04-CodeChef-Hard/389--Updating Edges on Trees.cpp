#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ss(x) (int) x.size()
#define cat(x) cerr << #x << " = " << x << endl
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, l, r) for (int i = r; l <= i; --i)

using ll = long long;
using namespace std;

const int N = 4e5 + 100;
const int LOG = 18;
 
int n, in[N], out[N], siz[N], dep[N], jj[N][LOG];
vector <int> G[N];
 
int dfs(int v, int p) { // proszę dać v = p! <----------------------------------
	jj[v][0] = p;
	rep(i, 1, LOG - 1) jj[v][i] = jj[jj[v][i - 1]][i - 1];
	in[v] = ++*in;
	dep[v] = dep[p] + 1;
	siz[v] = 1;
	for (auto u : G[v])
		if (u != p)
			siz[v] += dfs(u, v);
	out[v] = *in;
	return siz[v];
}
 
int ispar(int a, int b) {
	return in[a] <= in[b] && in[b] <= out[a];
}
 
int lca(int a, int b) {
	if (ispar(a, b)) return a;
	if (ispar(b, a)) return b;
	per(i, 0, LOG - 1)
		if (!ispar(jj[a][i], b))
			a = jj[a][i];
	return jj[a][0];
}

ll dp[N], all[N];

void add(int x, int y, int z) {
	dp[x] += z;
	dp[y] += z;
	dp[lca(x, y)] -= 2 * z;
}

void work(int v, int p) {
	for (auto u : G[v])
		if (u != p) {
			work(u, v);
			dp[v] += dp[u];
		}
}			

void solve(int v, int p) {
	all[v] = dp[v] + all[p];
	for (auto u : G[v])
		if (u != p)
			solve(u, v);
}
 
int main() {
	int n, m1, m2;
	scanf ("%d%d%d", &n, &m1, &m2);
	rep(i, 2, n) {
		int x, y;
		scanf ("%d%d", &x, &y);
		G[x].pb(y);
		G[y].pb(x);
	}
	dfs(1, 1);
	rep(i, 1, m1) {
		int a, b, c, d;
		scanf ("%d%d%d%d", &a, &b, &c, &d);
		add(a, b, 1);
		int e = lca(c, a), f = lca(c, b);
		int x = (dep[e] > dep[f] ? e : f);
		e = lca(d, a), f = lca(d, b);
		int y = (dep[e] > dep[f] ? e : f);
		int g = lca(a, b);
		if (dep[x] < dep[g]) x = g;
		if (dep[y] < dep[g]) y = g;
		add(x, y, -1);
	}
	work(1, 1);
	solve(1, 0);
	while (m2--) {
		int a, b;
		scanf ("%d%d", &a, &b);
		printf ("%lld\n", all[a] + all[b] - 2 * all[lca(a, b)]);
	}
	
	return 0;
}
