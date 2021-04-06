#include <bits/stdc++.h>
using namespace std;
 
typedef long double ld;
 
const int Maxn = 61;
const int nil = 72005;
const int Maxm = nil * 2 + 5;
const int Inf = 1000000000;
 
int t;
int n, k;
int a[Maxn];
int cur;
bool dp[2][Maxn][Maxm];
int mn[2][Maxn], mx[2][Maxn];
 
int main()
{
	scanf("%d", &t);
	fill((int*)mn, (int*)mn + 2 * Maxn, Inf);
	fill((int*)mx, (int*)mx + 2 * Maxn, -Inf);
	while (t--) {
		scanf("%d %d", &n, &k);
		for (int i = 0; i < n; i++) {
			scanf("%d", &a[i]); a[i] = -a[i];
		}
		sort(a, a + n);
		for (int i = 0; i < n; i++)
			a[i] = -a[i];
		int spec = k / 2;
		dp[cur][0][nil] = true;
		mn[cur][0] = mx[cur][0] = nil;
		for (int i = 0; i < n; i++) {
			for (int j = min(i, k); j >= 0; j--) {
				for (int l = mn[cur][j]; l <= mx[cur][j]; l++) if (dp[cur][j][l]) {
					dp[cur][j][l] = false;
					if (j + (n - 1 - i) >= k) {
						dp[!cur][j][l] = true;
						mn[!cur][j] = min(mn[!cur][j], mn[cur][j]);
						mx[!cur][j] = max(mx[!cur][j], mx[cur][j]);
					}
					if (j + 1 <= k)
						if (j == spec) {
							int val = l - (k - 1) * a[i];
							dp[!cur][j + 1][val] = true;
							mn[!cur][j + 1] = min(mn[!cur][j + 1], val);
							mx[!cur][j + 1] = max(mx[!cur][j + 1], val);
						} else {
							int val = l + a[i];
							dp[!cur][j + 1][val] = true;
							mn[!cur][j + 1] = min(mn[!cur][j + 1], val);
							mx[!cur][j + 1] = max(mx[!cur][j + 1], val);
						}
				}
				mn[cur][j] = Inf; mx[cur][j] = -Inf;
			}
			cur = !cur;
		}
		int small = Maxm;
		for (int j = 0; j <= k; j++) {
			for (int l = mn[cur][j]; l <= mx[cur][j]; l++) if (dp[cur][j][l]) {
				dp[cur][j][l] = false;
				if (j == k) small = min(small, abs(l - nil));
			}
			mn[cur][j] = Inf; mx[cur][j] = -Inf;
		}
		cout << fixed << setprecision(3) << ld(small) / ld(k) + 1e-10l << endl;
	}
	return 0;
} 