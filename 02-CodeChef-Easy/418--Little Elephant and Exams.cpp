#include <bits/stdc++.h>
#include <unordered_map>
#include <unordered_set>
using namespace std;
#define endl "\n"
#define ll long long
#define sz(s) (int)(s.size())
#define INF 0x3f3f3f3f3f3f3f3fLL
#define all(v) v.begin(),v.end()
#define watch(x) cout<<(#x)<<" = "<<x<<endl
const int dr[] { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dc[] { 0, 1, 1, 1, 0, -1, -1, -1 };
#if __cplusplus >= 201402L
template<typename T>
vector<T> create(size_t n) {
	return vector<T>(n);
}
template<typename T, typename ... Args>
auto create(size_t n, Args ... args) {
	return vector<decltype(create<T>(args...))>(n, create<T>(args...));
}
#endif
void run() {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
#ifndef ONLINE_JUDGE
	freopen("input.in", "r", stdin);
#else
	//freopen("groups.in", "r", stdin);
#endif
}

const int M = 16;
double dp[M + 1][1 << M];
int main() {
	run();
	int T;
	cin >> T;
	while (T--) {
		int n;
		cin >> n;
		vector<tuple<int, int, int>> v(n);
		for (auto &it : v) {
			int p, a, b;
			cin >> p >> a >> b;
			a--;
			b--;
			it = tie(a, b, p);
		}
		if (n > M) {
			cout << 0 << endl;
			continue;
		}
		fill(dp[n], dp[n] + (1 << M), 1);
		for (int i = n - 1; i >= 0; i--) {
			int p, a, b;
			tie(a, b, p) = v[i];
			for (int mask = 0; mask < (1 << M); mask++) {
				double &res = dp[i][mask];
				res = 0;
				if ((mask & (1 << a)) == 0)
					res += dp[i + 1][mask | (1 << a)] * p / 100;
				if ((mask & (1 << b)) == 0)
					res += dp[i + 1][mask | (1 << b)] * (100 - p) / 100;
			}
		}
		cout << fixed << setprecision(10) << dp[0][0] << endl;
	}
}
