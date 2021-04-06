#include <bits/stdc++.h>

using namespace std;

#define INF 		INT_MAX
#define NINF 		INT_MIN
#define ll 			long long
#define ull 			unsigned ll
#define vi 			vector<int>
#define vb 			vector<bool>
#define vvi 			vector<vi>
#define vll 		vector<long long>
#define pii 		pair<int,int>
#define vpii		vector<pii>
#define push_back 	pb

const ll M = 1e9 + 7;

void solve() {
	int n, m, k;
	ll ans = 0;
	cin >> n >> m >> k;
	map<int, map<int, int>> A;
	// vvi grid(n, vi(m, 0));
	int dx[] = {1, 0, -1, 0};
	int dy[] = {0, 1, 0, -1};


	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		// grid[x - 1][y - 1] = 1;
		for (int i = 0; i < 4; i++) {
			int ndx = x + dx[i];
			int ndy = y + dy[i];
			ans += A[ndx][ndy] ? -1 : 1;
		}
		A[x][y] = 1;
	}
	cout << ans << "\n";
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;

	while (t--)
		solve();

	return 0;
}