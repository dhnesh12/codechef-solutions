#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#define ll long long int
#define inf 1000000000000
#define mod 1000000007
#define tc(t) int t; cin >> t; while (t--)
#define all(v) v.begin(),v.end()
#define sz(x) (int)x.size()
#define F first
#define S second
#define ps(x,y)   fixed<<setprecision(y)<<x
using namespace std;

struct segtree {

	vector<int> node;
	int size;
	void init(int n) {

		size = 1;
		while (size < n)size *= 2;
		node.assign(2 * size, 600);
	}
	void set(int l, int r, int v, int x, int lx, int rx)
	{
		if (lx >= r || l >= rx)return;
		if (lx >= l && rx <= r ) {

			node[x] = min(node[x], v);
			return;

		}
		int m = (lx + rx) / 2;
		set(l, r, v, 2 * x + 1, lx, m);
		set(l, r, v, 2 * x + 2, m, rx);
	}

	void set(int l, int r, int v) {

		set(l, r, v, 0, 0, size);
	}

	int get(int i, int x, int lx, int rx) {

		if (rx - lx == 1) {

			return node[x];
		}
		int m = (lx + rx) / 2;
		int res ;
		if (i < m) {

			res = get(i, 2 * x + 1, lx, m);
		}
		else {
			res = get(i, 2 * x + 2, m, rx);
		}
		return min(res, node[x]);

	}

	int get(int i) {

		return get(i, 0, 0, size);
	}


};


void solve()
{
	int n, k, m;
	cin >> n >> k >> m;
	vector<int>a(n);
	vector<vector<ll>>dp(n + 2, vector<ll>(k + 5, 0));
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i];
	}
	segtree st;
	st.init(n + 1);
	for (int i = 0; i < m; ++i)
	{
		int l, r, c;
		cin >> l >> r >> c;
		st.set(l - 1, r, c); //  [l,r)
	}
	vector<int>cost(n);
	for (int i = 0; i < n; ++i)
	{
		cost[i] = st.get(i);
	}
	for (int i = 1; i <= n; i++) {
		dp[i][0] += dp[i - 1][0] + a[i - 1];
	}
	for (int i = 1; i <= n; ++i)
	{
		for (int j = 1; j <= k; ++j)
		{
			dp[i][j] = dp[i - 1][j] + a[i - 1];
			if (j >= cost[i - 1]) {
				dp[i][j] = max(dp[i][j], dp[i - 1][j - cost[i - 1]]);
			}
		}
	}
	// cout << after << " " << before << endl;
	cout << dp[n][k] << endl;

}
int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}