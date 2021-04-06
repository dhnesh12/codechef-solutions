#include<bits/stdc++.h>
using namespace std;

vector<int> mul(const vector<int> &x, const vector<int> &y) {
	int sz = (int)(x.size());
	vector<int> res(sz);
	for (int i = 0; i < sz; i++)
		res[i] = y[x[i]];
	return res;
}

int main() { 
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int n, m;
		cin >> n >> m;
		vector<vector<int>> p(n, vector<int>(m, 0));
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				cin >> p[i][j];
				--p[i][j];
			}
		if (1LL * n * n * m < 1LL * n * m * m) {
			vector<vector<vector<int>>> ans(n, vector<vector<int>>(n, vector<int>(m, 0)));
			vector<vector<long long>> res(n, vector<long long>(n, 0));
			for (int i = 0; i < n; i++) {
				ans[i][i] = p[i];
				for (int k = 0; k < m; k++)
					res[i][i] += 1LL * (k + 1) * (ans[i][i][k] + 1);
			}
			for (int i = n - 1; i >= 0; i--)
				for (int j = i + 1; j < n; j++) {
					ans[i][j] = mul(ans[i][j - 1], ans[j][j]);
					for (int k = 0; k < m; k++)
						res[i][j] += 1LL * (k + 1) * (ans[i][j][k] + 1);
				}
			int Q;
			cin >> Q;
			while (Q--) {
				int l, r;
				cin >> l >> r;
				--l, --r;
				cout << res[l][r] << '\n';
			}
		} else {
			vector<vector<int>> pref(n, vector<int>(m, 0));
			pref[0] = p[0];
			for (int i = 1; i < n; i++)
				pref[i] = mul(pref[i - 1], p[i]);
			int Q;
			cin >> Q;
			while (Q--) {
				int l, r;
				cin >> l >> r;
				--l, --r;
				long long res = 0;
				if (l == 0) {
					for (int i = 0; i < m; i++)
						res += 1LL * (i + 1) * (pref[r][i] + 1);
				} else {
					for (int i = 0; i < m; i++)
						res += 1LL * (pref[l - 1][i] + 1) * (pref[r][i] + 1);
				}
				cout << res << '\n';
			}
		}
	}
	return 0;
}
