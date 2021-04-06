#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> ii;
typedef pair <int, ii> iii;

const int Maxn = 505;
const int Maxm = 2048;
const int Inf = 1000000000;

int t;
int n, m;
int d, r, c;
vector <iii> seq;
int B[Maxn][Maxn];
int res[Maxn][Maxn];
int mn[Maxm][Maxm];

void CreateC(int s, int v, int l, int r)
{
	mn[s][v] = Inf;
	if (l < r) {
		int m = l + r >> 1;
		CreateC(s, 2 * v, l, m); 
		CreateC(s, 2 * v + 1, m + 1, r);
	}
}

void CreateR(int v, int l, int r)
{
	CreateC(v, 1, 0, m - 1);
	if (l < r) {
		int m = l + r >> 1;
		CreateR(2 * v, l, m); 
		CreateR(2 * v + 1, m + 1, r);
	}
}

int GetC(int s, int v, int l, int r, int a, int b)
{
	if (l == a && r == b) return mn[s][v];
	else {
		int m = l + r >> 1;
		if (b <= m) return GetC(s, 2 * v, l, m, a, b);
		if (m + 1 <= a) return GetC(s, 2 * v + 1, m + 1, r, a, b);
		return min(GetC(s, 2 * v, l, m, a, m), GetC(s, 2 * v + 1, m + 1, r, m + 1, b));
	}
}

int GetR(int v, int l, int r, int a, int b, int c, int d)
{
	if (l == a && r == b) return GetC(v, 1, 0, m - 1, c, d);
	else {
		int m = l + r >> 1;
		if (b <= m) return GetR(2 * v, l, m, a, b, c, d);
		if (m + 1 <= a) return GetR(2 * v + 1, m + 1, r, a, b, c, d);
		return min(GetR(2 * v, l, m, a, m, c, d), GetR(2 * v + 1, m + 1, r, m + 1, b, c, d));
	}
}

void UpdateC(int s, int v, int l, int r, int x, int val)
{
	mn[s][v] = min(mn[s][v], val);
	if (l < r) {
		int m = l + r >> 1;
		if (x <= m) UpdateC(s, 2 * v, l, m, x, val);
		else UpdateC(s, 2 * v + 1, m + 1, r, x, val);
	}
}

void UpdateR(int v, int l, int r, int x, int y, int val)
{
	UpdateC(v, 1, 0, m - 1, y, val);
	if (l < r) {
		int m = l + r >> 1;
		if (x <= m) UpdateR(2 * v, l, m, x, y, val);
		else UpdateR(2 * v + 1, m + 1, r, x, y, val);
	}
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		scanf("%d %d %d", &d, &r, &c);
		CreateR(1, 0, n - 1);
		seq.clear();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				scanf("%d", &B[i][j]);
				if (i || j)
					seq.push_back(iii(i * i + j * j, ii(i, j)));
			}
		UpdateR(1, 0, n - 1, 0, 0, 0);
		sort(seq.begin(), seq.end());
		for (int i = 0, j; i < seq.size(); i = j) {
			j = i;
			while (j < seq.size() && seq[j].first == seq[i].first) {
				ii p = seq[j].second;
				res[p.first][p.second] = B[p.first][p.second] + GetR(1, 0, n - 1, max(0, p.first - d), min(n - 1, p.first + d), 
																				  max(0, p.second - d), min(m - 1, p.second + d));
				j++;
			}
			j = i;
			while (j < seq.size() && seq[j].first == seq[i].first) {
				ii p = seq[j].second;
				UpdateR(1, 0, n - 1, p.first, p.second, res[p.first][p.second]);
				j++;
			}
		}
		printf("%d\n", res[r][c]);
	}
	return 0;
}