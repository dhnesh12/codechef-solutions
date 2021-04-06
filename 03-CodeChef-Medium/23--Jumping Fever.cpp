#include "bits/stdc++.h"
using namespace std;
#ifndef LOCAL
#define endl '\n'
#endif

#define fr(i, a, b) for(int i = a; i <= b; i++)
#define rf(i, a, b) for(int i = a; i >= b; i--)
#define pf push_front
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define rall(x) x.rbegin(), x.rend()
#define sz(x) (int)x.size()
#define rsz resize()
#define lb lower_bound
#define ub upper_bound
#define br cout << endl

typedef long long ll;
typedef long double f80;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

int pct(int x) { return __builtin_popcount(x); }
int pct(ll x) { return __builtin_popcountll(x); } 
int bit(int x) { return 31 - __builtin_clz(x); } // floor(log2(x))
int bit(ll x) { return 63 - __builtin_clzll(x); } // floor(log2(x))
int cdiv(int a, int b) { return a / b + !(a < 0 || a % b == 0); }
ll cdiv(ll a, ll b) { return a / b + !(a < 0 || a % b == 0); }

template<typename T>
void leftShift(vector<T> &v, ll k) { k %= sz(v); if(k < 0) k += sz(v); rotate(v.begin(), v.begin() + k, v.end()); }
template<typename T>
void rightSift(vector<T> &v, ll k) { leftShift(v, sz(v) - k); }

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

ll rand(ll l, ll r){
	uniform_int_distribution<ll> uid(l, r);
	return uid(rng);
}

inline int nxt() {
	int x;
	cin >> x;
	return x;
}

inline ll nxtll() {
	ll x;
	cin >> x;
	return x;
}

void pr() {}
void sc() {}

template <typename Head, typename... Tail>
void pr(Head H, Tail... T) { cout << H << " "; pr(T...); }

template <typename Head, typename... Tail>
void sc(Head &H, Tail &... T) { cin >> H; sc(T...); }

#ifdef LOCAL
#define debug(...) cerr << "[L:" << __LINE__ << "][" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
#else
#define debug(...) 42
#endif

#ifndef LOCAL
string to_string(__int128 x) {
	string s = "";
	bool neg = 0;
	if(x < 0) { s += "-"; neg = 1; x = -x; }
	if(!x) s += '0';
	while(x) {
		int rem = x % 10;
		s += to_string(rem);
		x /= 10;
	}
	reverse(s.begin() + neg, s.end());
	return s;
}
#endif

const int mod = 1e9 + 7; // 998244353;

int pwr(int a,int b) {
	int ans = 1;
	while(b) {
		if(b & 1) ans = (ans * 1LL * a) % mod;
		a = (a * 1LL * a) % mod;
		b >>= 1;
	}
	return ans;
}

/*
	Lookout for overflows!!
	Check array sizes!!
	Clear before test cases!!
	Use the correct modulo!!
	Check for corner cases!!
	Are you forgetting something?!
	Read problem statement carefully!!!
*/

/**
 * Author: Simon Lindholm
 * Date: 2017-04-20
 * License: CC0
 * Source: own work
 * Description: Container where you can add lines of the form kx+m, and query maximum values at points x.
 *  Useful for dynamic programming (``convex hull trick'').
 * Time: O(\log N)
 * Status: stress-tested
 */

struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return k < o.k; }
	bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		if(empty()) return -1e18;
		auto l = *lower_bound(x);
		return l.k * x + l.m;
	}
};

const int N = 3e5 + 5;
ll a[N], depth[N], sz[N], s[N], p[N], r[N], dp[N], dp1[N];
ll ans = -1e18;
vector<int> g[N];

LineContainer ch[N], ch1[N];
int lol[N];

void pre_dfs(int u,int pp) {
	depth[u] = depth[pp] + 1;
	sz[u] = 1;
	s[u] = s[pp] + a[u];
	r[u] = r[pp] + s[u];
	p[u] = p[pp] + depth[u] * 1LL * a[u];
	for(int v : g[u]) {
		if(v != pp) {
			pre_dfs(v, u);
			sz[u] += sz[v];
		}
	}
}

void _add(int ss,int u) {
	ch[ss].add(s[u], p[u] + dp[u]);
}

ll _query(int ss, int u2, int u) {
	int l2 = depth[u2] - depth[u] - 1;
	ll x = l2 + 2 - depth[u];
	ll c = dp1[u2] - p[u] + depth[u] * s[u] - (l2 + 2) * s[u] + a[u] * (l2 + 2) + (r[u2] - r[u]) - (l2 + 1) * s[u];
	return ch[ss].query(x) + c;
}

void _add1(int ss,int u) {
	ch1[ss].add(depth[u], r[u] + dp1[u]);
}

ll _query1(int ss, int u2, int u) {
	int l2 = depth[u2] - depth[u] - 1;
	ll x = -2 * s[u] + a[u] + s[u2];
	ll c = dp[u2] + p[u2] - p[u] + 2 * depth[u] * s[u] - depth[u] * s[u2] + (-depth[u] + 1) * (s[u2] - s[u]) - r[u] - depth[u] * a[u] + a[u];
	return ch1[ss].query(x) + c;
}

void dfs2(int u2, int p, int u, bool add) {
	if(!add) {
		ans = max(ans, _query(lol[u], u2, u));
		ans = max(ans, _query1(lol[u], u2, u));
	}
	else {
		_add(lol[u], u2);
		_add1(lol[u], u2);
	}
	for(int v : g[u2]) {
		if(v != p) {
			dfs2(v, u2, u, add);
		}
	}
}

void dfs(int u,int p) {
	int hc = -1, S = -1;
	for(int v : g[u]) {
		if(v != p) {
			dfs(v, u);
			if(sz[v] > S) {
				S = sz[v], hc = v;
			}
		}
	}
	if(hc == -1) {
		lol[u] = u;
	}
	else {
		lol[u] = lol[hc];
	}
	for(int v : g[u]) {
		if(v != p && v != hc) {
			dfs2(v, u, u, 0);
			dfs2(v, u, u, 1);
		}
	}
	ll q = _query(lol[u], u, u);
	ll q1 = _query1(lol[u], u, u);
	dp[u] = max(q, 0LL);
	dp1[u] = max(q1, 0LL);
	ans = max(ans, q);
	ans = max(ans, q1);
	_add(lol[u], u);
	_add1(lol[u], u);
}

void solve() {
	ans = -1e18;
	int n;
	sc(n);
	fr(i, 1, n) {
		ch[i].clear();
		ch1[i].clear();
		dp[i] = dp1[i] = 0;
		r[i] = p[i] = s[i] = 0;
		g[i].clear();
		sc(a[i]);
	}
	fr(i, 1, n - 1) {
		int u, v;
		sc(u, v);
		g[u].pb(v);
		g[v].pb(u);
	}
	int r = 1;
	pre_dfs(r, 0);
	dfs(r, 0);
	pr(ans);
	br;
}

signed main() {
	ios :: sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	// t = 1;
	for(int tt = 1; tt <= t; tt++) {
		solve();
	}
	return 0;
}