#include<bits/stdc++.h>
using namespace std;
template <class T> ostream &operator << (ostream &os, const vector<T> &p) { os << "["; for (auto&it : p) os << it << " "; return os << "]";}
template <class S, class T> ostream &operator << (ostream &os, const pair<S, T> &p) { return os << "(" << p.first << "," << p.second << ")";}
#ifndef ONLINE_JUDGE
#define deb(...) dbs(#__VA_ARGS__,__VA_ARGS__)
template <class T> void dbs(string str, T t) { cerr << str << ":" << t << "\n";}
template<class T, class...S> void dbs(string str, T t, S... s) { int idx = str.find(','); cerr << str.substr(0, idx) << ":" << t << ","; dbs(str.substr(idx + 1), s...);}
#else
#define deb(...){}
#endif
#define int long long
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i,n) for(int i = 0; i < n; i++)
#define sz(x) (int)x.size()
#define nl cout<< '\n'
#define pr(x) {cout << x << "\n"; return;}
#define all(x) x.begin(), x.end()
#define re(i,n) for(int i = 1; i <= n; i++)
#define prl(x) {cout << x << "\n";}
#define ini(x, y) memset(x, y, sizeof(x))
#define fr(i,a,b) for(int i = a; i <= b; i++)
#define fb(i,a,b) for(int i = a; i >= b; i--)
#define vi vector<int>
#define pii pair<int, int>
#define vii vector<pii>
template<class T> bool umin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool umax(T &a, T b) { return a < b ? (a = b, true) : false; }
const int N = 2e5 + 10;

void solve() {
	int n; cin >> n;
	vi a(n); rep(i, n) cin >> a[i];
	vi b(n); rep(i, n) cin >> b[i];
	fb(i, n - 1, 2) {
		if (a[i] > b[i]) pr("NIE");
		if ((b[i] - a[i]) % 3 > 0) pr("NIE");
		int x = (b[i] - a[i]) / 3;
		a[i - 1] += 2 * x;
		a[i - 2] += x;
	}
	if (a[0] != b[0]) pr("NIE");
	if (n > 1 && a[1] != b[1]) pr("NIE");
	pr("TAK");

}
signed main() {
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("ouyput.txt", "w", stdout);
#endif
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
}