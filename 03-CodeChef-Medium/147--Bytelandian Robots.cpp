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

const int Maxn = 505;
const int Maxm = 1015;
const int mod = 7051954;

int t;
int n, L, A, B;
char str[Maxn];
int pos[Maxn], neg[Maxn];
int dp[Maxn][Maxm];
int res;

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d", &n, &L, &A, &B);
		scanf("%s", str);
		pos[n] = neg[n] = n;
		for (int i = n - 1; i >= 0; i--)
			if (str[i] == '+') pos[i] = i, neg[i] = neg[i + 1];
			else neg[i] = i, pos[i] = pos[i + 1];
		fill((int*)dp, (int*)dp + Maxn * Maxm, 0);
		res = 0;
		dp[0][Maxn] = 1;
		for (int i = 0; i <= n; i++)
			for (int j = 0; j < Maxm; j++) if (dp[i][j] != 0) {
				int real = j - Maxn + A;
				if (real == B) res = (res + dp[i][j]) % mod;
				if (real > 0) {
					int ni = neg[i] + 1;
					if (ni <= n) dp[ni][j - 1] = (dp[ni][j - 1] + dp[i][j]) % mod;
				}
				if (real < L) {
					int ni = pos[i] + 1;
					if (ni <= n) dp[ni][j + 1] = (dp[ni][j + 1] + dp[i][j]) % mod;
				}
			}
		printf("%d\n", res);
	}
	return 0;
}