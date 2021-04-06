#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define ll long long

int c[21][1 << 20], dp[21][1 << 20], a[20][20];
int32_t main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	int t; cin >> t;
	while (t--) {
		int n, k; cin >> n >> k;
		int ans = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> a[i][j];
				if (i < j) {
					ans += a[i][j];
				}
			}
		}
		memset(c, 0, sizeof c);
		memset(dp, 0, sizeof dp);
		for (int i = 0; i < k; i++) {
			for (int mask = 0; mask < (1 << (n - k)); mask++) {
				for (int j = 0; j < (n - k); j++) {
					if (mask >> j & 1) {
						c[i][mask] += a[i][j + k];
						for (int x = j + 1; x < (n - k); x++) {
							if (mask >> x & 1) {
								c[i][mask] += a[j + k][x + k];
							}
						}
					}
				}
			}
		}
		for (int i = k - 1; i >= 0; i--) {
			for (int mask = 0; mask < (1 << (n - k)); mask++) {
				if (i == k - 1) {
					dp[i][mask] = c[i][mask];
					continue;
				}
				for (int sub = mask; ; sub = (sub - 1) & mask) {
					dp[i][mask] = max(dp[i][mask], dp[i + 1][mask ^ sub] + c[i][sub]);
					if (sub == 0) break;
				}
			}
		}
		int cur = 0;
		for (int mask = 0; mask < (1 << (n - k)); mask++) {
			cur = max(cur, dp[0][mask]);
		}
		cout << ans - cur << '\n';	
	}
}