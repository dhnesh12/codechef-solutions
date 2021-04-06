#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define llu unsigned long long
#define ld long double
#define vi vector<int>
#define vll vector<ll>
#define pb push_back
#define pf push_front
#define pii pair<int, int>
#define pll pair<ll, ll>
#define mp make_pair
#define ff first
#define ss second
#define endl '\n'
#define sz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()
#define fill(x,v) fill(all(x), v)
#define sumv(v) accumulate(all(v), 0LL)
#define bitcount(x) __builtin_popcount(x)
#define present(v,x) ((v).find(x) != (v).end())
#define cpresent(v,x) (find(all(v),x) != (v).end())
#define v2(type, v, n, m) vector<vector<type>> v(n, vector<type>(m))
#define v3(type, v, x, y, z) vector<vector<vector<type>>> v(x, vector<vector<type>>(y, vector<type>(z)))
#define unique(v) {sort(all(v)); v.resize(unique(all(v))-v.begin());}

// const int MOD = 1000000007;
const int MOD = 998244353;
const int INF = 0x3f3f3f3f;
const ll INFLL = 0x3f3f3f3f3f3f3f3fLL;
const double EPS = 1e-6;

#define cerr cout
string to_string(string s) { return '"' + s + '"';}
string to_string(char s) { return string(1, s);}
string to_string(const char* s) { return to_string((string) s);}
string to_string(bool b) { return (b ? "true" : "false");}
string to_string(_Bit_reference b) { return (b ? "true" : "false");}
void debug_out() { cerr << ""; }
template <typename A> string to_string(A);
template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}
template <typename A> string to_string(A v) {bool f = 1; string r = "{"; for (const auto &x : v) {if (!f)r += ", "; f = 0; r += to_string(x);} return r + "}";}
template <typename Head, typename... Tail> void debug_out(Head H, Tail... T) {cerr << " " << to_string(H); debug_out(T...);}
#define pr(v, n) {for(int j=0; j<n; j++){debug_out(v[j]); if(j<n-1) cerr<<",";}}
#define dbg(...) {cerr << "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__); { cerr << endl; }}
#define dbg1d(v, n) {cerr << "[" << #v << "]: {"; pr(v, n); {cerr << " }" << endl;}}
#define dbg2d(v, n, m) {cerr<<"["<<#v<<"]:"<<endl;{for(int i=0; i<n; i++){cerr<<right<<setw(10)<<"["+to_string(i)+"] {";pr(v[i],m);{cerr<<" }"<<endl;}}}}
#define shout()  {cerr << "I'm Here...!!!" << endl;}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
random_device rd; mt19937 mt(rd()); uniform_int_distribution<long long> mtrng(1,LONG_LONG_MAX);
inline long long myRand() {return mtrng(mt);}

inline ll fpow(ll n, ll k, int p = MOD) {ll r = 1; for (; k; k >>= 1) {if (k & 1) r = r * n % p; n = (n%p) * (n%p) % p;} return r;}
inline int inv(ll a, int p = MOD) {return fpow(a, p - 2, p);}
inline int addmod(int a, int val, int p = MOD) {{if ((a = (a + val)) >= p) a -= p;} return a;}
inline int submod(int a, int val, int p = MOD) {{if ((a = (a - val)) < 0) a += p;}return a;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

// Define MAXN
#define MAXN 100005
struct query{
	int s, d; 
	inline bool operator!=(query a) {
       if (a.s!=s or a.d!=d)
          return true;
       else
          return false;
    }
};
const query ZERO = query({0, 0});

int t[4*MAXN][2];
query lazy[4*MAXN][2];
int rpow[MAXN][2], prpow[MAXN][2], rp[MAXN][2];

struct SegTree{
	int R, P1, P2;

	SegTree(int r, int p1, int p2): R(r), P1(p1), P2(p2){}

	void build(vector<int> &a, int v, int tl, int tr){
		if(tl==tr){
			t[v][0] = a[tr]%P1;
			t[v][1] = a[tr]%P2;
		}
		else{
			int tm = (tl + tr)/2;
			build(a, v*2, tl, tm);
			build(a, v*2+1, tm+1, tr);
			t[v][0] = addmod(t[v*2][0], t[v*2+1][0], P1); 
			t[v][1] = addmod(t[v*2][1], t[v*2+1][1], P2);
		}
		lazy[v][0] = ZERO;
		lazy[v][1] = ZERO;
	}

	void preCompute(int n){
		rpow[0][0] = 0;
		rpow[0][1] = 0;
		prpow[0][0] = 0;
		prpow[0][1] = 0;
		int rp1 = 1, rp2 = 1;
		rp[0][0] = rp1;
		rp[0][1] = rp2;
		for(int i=1; i<=n; i++){
			rpow[i][0] = addmod(rpow[i-1][0], rp1, P1);
			rpow[i][1] = addmod(rpow[i-1][1], rp2, P2);
			prpow[i][0] = addmod(prpow[i-1][0], mult(i-1, rp1, P1), P1);
			prpow[i][1] = addmod(prpow[i-1][1], mult(i-1, rp2, P2), P2);
			rp1 = mult(rp1, R, P1);
			rp2 = mult(rp2, R, P2);
			rp[i][0] = rp1;
			rp[i][1] = rp2;
		}
	}

	int getSum(int s, int d, int n, int pi){
		int p;
		if(pi==0)
			p = P1;
		else
			p = P2;
		int r1 = mult(s, rpow[n][pi], p);
		int r2 = mult(d, prpow[n][pi], p);
		return addmod(r1, r2, p);
	}

	void push(int v, int tl, int tr){
		int s1 = lazy[v][0].s;
		int d1 = lazy[v][0].d;
		int s2 = lazy[v][1].s;
		int d2 = lazy[v][1].d;
		if(lazy[v][0]!=ZERO)
			t[v][0] = addmod(t[v][0], getSum(s1, d1, tr-tl+1, 0), P1);
		if(lazy[v][1]!=ZERO)
			t[v][1] = addmod(t[v][1], getSum(s2, d2, tr-tl+1, 1), P2);
		if(tl!=tr){
			lazy[v*2][0].s = addmod(lazy[v*2][0].s, lazy[v][0].s, P1);
			lazy[v*2][0].d = addmod(lazy[v*2][0].d, lazy[v][0].d, P1);
			lazy[v*2][1].s = addmod(lazy[v*2][1].s, lazy[v][1].s, P2);
			lazy[v*2][1].d = addmod(lazy[v*2][1].d, lazy[v][1].d, P2);
			int tm = (tl+tr)/2;
			int d1_ = mult(d1, rp[tm+1-tl][0], P1);
			int s1_ = addmod(mult(s1, rp[tm+1-tl][0], P1), mult(tm+1-tl, d1_, P1), P1);
			int d2_ = mult(d2, rp[tm+1-tl][1], P2);
			int s2_ = addmod(mult(s2, rp[tm+1-tl][1], P2), mult(tm+1-tl, d2_, P2), P2);
			lazy[v*2+1][0].s = addmod(lazy[v*2+1][0].s, s1_, P1);
			lazy[v*2+1][0].d = addmod(lazy[v*2+1][0].d, d1_, P1);
			lazy[v*2+1][1].s = addmod(lazy[v*2+1][1].s, s2_, P2);
			lazy[v*2+1][1].d = addmod(lazy[v*2+1][1].d, d2_, P2);
		}
		lazy[v][0] = ZERO;
		lazy[v][1] = ZERO;
	}

	void updateRange(int v, int tl, int tr, int l, int r, int s1, int d1, int s2, int d2){
		if(lazy[v][0]!=ZERO or lazy[v][1]!=ZERO)
			push(v, tl, tr);
		if(l>r)
			return;
		if(l==tl and r==tr){
			lazy[v][0] = {s1, d1};
			lazy[v][1] = {s2, d2};
			push(v, tl, tr);
		}
		else{
			int tm = (tl + tr)/2;
			int sz = max(l, tm+1)-l;
			updateRange(v*2, tl, tm, l, min(r, tm), s1, d1, s2, d2);
			int d1_ = mult(d1, rp[sz][0], P1);
			int s1_ = addmod(mult(s1, rp[sz][0], P1), mult(sz, d1_, P1), P1);
			int d2_ = mult(d2, rp[sz][1], P2);
			int s2_ = addmod(mult(s2, rp[sz][1], P2), mult(sz, d2_, P2), P2);
			updateRange(v*2+1, tm+1, tr, max(l, tm+1), r, s1_, d1_, s2_, d2_);
			t[v][0] = addmod(t[v*2][0], t[v*2 + 1][0], P1);
			t[v][1] = addmod(t[v*2][1], t[v*2 + 1][1], P2);
		}
	}

	void updatePoint(int v, int tl, int tr, int pos, int g){
		if(lazy[v][0]!=ZERO or lazy[v][1]!=ZERO)
			push(v, tl, tr);
		if(pos<tl or pos>tr)
			return;
		if(tl==pos and tr==pos){
			t[v][1] = fpow(t[v][1], g, P2);
			t[v][0] = t[v][1]%P1;
		}
		else{
			int tm = (tl+tr)/2;
			updatePoint(v*2, tl, tm, pos, g);
			updatePoint(v*2+1, tm+1, tr, pos, g);
			t[v][0] = addmod(t[v*2][0], t[v*2 + 1][0], P1);
			t[v][1] = addmod(t[v*2][1], t[v*2 + 1][1], P2);
		}
	}

	int sum(int v, int tl, int tr, int l, int r){
		if(l>r)
			return 0;
		if(lazy[v][0]!=ZERO or lazy[v][1]!=ZERO)
			push(v, tl, tr);
		if(l==tl and r==tr)
			return t[v][0];
		int tm = (tl + tr)/2;
		return addmod(sum(v*2, tl, tm, l, min(r, tm)), sum(v*2+1, tm+1, tr, max(l, tm+1), r), P1);
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t;
	cin >> t;
	while(t--){
		int n, q, r, p1, p2;
		cin >> n >> q >> r >> p1 >> p2;

		vector<int> a(n+1);
		for(int i=1; i<=n; i++)
			cin >> a[i];

		SegTree T(r, p1, p2);
		T.build(a, 1, 1, n);
		T.preCompute(n);

		while(q--){
			int op;
			cin >> op;
			if(op==0){
				int s, d, x, y;
				cin >> s >> d >> x >> y;
				T.updateRange(1, 1, n, x, y, s%p1, d%p1, s%p2, d%p2);
			}
			if(op==1){
				int x, g;
				cin >> x >> g;
				T.updatePoint(1, 1, n, x, g);
			}
			if(op==2){
				int x, y;
				cin >> x >> y;
				cout << T.sum(1, 1, n, x, y) << endl;
			}
		}
	}

	return 0;
}