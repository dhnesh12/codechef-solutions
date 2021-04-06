#include <bits/stdc++.h>
using namespace std;

int main() {
	int n;
	cin >> n;
	vector<long long> a(n);
	for (auto & it : a) cin >> it;
	vector<pair<long long, pair<int, int>>> v;
	for (int i = 0; i < n - 1; i++) {
	    for (int j = i + 1; j < n; j++) {
	        v.push_back({a[i] ^ a[j], {i, j}});
	    }
	}
	sort(v.begin(), v.end());
	vector<int> dp(n);
	for (auto & it : v) {
	    int l = it.second.first , r = it.second.second;
	    dp[r] = max(dp[r], dp[l] + 1);
	}
	cout << (*(max_element(dp.begin(), dp.end())) + 1) << endl;
	return 0;
}
