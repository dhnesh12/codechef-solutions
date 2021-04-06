#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
// #define int long long
#define ll long long
#define FILE_READ_IN freopen("input.txt","r",stdin);
#define FILE_READ_OUT freopen("output.txt","w",stdout);
#define Fast ios_base::sync_with_stdio(false);cin.tie();cout.tie();
#define deb(x) cout<<#x<<" "<<x<<endl;
#define all(v) v.begin(),v.end()
#define endl '\n'
using namespace __gnu_pbds;
using namespace std;

// template <typename T>
// using ordered_set =
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

void judge() {
#ifndef ONLINE_JUDGE
	FILE_READ_IN
	FILE_READ_OUT
#endif
}
const int N = 1e6 + 2;
int a[N];
int l[N];
int r[N];

signed main() {
	Fast;
	int t = 1;
	judge();
	// cin >> t;
	while (t--) {
		int n, q;
		cin >> n >> q;
		for (int i = 1; i <= n; i++)cin >> a[i];
		a[0] = 1e9 + 7;
		a[n + 1] = 1e9 + 7;
		l[1] = 1;
		for (int i = 2; i <= n; i++) {
			if (a[i] % a[i - 1] == 0)l[i] = l[i - 1];
			else
				l[i] = i;
		}
		r[n] = n;
		for (int i = n - 1; i >= 1; i--) {
			if (l[i] == l[i + 1])r[i] = r[i + 1];
			else
				r[i] = i;
		}
		set<array<int, 2>> s;
		s.insert({0, 0});
		s.insert({n + 1, n + 1});
		for (int i = 1; i <= n; i++) {
			s.insert({l[i], r[i]});
		}
		// for (auto i : s) {
		// 	cout << i[0] << " " << i[1] << endl;
		// }
		while (q--) {
			int op, b, c;
			cin >> op >> b;
			if (op == 1) {
				cin >> c;
				auto x = s.upper_bound({b, INT_MAX});
				// cout << (*x)[0] << " " << (*x)[1] << endl;
				auto z = x;
				x--;
				a[b] = c;
				auto y = *x;
				// cout << y[0] << " " << y[1] << endl;
				x--;
				auto w = x;
				x++;
				s.erase(x);
				int l = y[0], r = y[1];
				// cout << b << " " << c << " " << l << " " << r << endl;
				if (b > l && b < r) {
					if (a[b] % a[b - 1] != 0) {
						s.insert({y[0], b - 1});
						l = b;
					}
					if (a[b + 1] % a[b] != 0) {
						s.insert({b + 1, y[1]});
						r = b;
					}
					s.insert({l, r});
					continue;
				}
				if (b == l) {
					if (a[b] % a[b - 1] == 0) {
						l = (*w)[0];
						s.erase(w);
					}
					if (a[b + 1] % a[b] != 0) {
						if (r != b)s.insert({b + 1, r});
						r = b;
					}
				}
				if (b == r) {
					if (a[b + 1] % a[b] == 0) {
						r = (*z)[1];
						s.erase(z);
					}
					if (a[b] % a[b - 1] != 0) {
						if (l != b)s.insert({l, b - 1});
						l = b;
					}
				}
				s.insert({l, r});
			}
			else {
				auto x = s.upper_bound({b, INT_MAX});
				x--;
				auto y = *x;
				cout << y[0] << endl;
			}
			// for (auto i : s) {
			// 	cout << i[0] << " " << i[1] << endl;
			// }
		}
	}
}