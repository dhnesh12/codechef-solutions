#include <bits/stdc++.h>
using namespace std;

int main()
{
	int N, M, P;
	cin >> N >> M >> P;
	vector<vector<pair<int, int>>> all(M);
	for (int i = 0; i < N; i++) {
		int a, p, v;
		cin >> a >> p >> v; --a;
		all[a].emplace_back(p, v);
	}
	vector<int> b(M);
	for (int i = 0; i < M; i++) {
		cin >> b[i];
	}
	vector<int> dp(P + 1);
	for (int i = 0; i < M; i++) {
		auto tmp1 = dp;
		int sum = 0;
		for (auto p : all[i]) {
			sum += p.second;
			for (int j = P - p.first; j >= 0; j--) {
				tmp1[j + p.first] = max(tmp1[j + p.first], tmp1[j] + p.second);
			}
		}
		for (int j = 0; j + b[i] <= P; j++) {
			tmp1[j + b[i]] = max(tmp1[j + b[i]], dp[j] + sum);
		}
		dp = move(tmp1);
	}
	cout << *max_element(dp.begin(), dp.end()) << endl;
	return 0;
}
