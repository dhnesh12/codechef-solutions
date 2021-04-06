#include <bits/stdc++.h>
using namespace std;

#define ll long long 
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define MOD 1000000007

const ll MAX = (ll)1e18;
const ll MIN = (ll)-1e18;

void __print(int x) {cerr << x;}
void __print(long x) {cerr << x;}
void __print(long long x) {cerr << x;}
void __print(unsigned x) {cerr << x;}
void __print(unsigned long x) {cerr << x;}
void __print(unsigned long long x) {cerr << x;}
void __print(float x) {cerr << x;}
void __print(double x) {cerr << x;}
void __print(long double x) {cerr << x;}
void __print(char x) {cerr << '\'' << x << '\'';}
void __print(const char *x) {cerr << '\"' << x << '\"';}
void __print(const string &x) {cerr << '\"' << x << '\"';}
void __print(bool x) {cerr << (x ? "true" : "false");}

template<typename T, typename V>
void __print(const pair<T, V> &x) {cerr << '{'; __print(x.first); cerr << ','; __print(x.second); cerr << '}';}
template<typename T>
void __print(const T &x) {int f = 0; cerr << '{'; for (auto &i: x) cerr << (f++ ? ", " : ""), __print(i); cerr << "}";}
void _print() {cerr << "]\n";}
template <typename T, typename... V>
void _print(T t, V... v) {__print(t); if (sizeof...(v)) cerr << ", "; _print(v...);}
#ifndef ONLINE_JUDGE
#define debug(x...) cerr << "[" << #x << "] = ["; _print(x)
#else
#define debug(x...)
#endif

const ll N = 100100;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	int t; cin >> t;
	while (t--) {	
		int n, m;
		cin >> n >> m;
		ll a[n][m];
		map<ll, ll> h;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> a[i][j];
				h[a[i][j]]++;
			}
		}
		if (m == 1) {
			for (int i = 0; i < n; ++i) {
				cout << a[i][0] << "\n";
			}cout << endl;
			continue;
		}
		// debug(h);
		vector<vector<ll>> ans(n, vector<ll>(m, 0));
		int row = 0, col = 0;
		for (auto x: h) {
			debug(x);
			ll freq = x.second;
			for (int i = 0; i < freq / 2; i++) {
				debug(row, col);
				debug(row, m - col - 1);
				ans[row][col] = x.first;
				ans[row][m - 1 - col] = x.first;
				if (col == (m / 2) - 1) {
					col = 0;
					++row;
				}
				else {
					col++;
				}
				h[x.first] -= 2;
				if (row == n) {
					break;
				}
			}
			if (row == n) {
				break;
			}
		}

		// debug(h);

		if (m % 2 == 1) {
			int row = 0;
			for (auto x: h) {
				for (int i = 0; i < x.second; ++i) {
					ans[row][m / 2] = x.first;
					++row;
					if (row == n) break;
				}
				if (row == n) break;
			}
		}

		bool ok = 1;
		for (auto x: ans) {
			for (auto y: x) {
				if (y == 0) {
					ok = 0;
					break;
				}
			}
			if (!ok) break;
		}

		if (ok) {
			for (int i = 0; i < n; ++i) {
				for (int j = 0; j < m; ++j) {
					cout << ans[i][j] << " ";
				}cout << endl;
			}
		}
		else cout << "-1\n";
	}

	return 0;
}
