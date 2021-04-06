#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, m;
	long long a, b, c;
	cin >> n >> m >> a >> b >> c;
	vector<vector<long long>> dp(n + 1, vector<long long>(n + m + 1));
	for(int i = 0;i <= n;i ++) {
		for(int j = 0;j <= n + m;j ++) {
			if(i + j > n + m) {
				dp[i][j] = LONG_LONG_MIN;
			} else if(i == 0 && j == 0) {
				dp[i][j] = 0;
			} else {
				if((i + j) % 2 == 0) {
					long long res = i * i * a + j * j * b + c * i * j;
					dp[i][j] = LONG_LONG_MIN;
					if(i != 0 && dp[i - 1][j + 1] != LONG_LONG_MIN) 
						dp[i][j] = max(dp[i][j], res + dp[i - 1][j + 1]);
					if(j != 0 && dp[i][j - 1] != LONG_LONG_MIN)
						dp[i][j] = max(dp[i][j], res + dp[i][j - 1]);
				} else {
					long long res = i * i * a + j * j * b + c * i * j;
					dp[i][j] = LONG_LONG_MAX;
					if(i != 0 && dp[i - 1][j + 1] != LONG_LONG_MIN) 
						dp[i][j] = min(dp[i][j], res + dp[i - 1][j + 1]);
					if(j != 0 && dp[i][j - 1] != LONG_LONG_MIN)
						dp[i][j] = min(dp[i][j], res + dp[i][j - 1]);
				}
			}
		}
	}
	cout << dp[n][m] << '\n';

	return 0;
}
