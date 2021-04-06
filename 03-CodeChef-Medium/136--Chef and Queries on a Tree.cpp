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

const int N = 1e5 + 10;
const int MEM = 1e7;
const int LOG = 16;
const int INF = -1e9;

int T, n, a, b, q, r, k, wei[N], in[N], out[N], tim, jump[N][LOG + 1], id, root[N], lson[MEM], rson[MEM], t[MEM], dep[N], num[N];
vector <int> g[N];
vector <pair<int, int>> vec;

int queryleft(int H, int ID, int v, int l = 0, int r = n - 1) {
	if (t[v] < H || l > ID) return INF; // nie udalo sie
	if (l == r) 
		return vec[l].fi;
	int m = (l + r) / 2;
	int Pr = queryleft(H, ID, rson[v], m + 1, r);
	if (Pr != INF) return Pr;
	return queryleft(H, ID, lson[v], l, m);
}

int queryright(int H, int ID, int v, int l = 0, int r = n - 1) {
	if (t[v] < H || r < ID) return INF;
	if (l == r) 
		return vec[l].fi;
	int m = (l + r) / 2;
	int Le = queryright(H, ID, lson[v], l, m);
	if (Le != INF) return Le;
	return queryright(H, ID, rson[v], m + 1, r);
}
				
		
int build(int x, int val, int l = 0, int r = n - 1) {
	int ja = id++;
	if (l == r) {
		if (x == l)
			t[ja] = val;
		return ja;
	}
	int m = (l + r) / 2;
	lson[ja] = build(x, val, l, m);
	rson[ja] = build(x, val, m + 1, r);
	t[ja] = max(t[lson[ja]], t[rson[ja]]);
	return ja;
}

int add(int x, int val, int v, int l = 0, int r = n - 1) {
	int ja = id++;
	if (l == r) {
		t[ja] = val;
		return ja;
	}
	int m = (l + r) / 2;
	if (x <= m) {
		lson[ja] = add(x, val, lson[v], l, m);
		rson[ja] = rson[v];
	}
	else {
		lson[ja] = lson[v];
		rson[ja] = add(x, val, rson[v], m + 1, r);
	}
	t[ja] = max(t[lson[ja]], t[rson[ja]]);
	return ja;
}
				

void dfs(int v, int p) {
	dep[v] = dep[p] + 1;
	jump[v][0] = (v == 1 ? 1 : p);
	rep(i, 1, LOG)
		jump[v][i] = jump[jump[v][i - 1]][i - 1];
	
	if (v == 1) root[v] = build(num[v], dep[v]);
	else root[v] = add(num[v], dep[v], root[p]);	
		
	in[v] = ++tim;
	for (auto it : g[v])
		if (it != p)
			dfs(it, v);
	out[v] = tim;
}

bool par(int a, int b) {
	return in[a] <= in[b] && out[b] <= out[a];
}

int lca(int a, int b) {
	if (par(a, b)) return a;
	if (par(b, a)) return b;
	per(i, 0, LOG)
		if (!par(jump[a][i], b))
			a = jump[a][i];
	return jump[a][0];
}

int path(int up, int down) {
	//cat(up);
	//cat(down);
	int res = 1e9;
	int ID = (int) (lower_bound(all(vec), mp(r, 0)) - vec.begin());
	
	if (ID < n) 
		res = min(res, abs(r - queryright(dep[up], ID, root[down])));
	
	if (ID > 0) 
		res = min(res, abs(r - queryleft(dep[up], ID - 1, root[down])));
	
	return res;
}

void solve() {
	vec.clear();
	scanf ("%d%d", &n, &q);
	rep(i, 1, n) g[i].clear();
	rep(i, 1, n) {
		scanf ("%d", wei + i);
		vec.pb({wei[i], i});
	}
	
	sort(all(vec));
	
	rep(i, 0, n - 1)
		num[vec[i].se] = i;
	
	rep(i, 2, n) {
		scanf ("%d%d", &a, &b);
		g[a].pb(b);
		g[b].pb(a);
	}
	dfs(1, 0);
	int ans = 0;
	while (q--) {
		scanf ("%d%d", &r, &k);
		r ^= ans;
		vector <int> ver(k);
		for (auto &it : ver) {
			scanf ("%d", &it);
			it ^= ans;
			assert (1 <= it && it <= n);
		}
		sort(all(ver), [](int a, int b) {
			return in[a] < in[b];
		});
		ans = 1e9;
		rep(i, 0, k - 1) {
			a = ver[i];
			b = ver[(i + 1) % k];
			int c = lca(a, b);
			ans = min(ans, path(c, a));
			ans = min(ans, path(c, b));
		}
		printf ("%d\n", ans);
	}
}	
	

int main() {
	scanf ("%d", &T);
	while (T--) solve();
		
	return 0;
}	
/* 
 * 1
5 7
1 2 3 4 5
1 2
2 3
2 4
1 5
3 2 4 5
* */
