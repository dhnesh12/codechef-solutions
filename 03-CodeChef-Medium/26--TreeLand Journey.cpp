#include <bits/stdc++.h>
using namespace std;
 
typedef long long ll;
 
const int mod = 1000000007;
const int Maxn = 505;
const int Maxm = 1 << 8;
 
int n;
int A[Maxn];
vector <int> neigh[Maxn];
int myind[Maxn][Maxn];
int dp[Maxn][Maxm][Maxn][2];
int siz[Maxn][Maxn];
int res;
 
int getSize(int p, int v)
{
	if (siz[p][v] == 0) {
		int res = 1;
		for (int i = 0; i < neigh[v].size(); i++) {
			int u = neigh[v][i];
			if (u == p) continue;
			res += getSize(v, u);
		}
		siz[p][v] = res;
	}
	return siz[p][v];
}
 
int Get(int v, int m, int ind, bool chk)
{
	if (dp[v][m][ind][chk] == -1) {
		int pnt = ind;
		if (chk)
			if (A[ind] != 0 && A[ind] != v) return dp[v][m][ind][chk] = 0;
			else pnt++;
		if (m >= (1 << int(neigh[v].size())) - 1)
			dp[v][m][ind][chk] = 1;
		else {
			int res = 0;
			for (int i = 0; i < neigh[v].size(); i++) if (!(m & 1 << i)) {
				int u = neigh[v][i];
				res = (res + ll(Get(u, 1 << myind[v][u], pnt, true)) * Get(v, m | 1 << i, pnt + getSize(v, u), false)) % mod;
			}
			dp[v][m][ind][chk] = res;
		}
	}
	return dp[v][m][ind][chk];
}
 
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);
	for (int i = 0; i < n - 1; i++) {
		int x, y; scanf("%d %d", &x, &y);
		myind[x][y] = neigh[y].size();
		myind[y][x] = neigh[x].size();
		neigh[x].push_back(y);
		neigh[y].push_back(x);
	}
	fill((int*)dp, (int*)dp + Maxn * Maxm * Maxn * 2, -1);
	for (int i = 1; i <= n; i++)
		res = (res + Get(i, 0, 0, true)) % mod;
	printf("%d\n", res);
	return 0;
} 