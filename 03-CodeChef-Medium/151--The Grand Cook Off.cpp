#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long double ld;

const int Maxn = 105;

ld F[Maxn][Maxn];
int t;
int n;
int C[Maxn], S[Maxn];
int cur;
ld ways[2][Maxn][Maxn];

int main()
{
	F[1][1] = 1;
	for (int i = 1; i < Maxn; i++)
		for (int j = 1; j < Maxn; j++) {
			if (i > 1) F[i][j] += ld(i) * (i - 1) / 2 * F[i - 1][j];
			if (j > 1) F[i][j] += ld(j) * (j - 1) / 2 * F[i][j - 1];
			F[i][j] /= ld(i + j) * ld(i + j - 1) / 2;
		}
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &C[i]); S[i] = C[i] + S[i - 1];
		}
		cur = 0;
		fill((ld*)ways, (ld*)ways + 2 * Maxn * Maxn, 0.0l);
		ways[0][0][0] = 1;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j <= i; j++)
				for (int l = 0; l < Maxn; l++) if (ways[cur][j][l] > 0) {
					ways[!cur][j + 1][l + C[i + 1]] += ways[cur][j][l];
					ways[!cur][j][l] += ways[cur][j][l];
					ways[cur][j][l] = 0;
				}
			cur = !cur;
		}
		ld res = 0;
		for (int j = 1; j < n; j++)
			for (int l = 0; l < Maxn; l++) if (ways[cur][j][l] > 0) {
				int dif = abs(l - (S[n] - l));
				res += ld(dif) * ways[cur][j][l] * F[j][n - j];
			}
		cout << fixed << setprecision(6) << res / 2 + 1e-11l << endl;
	}
	return 0;
}