#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include<bits/stdc++.h>
using namespace std;
template <class T> ostream &operator << (ostream &os, const vector<T> &p) { os << "["; for (auto&it : p) os << it << " "; return os << "]";}
template <class T> ostream &operator << (ostream &os, const set<T>&p) { os << "["; for (auto&it : p) os << it << " "; return os << "]";}
template <class T> ostream &operator << (ostream &os, const multiset<T>&p) { os << "["; for (auto&it : p) os << it << " "; return os << "]";}
template <class S, class T> ostream &operator << (ostream &os, const map<S, T> &p) { os << "["; for (auto&it : p) os << it << " "; return os << "]";}
template <class S, class T> ostream &operator << (ostream &os, const pair<S, T> &p) { return os << "(" << p.first << "," << p.second << ")";}
template <class S, class T> ostream &operator << (ostream &os, const unordered_map<S, T> &v) { for (auto i : v) os << '(' << i.first << "=>" << i.second << ')' << ' '; return os;}
#ifndef ONLINE_JUDGE
#define debarr(a, x, y) cerr << (#a) << ":"; for(int i = x; i <= y; i++) cerr << a[i] << " " ; cerr<< endl;
#define debmat(mat, row, col)  cerr << (#mat) << ":\n"; for(int i = 0; i < row; i++){ for(int j = 0; j < col; j++) cerr << mat[i][j] << " "; cerr << endl;}
#define deb(...) dbs(#__VA_ARGS__,__VA_ARGS__)
template <class T> void dbs(string str, T t) { cerr << str << ":" << t << "\n";}
template<class T, class...S>void dbs(string str, T t, S... s) { int idx = str.find(','); cerr << str.substr(0, idx) << ":" << t << ","; dbs(str.substr(idx + 1), s...);}
#else
#define deb(...){}
#define debarr(a,x,y){}
#define debmat(mat,row,col){}
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
const int N = 1e3 + 10;

const int mod = 1e9 + 7; // 998244353;
int powm(int a, int b) { int res = 1; while (b) { if (b & 1) res = (res * a) % mod; a = (a * a) % mod; b >>= 1;} return res;}
int modinv(int a) { return powm(a, mod - 2);}
void add(int &a, int b) { a = (a + b); if (a >= mod) a -= mod;}
void sub(int &a, int b) { a = (a - b); if (a < 0) a += mod;}
void mult(int &a, int b) { a = (a * b) % mod;}
void divide(int &a, int b) { a = a * modinv(b) % mod;}
int mul(int a, int b) { return (a * b) % mod;}
const int maxN = 1e3 + 10;
int fact[maxN], ifact[maxN];
void factorial() {
	fact[0] = 1;
	for (int i = 1; i < maxN; i++) fact[i] = (fact[i - 1] * i) % mod;
	ifact[maxN - 1] = powm(fact[maxN - 1], mod - 2);
	for (int i = maxN - 2; i >= 0; i--) ifact[i] = (ifact[i + 1] * (i + 1)) % mod;
}

int C(int n, int r) { if (n < r || r < 0 || n < 0) return 0; return mul(fact[n], mul(ifact[r], ifact[n - r]));}

int a[N], n, k, idx = 0;
int dp[N][N], pre[N];

void solve() {
	cin >> n >> k;
	map<int, int> m;
	rep(i, n) {
		int x; cin >> x;
		m[x]++;
	}
	for (auto u : m) a[idx++] = u.se;
	dp[0][0] = 1;
	rep(i, idx) {
		rep(j, k + 1) {
			if (dp[i][j] > 0) {
				for (int l = 0; l + j <= k; l++) {
					add(dp[i + 1][l + j], mul(dp[i][j], mul(C(a[i], l), fact[l])));
				}
			}
		}
	}
	int ans = dp[idx][k];
	divide(ans, mul(fact[k], C(n, k)));
	pr(ans);
}

signed main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int q = 1;
	factorial();
	// cin >> q;
	while (q--) solve();
	return 0;
}