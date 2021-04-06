#include <bits/stdc++.h>

using namespace std;

#define ar array
#define ll long long
#define mod (1LL<<32)
const int MAX_N = 1e5 + 1;
const int MOD = 1e9 + 7;
const int INF = 1e9;
const ll LINF = 1e18;


void solve() {
	bitset<INT_MAX> bits;
	ll q, s, a, b, ans = 0;
	cin >> q >> s >> a >> b;
	while (q--) {
		int x = s / 2;
		if (s & 1) {
			if (bits[x]==0) {
				bits[x] = 1;
				ans += x;
			}
		}
		else {
			if (bits[x]==1) {
				bits[x] = 0;
				ans -= x;
			}
		}
		s = (a * s + b) % mod;
	}
	cout << ans << endl;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
#ifndef ONLINE_JUDGE
	freopen("inputCC.txt", "r", stdin);
	freopen("outputCC.txt", "w", stdout);
#endif

	int tc = 1;
	//cin >> tc;
	for (int t = 1; t <= tc; t++) {
		// cout << "Case #" << t  << ": ";
		solve();
	}
	return 0;
}