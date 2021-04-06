#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ss(x) (int) x.size()
#define fi first
#define se second
#define cat(x) cerr << #x << " = " << x << endl
#define rep(i, j, n) for (int i = j; i <= n; ++i)
#define per(i, j, n) for (int i = n; j <= i; --i)
#define all(x) x.begin(), x.end()
 
using namespace std;		

const int N = 5e6 + 100;
const int MOD = 1e9 + 7;

void add(int &a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

int n, a, b, c, d, e;

struct ed {
	int f, cost, id;
};

vector <ed> g[N];
vector <int> ans[N];

int dp[N];
pair<int, int> best[N][3];
pair<int, int> dp2[N][2];

void dfs1(int v, int p) {
	dp[v] = 0;
	rep(j, 0, 2)
		best[v][j] = {0, 0};
	rep(j, 0, 1)
		dp2[v][j] = {0, 0};
		
	for (auto it : g[v]) {
		if (it.f == p) continue;
		dfs1(it.f, v);
		dp[v] = max(dp[v], dp[it.f]);
		pair<int, int> now = {best[it.f][0].fi + it.cost, it.f};
		if (best[v][2] < now) swap(best[v][2], now);
		if (best[v][1] < best[v][2]) swap(best[v][1], best[v][2]);
		if (best[v][0] < best[v][1]) swap(best[v][0], best[v][1]);
		
		now = {dp[it.f], it.f};
		if (dp2[v][1] < now) swap(now, dp2[v][1]);
		if (dp2[v][0] < dp2[v][1]) swap(dp2[v][0], dp2[v][1]);
	}
	dp[v] = max(dp[v], best[v][0].fi + best[v][1].fi);
}

int lca(int v, int zak, int k) {
	rep(i, 0, 2) {
		if (best[v][i].se == zak) continue;
		if (!k) return best[v][i].fi;
		k--;
	}
	assert(0);
}

int lcadp(int v, int zak) {
	rep(i, 0, 1) {
		if (dp2[v][i].se == zak) continue;
		return dp2[v][i].fi;
	}
	assert(0);
}

void dfs2(int v, int p, int up, int updp) {
	for (auto it : g[v]) {
		if (it.f == p) continue;
		
		ans[it.id].pb(dp[it.f]);
		
		int now = max({updp, lca(v, it.f, 0) + lca(v, it.f, 1), up + lca(v, it.f, 0), lcadp(v, it.f)});
		
		ans[it.id].pb(now);
		
		int nup = max(lca(v, it.f, 0), up) + it.cost;
		
		dfs2(it.f, v, nup, now);
	}
}
		
		
		
		
	

void solve() {
	scanf ("%d%d%d%d%d%d", &n, &a, &b, &c, &d, &e);
	
	rep(i, 1, n) {
		g[i].clear();
		ans[i].clear();
	}
	
	rep(i, 1, n - 1) {
		int x = i + 1;
		int y = ((a + 1LL * b * (i - 1) % i) % i + 1);
		int z = (c * 1LL * i + d) % e;
		g[x].pb({y, z, i});
		g[y].pb({x, z, i});
	}
	
	dfs1(1, 0);
	dfs2(1, 0, 0, 0);
	
	int answer = 0;
	int W = 1000000 + 3;
	int now = 1;
	rep(i, 1, n - 1) {
		assert(ss(ans[i]) == 2);
		if (ans[i][0] > ans[i][1])
			swap(ans[i][0], ans[i][1]);
		add(answer, 1LL * ans[i][0] * now % MOD);
		now = 1LL * now * W % MOD;
		add(answer, 1LL * ans[i][1] * now % MOD);
		now = 1LL * now * W % MOD;
	}
	printf ("%d\n", answer);
}

int main() {	
	int T;
	scanf ("%d", &T);
	while (T--) solve();
	
	return 0;
}	
