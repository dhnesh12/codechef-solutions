#include <bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

typedef long long LL;

typedef pair<int, int> PII;
const int MN = 255;
const int MM = 2005;
const LL INF = 200000000000000LL;
#define MAX 200000000

int N, M, S, T, K;
int a[MM], b[MM], c[MM];
LL d[MM], cst[MN];
int fst[MN], nxt[MM];
int prv[MN];
int chk[MN];

queue<int> q;

void init() {
	M = 0;
	fill_n(fst, N, -1);
}

void add_edge(int u, int v, int w, LL x) {
	a[M] = u, b[M] = v, c[M] = w, d[M] = x;
	nxt[M] = fst[u], fst[u] = M++;
	a[M] = v, b[M] = u, c[M] = 0, d[M] = -x;
	nxt[M] = fst[v], fst[v] = M++;
}

LL mincost_maxflow() {
	int e, u, v;
	int inc, flow;
	LL cost;
	flow = cost = 0;
	LL res = 0;
	while (flow < K) {
		fill_n(cst, N, INF);
		cst[S] = 0;
		chk[S]++;
		q.push(S);
		while (!q.empty()) {
			u = q.front();
			q.pop();
			chk[u]--;
			for (e = fst[u]; ~e; e = nxt[e]) {
				v = b[e];
				if (!c[e] || cst[v] <= cst[u] + d[e]) continue;
				cst[v] = cst[u] + d[e];
				prv[v] = e;
				if (!chk[v]) {
					chk[v]++;
					q.push(v);
				}
			}
		}
		if (cst[T] == INF) break;
		inc = MAX;
		for (v = T; v != S; v = a[e]) {
			e = prv[v];
			inc = min(inc, c[e]);
		}
//		assert(inc == 1);
		flow += inc;
		cost += cst[T] * inc;
		for (v = T; v != S; v = a[e]) {
			e = prv[v];
			c[e] -= inc, c[e ^ 1] += inc;
		}
		res = max (res, 1LL * flow * MAX - cost);
	}
	return res;
}

LL w[MN];
map <PII, LL> edge;
LL rlt = 0;
int n, m;
int col[MN];
int xx[MN], yy[MN], ww[MN];

LL PRO () {
	init();
	for (int i = 1; i <= n; i ++) col[i] = rng() & 1;
	for (int i = 1; i <= n; i ++) {
		if (!col[i]) {
			add_edge(S, 2 * i - 1, 1, 0);
			add_edge(S, 2 * i, K - 1, 0);
		}
		else {
			add_edge(2 * i - 1, T, 1, 0);
			add_edge(2 * i, T, K - 1, 0);
		}
	}
	int x, y;
	LL W;
	for (int i = 0; i < m; i ++) {
		x = xx[i], y = yy[i], W = ww[i];
		if (col[x] == col[y]) continue;
		if(col[x]) swap(x, y);
		add_edge(2 * x - 1, 2 * y - 1, 1, MAX - w[x] - w[y] + W);
		if (w[y] - W > 0) add_edge(2 * x, 2 * y - 1, 1, MAX - w[y] + W);
		if (w[x] - W > 0) add_edge(2 * x - 1, 2 * y, 1, MAX - w[x] + W);
	}
	return mincost_maxflow();
}

void solve () {
	scanf ("%d %d %d", &n, &m, &K);
	S = 0, T = 2 * n + 1;
	N = T + 3;
	rlt = 0;
	for (int i = 1; i <= n; i ++) scanf ("%lld", w + i);
	edge.clear();
	for (int i = 0; i < m; i ++) {
		int u, v;
		LL W;
		scanf ("%d %d %lld", &u, &v, &W);
		if(u > v) swap(u, v);
		if (w[u] + w[v] - W <= 0 || edge.count({u, v}) && edge[{u, v}] <= W) continue;
		edge[{u, v}] = W;
	}
	m = 0;
	for (auto v : edge) {
		xx[m] = v.first.first, yy[m] = v.first.second, ww[m ++] = v.second;
	}
	int TT = 10000;
	while (TT --) {
		rlt = max (rlt, PRO());
	}
	printf("%lld\n", rlt);
}

int main () {
//#ifndef ONLINE_GUDGE
//	freopen ("in.txt", "r", stdin);
//	freopen ("out.txt", "w", stdout);
//#endif
	int t;
	scanf ("%d", &t);
	while (t --) {
		solve();
	}
}
