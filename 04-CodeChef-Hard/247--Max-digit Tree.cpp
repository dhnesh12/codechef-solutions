#include <bits/stdc++.h>
#define bp __builtin_popcountll
#define pb push_back
#define in(s) freopen(s, "r", stdin);
#define inout(s, end1, end2) freopen((string(s) + "." + end1).c_str(), "r", stdin),\
		freopen((string(s) + "." + end2).c_str(), "w", stdout);
#define fi first
#define se second
#define bw(i, r, l) for (int i = r - 1; i >= l; i--)
#define fw(i, l, r) for (int i = l; i < r; i++)
#define fa(i, x) for (auto i: x)
using namespace std;
const int mod = 1e9 + 7, inf = 1061109567;
const long long infll = 4557430888798830399;
const int N = 505;
int n, d[N], dp[11][11][N], ind[N], tour[N], sz[N], f[N][11][11][N];
vector<int> g[N];
void prepdp() {
	//dp[i][j][k]: Add every number by max(i, maxD), original form is a00....0j, what's the last digit of
	//(a+1)00...0. k means number of digit of a000...j
	memset(dp, -1, sizeof dp);
	fw (i, 0, 10) fw (j, 0, 10) {
		if (!i && !j) continue;
		int cur = j;
		while (cur < 10) cur += max(cur, i);
		dp[i][j][1] = cur % 10;
	}
	fw (k, 2, N) fw (i, 0, 10) fw (j, 0, 10) {
		if (!i && !j) continue;
		int cur = j;
		fw (x, 0, 10) cur = dp[max(i, x)][cur][k - 1];
		dp[i][j][k] = cur;
	}
}
int cur;
void dfs(int u, int p) {
	tour[cur++] = u;
	sz[u] = 1;
	fa (v, g[u]) if (v != p) dfs(v, u), sz[u] += sz[v];
}
void add(int &x, int y) { x += y; if (x >= mod) x -= mod; }
void proc() {
	cin >> n;
	fw (i, 0, n) g[i].clear();
	fw (i, 1, n) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		g[u].pb(v), g[v].pb(u);
	}
	fw (i, 0, n) cin >> d[i];
	fw (i, 0, n) sort(g[i].begin(), g[i].end());
	//Create an euler tour of the tree, then DPing on it is easy as a subtree is continuous.
	//dp[i][j][k][l]: Subtree of i, curi is j, curj is k, we still need l more digits to finish.
	fw (i, 0, n) sz[i] = 0;
	cur = 0;
	dfs(0, -1);
	memset(f, 0, sizeof f);
	fw (i, 0, n) ind[tour[i]] = i;
	fw (i, 1, n) {
		int curk = 1;
		fw (j, 0, d[0]) curk = dp[j][curk][i];
		f[0][d[0]][curk][i] = 1;
	}
	fw (i, 0, n - 1) fw (j, 0, 10) fw (k, 0, 10) fw (l, 1, n) if (f[tour[i]][j][k][l]) {
		int v = tour[i], pick = tour[i + 1];
		//Take vertex pick.
		int nxtk = k;
		if (l > 1) fw (x, 0, d[pick]) nxtk = dp[max(j, x)][nxtk][l - 1];
		else {
			//Only 1 digit left, we need to check if it's valid.
			int curk = k, curmx = max(j, k);
			bool good = 0;
			while (curk < 10) {
				if (curk == d[pick]) good = 1;
				curk += curmx;
				curmx = max(curmx, curk);
			}
			if (good) nxtk = d[pick];
			else nxtk = -1;
		}
		if (nxtk != -1) add(f[tour[i + 1]][max(j, d[pick])][nxtk][l - 1], f[v][j][k][l]);
		//Don't take this vertex. Skip the subtree.
		add(f[tour[i + sz[pick]]][j][k][l], f[v][j][k][l]);
	}
	int ans = 0;
	fw (i, 0, n) fw (j, 0, 10) fw (k, 0, 10) add(ans, f[i][j][k][0]);
	if (d[0] == 1 || d[0] == 2 || d[0] == 4 || d[0] == 8) add(ans, 1);
	cout << ans << "\n";
}
signed main() {
	#ifdef BLU
	in("blu.inp");
	#endif
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	prepdp();
	int t;
	cin >> t;
	while (t--) proc();
	return 0;
}