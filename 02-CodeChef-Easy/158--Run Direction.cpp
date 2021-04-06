//In the name of Allah.
#include <bits/stdc++.h>
using namespace std;

const int N = 51;
int T, n, vis[N << 1], mark[N << 1];
pair <double, double> p[N];
vector <int> go[N << 1], to[N << 1];

void read_input() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> p[i].first >> p[i].second;
	sort(p, p + n);
}

int get_not(int x) {
	return (x + n) % (2 * n);
}

void add_edge(int u, int v) {
	go[u].push_back(v);
	to[v].push_back(u);
}

void add_clause(int u, int v) {
	add_edge(get_not(u), v);
	add_edge(get_not(v), u);
}

void make_graph(double x) {
	for (int u = 0; u < n << 1; u++) {
		go[u].clear();
		to[u].clear();
	}
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			double d = p[j].first - p[i].first, vi = p[i].second, vj = p[j].second;;
			if (d / (vi + vj) < x)
				add_clause(get_not(i), j);
			if (vi < vj && d / (vj - vi) < x)
				add_clause(i, j);
			if (vi > vj && d / (vi - vj) < x)
				add_clause(get_not(i), get_not(j));
		}
}

void dfs(int u, vector <int> *adj, vector <int> &vec) {
	vis[u] = 1;
	for (int v: adj[u])
		if (vis[v] == 0)
			dfs(v, adj, vec);
	vec.push_back(u);
}

void kosaraju() {
	memset(vis, 0, sizeof vis);
	vector <int> ord;
	for (int u = 0; u < n << 1; u++)
		if (vis[u] == 0)
			dfs(u, go, ord);
	reverse(ord.begin(), ord.end());
	memset(vis, 0, sizeof vis);
	int cur = 0;
	for (int u: ord)
		if (vis[u] == 0) {
			vector <int> comp;
			dfs(u, to, comp);
			for (int x: comp)
				mark[x] = cur;
			cur++;
		}
}

bool check(double x) {
	make_graph(x);
	kosaraju();
	for (int u = 0; u < n; u++)
		if (mark[u] == mark[get_not(u)])
			return false;
	return true;
}

void write_output() {
	double l = 0, r = 1e19;
	for (int i = 0; i < 100; i++) {
		double mid = (l + r) / 2;
		check(mid)? l = mid: r = mid;
	}
	cout << fixed << (l == 1e19? -1: l) << endl;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cin >> T;
	while (T--) {
		read_input();
		write_output();
	}
}