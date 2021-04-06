#include <bits/stdc++.h>
using namespace std;

template <typename A, typename B> string to_string(pair<A, B> p);
string to_string(const char& ch) { return "'" + string(1, ch) + "'"; }
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string((string) s); }
string to_string(bool b) { return (b ? "true" : "false"); }
string to_string(vector<bool> v) {
	bool first = true; string res = "{";
	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		if (!first) { res += ", "; }
		first = false; res += to_string(v[i]);
	}
	res += "}"; return res;
}
template <typename A> string to_string(A v) {
	bool first = true; string res = "{";
	for (const auto &x : v) {
		if (!first) { res += ", "; }
		first = false; res += to_string(x);
	}
	res += "}"; return res;
}
template <typename A, typename B> string to_string(pair<A, B> p) {
	return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}
#define output cout
void debug_out() { output << endl; }
template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
	output << " " << to_string(H);
	debug_out(T...);
}
#ifndef ONLINE_JUDGE
#define dbg(...) output << "[" << #__VA_ARGS__ << "] :", debug_out(__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define ll int64_t
#define ull uint64_t
#define lld long double
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define vt vector
#define vll vt<ll>
#define pll pair<ll,ll>
#define vpll vt<pll>
#define vvll vt<vll>
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(), v.rend()
#define FOR(i,n) for(ll i=0;i<n;i++)
#define ffo(i,a,b) for(ll i=a;i<=b;i++)
#define rfo(i,a,b) for(ll i=a;i>=b;i--)
template <typename T> using mxpq = priority_queue<T>;
template <typename T> using mnpq = priority_queue<T, vt<T>, greater<T>>;
#define fps(x,y) fixed << setprecision(y) << x
#define mmss(xa,v) memset(xa,v,sizeof(xa)) // use only if v = -1 or 0, else use fill

template<typename T1, typename T2>
istream& operator>>(istream& in, pair<T1, T2> &a) {in >> a.ff >> a.ss; return in;}
template<typename T1, typename T2>
ostream& operator<<(ostream& out, pair<T1, T2> a) {out << a.ff << " " << a.ss; return out;}
template<typename T, typename T1>
T amax(T &a, T1 b) {if (b > a) a = b; return a;}
template<typename T, typename T1>
T amin(T &a, T1 b) {if (b < a) a = b; return a;}
template <class A, size_t S>
istream& operator>>(istream& in, array<A, S>& a) { for (A& x : a) in >> x; return in; }
template <class A, size_t S>
ostream& operator<<(ostream& out, array<A, S>& a) {
	bool f = false; for (A& x : a) { if (f) out << " "; out << x; f = true; } return out;
}
template <typename T> istream& operator>>(istream& in, vt<T>& a)
{ for (T& x : a) in >> x; return in; }
template <typename T> ostream& operator<<(ostream& out, vt<T>& a) {
	bool f = false; for (T& x : a) {if (f) out << " "; out << x; f = true; } return out;
}

int dx[4] = { -1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
// up, right, down, left

const lld PI = 3.14159265359;
const ll INF = 2e18;
const ll N = 1e6 + 6;
const ll MAX_SIZE = 2e6 + 6;
const ll mod = 163577857;

ll powerM(ll x, ll y, ll M = mod) { // default argument
	ll v = 1; x = x % M; while (y > 0) {if (y & 1)v = (v * x) % M; y = y >> 1; x = (x * x) % M;} return v;
}
ll power(ll x, ll y) {
	ll v = 1; while (y > 0) {if (y & 1)v = v * x; y = y >> 1; x = x * x;} return v;
}
int largest_bit(long long x) { // based on 0-indexing
	return x == 0 ? -1 : 63 - __builtin_clzll(x);
}

const ll maxN = 1e5 + 5;
/*
https://discuss.codechef.com/t/guide-to-modular-arithmetic-plus-tricks-codechef-edition-there-is-no-other-edition/67424/2
*/

ll fact[maxN], invfact[maxN], inverse[maxN];
ll modinv(ll a) {
	return powerM(a, mod - 2, mod);
}
ll nCr(ll n, ll r) {
	if (r > n || r < 0) return 0;
	return ((fact[n] * invfact[r]) % mod * invfact[n - r]) % mod;
}
ll nPr(ll n, ll r) {
	if (r > n || r < 0) return 0;
	return (fact[n] * invfact[n - r]) % mod;
}
void precomputenCr() {
	fact[0] = fact[1] = 1;
	for (ll i = 2; i < maxN; i++) {
		fact[i] = (fact[i - 1] * i) % mod;
	}
	/*
	n! = n * (n-1) !
	==> 1/(n-1!) = n/(n!)
	==> (1/(n-1!)) % M = (n/(n!)) % M
	==> (1/(n-1!)) % M = ((n % M) * ((1/(n!)) % M)) % M
	*/
	invfact[maxN - 1] = modinv(fact[maxN - 1]);
	for (ll i = maxN - 2; i >= 0; i--) {
		invfact[i] = invfact[i + 1] * (i + 1);
		invfact[i] %= mod;
	}
	/*
	==> 1/n = (n-1)!/(n!)
	*/
	for (ll i = 1; i < maxN; i++) {
		inverse[i] = (fact[i - 1] * invfact[i]) % mod;
	}
}
// calculate ncr without mod
ll defnCr(ll n, ll r) {
	if (r > n) return 0;
	ll v = 1;
	r = min(r, n - r);
	for (ll i = 1; i <= r; ++i) {
		v *= (n - (i - 1));
		v /= i;
	}
	return v;
	// can also use formula (n)C(r) = (n-1)C(r) + (n-1)C(r-1);
}


void preSolve() {
	precomputenCr();
}

void solve() {
	ll n;
	cin >> n;
	ll c0, c1, c_1;
	c0 = c1 = c_1 = 0;
	FOR(i, n) {
		ll x; cin >> x;
		if (x > 0) c1++;
		else if (x < 0) c_1++;
		else c0++;
	}
	for (ll sum = -n; sum <= n; sum++) {
		// Vandermonde's identity
		ll tmp = powerM(2, c0);
		if (sum < 0) {
			tmp *= nCr(c1 + c_1, c_1 + sum);
		} else if (sum == 0) {
			tmp *= nCr(c1 + c_1, c1);
		} else {
			tmp *= nCr(c1 + c_1, c1 - sum);
		}
		tmp %= mod;
		if (sum == 0) {
			// removing the empty set
			tmp -= 1;
			tmp += mod;
			tmp %= mod;
		}
		cout << tmp << " \n"[sum == n];
	}
}

signed main()
{
#ifdef LOCAL
	freopen("in1.txt", "r", stdin);
	freopen("out1.txt", "w", stdout);
#endif
	FIO;
	preSolve();
	int testcases = 1;
	cin >> testcases;
	for (int caseno = 1; caseno <= testcases; ++caseno) {
		// cout << "Case #" << caseno << ": ";
		solve();
		// cout << endl;
	}
	return 0;
}

/*
On getting WA:
1. Check if implementation is correct and NOTHING overflows.
2. Start thinking about counter cases for your logic as well as implementation.
3. Try removing redundancy (any additon you might have done for ease of
   implementation or thought process) and putting asserts.
4. Make a generator, an unoptimized but correct soln and run it against wrong soln.


Things you may rarely use:

In C++, comparator should return false if its arguments are equal.
#define _GLIBCXX_DEBUG // Use at the top of code
cerr << "[Execution : " << (1.0 * clock()) / CLOCKS_PER_SEC << "s]\n";
int dx[] = {+1,-1,+0,+0,-1,-1,+1,+1}; // Eight Directions
int dy[] = {+0,+0,+1,-1,+1,-1,-1,+1}; // Eight Directions
int dx[]= {-2,-2,-1,1,-1,1,2,2}; // Knight moves
int dy[]= {1,-1,-2,-2,2,2,-1,1}; // Knight moves
For taking a complete line as input: string s; while(s == "") getline(cin, s);
For calculating inverse modulo, raise to the power mod-2.
For (a^b)%mod, where b is large, replace b by b%(mod-1).
x | (x + 1) sets lowest unset bit of x
x & (x - 1) unsets lowest set bit of x
x - 1 unsets the lowest set bit and sets all bits on it's right
arr.erase(unique(all(arr)), arr.end()); // erase duplicates
#define merg(a,b,c) set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()))
https://www.techiedelight.com/merge-two-sets-set_union-merge-cpp/

#pragma GCC optimize "trapv" // catches integer overflows
#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2,fma")

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <typename T> using oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
functions: set.insert(val), *(set.find_by_order(order-1)), set.order_of_key(val)
less_equal for multiset

#include <ext/pb_ds/priority_queue.hpp>
template<typename T> using pbds_pq = __gnu_pbds::priority_queue<T>;
template<typename T> using pbds_min_pq = __gnu_pbds::priority_queue<T, greater<T>>;
*/
