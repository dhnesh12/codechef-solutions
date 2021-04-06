#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

typedef pair <int, int> ii;

const int Inf = 2000000005;
const int Maxn = 5005;
const int Maxk = 14;

int t;
int n;
int X[Maxn], Y[Maxn];
vector <ii> neigh[Maxn];
int dist[Maxn], p[Maxn];
int L[Maxn], P[Maxn][Maxk], MX[Maxn][Maxk];
int q;

void MST()
{
	fill(dist + 2, dist + n + 1, Inf);
	fill(p + 1, p + n + 1, 0);
	priority_queue <ii> Q; Q.push(ii(0, 1));
	while (!Q.empty()) {
		int v = Q.top().second, d = -Q.top().first; Q.pop();
		if (d != dist[v]) continue;
		if (p[v] != 0) {
			neigh[v].push_back(ii(p[v], d));
			neigh[p[v]].push_back(ii(v, d));
		}
		p[v] = -1;
		for (int i = 1; i <= n; i++) if (p[i] != -1) {
			int cand = abs(X[v] - X[i]) + abs(Y[v] - Y[i]);
			if (cand < dist[i]) { dist[i] = cand; p[i] = v; Q.push(ii(-dist[i], i)); }
		}
	}
}

void Traverse(int v)
{
	for (int i = 0; i < neigh[v].size(); i++) {
		ii u = neigh[v][i];
		if (u.first == P[v][0]) continue;
		L[u.first] = L[v] + 1; P[u.first][0] = v; MX[u.first][0] = u.second;
		Traverse(u.first);
	}
}

int getRes(int a, int b)
{
	if (L[a] < L[b]) swap(a, b);
	int res = 0;
	for (int i = Maxk - 1; i >= 0; i--)
		if (L[a] - (1 << i) >= L[b]) {
			res = max(res, MX[a][i]);
			a = P[a][i];
		}
	if (a == b) return res;
	for (int i = Maxk - 1; i >= 0; i--)
		if (P[a][i] != P[b][i]) {
			res = max(res, max(MX[a][i], MX[b][i]));
			a = P[a][i], b = P[b][i];
		}
	res = max(res, max(MX[a][0], MX[b][0]));
	return res;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &X[i], &Y[i]);
			neigh[i].clear();
		}
		MST();
		Traverse(1);
		for (int j = 1; j < Maxk; j++)
			for (int i = 1; i <= n; i++) {
				MX[i][j] = max(MX[i][j - 1], MX[P[i][j - 1]][j - 1]);
				P[i][j] = P[P[i][j - 1]][j - 1];
			}
		scanf("%d", &q);
		while (q--) {
			int x, y; scanf("%d %d", &x, &y);
			printf("%d\n", getRes(x, y));
		}
	}
	return 0;
}