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

void solve() {
	int n;
	cin >> n;
	vector<int> a(n);
	for (auto &it : a)
		cin >> it;
	int cnt = 0, mx = 0, total = 0;
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++) {
			total++;
			if (a[i] + a[j] > mx) {
				mx = a[i] + a[j];
				cnt = 1;
			} else if (a[i] + a[j] == mx)
				cnt++;
		}
	cout << 1.0 * cnt / total << endl;
}

int main() {
	run();
	cout << fixed << setprecision(10);
	int T;
	cin >> T;
	while (T--) {
		solve();
	}
}
