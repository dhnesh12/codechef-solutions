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
 
const int Maxm = 15;
const int Inf = 2000000007;
 
int t;
int n, m;
int seq[Maxm];
int dist[Maxm][Maxm];
int tot[Maxm][1 << Maxm];
int dp[1 << Maxm];
int res[Maxm];
 
int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		fill((int*)dist, (int*)dist + Maxm * Maxm, 0);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				scanf("%d", &seq[j]); seq[j]--;
				for (int k = 0; k < j; k++)
					dist[seq[k]][seq[j]]++;
			}
		}
		for (int i = 0; i < m; i++)
			for (int j = 1; j < 1 << m; j++) {
				int b = __builtin_popcount((j & -j) - 1);
				tot[i][j] = tot[i][j ^ 1 << b] + dist[i][b];
			}
		for (int j = 1; j < 1 << m; j++) {
			dp[j] = Inf;
			for (int k = 0; k < m; k++) if (j & 1 << k)
				dp[j] = min(dp[j], dp[j ^ 1 << k] + tot[k][j ^ 1 << k]);
		}
		int cur = (1 << m) - 1;
		printf("%d:", dp[cur]);
		int slen = m - 1;
		while (slen >= 0)
			for (int j = 0; j < m; j++) if (cur & 1 << j)
				if (dp[cur] == dp[cur ^ 1 << j] + tot[j][cur ^ 1 << j]) {
					res[slen--] = j; cur ^= 1 << j; break;
				}
		for (int i = 0; i < m; i++)
			printf(" %d", res[i] + 1);
		printf("\n");
	}
	return 0;
} 
