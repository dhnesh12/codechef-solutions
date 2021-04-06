#include <bits/stdc++.h>
 
using namespace std;
 
#define int int64_t
 
void solve() {
	int N, M;
	cin >> N >> M;
	vector<int> A(N);
	for(int i = 0; i < N; i++) {
		cin >> A[i];
	}
	vector<vector<int>> g(N);
	vector<vector<int>> dp(N);
	for(int i = 0; i < M; i++) {
		int u, v;
		cin >> u >> v;
		u--, v--;
		if(A[u] > A[v]) {
			swap(u, v);
		} else if(A[u] == A[v]) {
			continue;
		}
		g[u].push_back(v);
	}
	vector<int> p(N);
	iota(begin(p), end(p), 0);
	sort(begin(p), end(p), [&](int a, int b){return A[a] > A[b];});
	int ans = 1;
	for(auto u: p) {
		sort(begin(g[u]), end(g[u]), [&](int a, int b){return A[a] > A[b];});
		int cur = 2;
		for(auto v: g[u]) {
			auto it = lower_bound(begin(g[v]), end(g[v]), 2 * A[v] - A[u], 
				[&](int w, int c){
					return A[w] > c;
				});
			if(it != begin(g[v])) {
				cur = max(cur, 1 + dp[v][it - begin(g[v]) - 1]);
			}
			ans = max(ans, cur);
			dp[u].push_back(cur);
		}
	}
	cout << ans << endl;
}
 
signed main() {
	//freopen("input.txt", "r", stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	int t;
	cin >> t;
	while(t--) {
		solve();
	}
	return 0;
}