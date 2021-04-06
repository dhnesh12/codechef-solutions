#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vector<vector<long long>> dp(n, vector<long long>(n));
	vector<vector<int>> a(n, vector<int>(n));
	for(int i = 0;i < n;i ++) {
		for(int j = 0;j < n;j ++) {
			cin >> a[i][j];
		}
	}

	for(int i = 0;i < n;i ++) {
		for(int j = 0;j < n;j ++) {
			if(i == 0 && j == 0) {
				dp[i][j] = a[i][j] + a[j][n - 1 - i];
			} else {
				long long val = a[i][j] + a[j][n - 1 - i];
				dp[i][j] = LONG_LONG_MIN;
				if(i != 0) {
					dp[i][j] = max(dp[i][j], dp[i - 1][j] + val);
				}
				if(j != 0) {
					dp[i][j] = max(dp[i][j], dp[i][j - 1] + val);
				}
			}
		}
	}
	
	cout << dp[n - 1][n - 1] << '\n';

	return 0;
}
