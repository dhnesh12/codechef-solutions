#define wiwihorz 
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma loop-opt(on)

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define rrep(i, a, b) for(int i = b; i >= a; i --)
#define all(x) x.begin(), x.end()
#define ceil(a, b) ((a + b - 1) / (b))

#define MAXN 1000005
#define MAXP 10000000
#define MOD 1000000007
#define INF 1000000000ll
#define eps (1e-9)

#define int long long int
#define lld long double
#define pii pair<int, int>
#define random mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count())

using namespace std;
#ifdef wiwihorz
#define print(a...) kout("[" + string(#a) + "] = ", a)
void vprint(auto L, auto R) {
	while(L < R) cerr << *L << " \n"[next(L) == R], ++L;
} 
void kout() {cerr << endl;}
template<class T1, class ... T2> void kout(T1 a, T2 ... e) {
	cerr << a << " ", kout(e...);
}
#else 
#define print(...) 0
#define vprint(...) 0
#endif
int Q, K, C;
struct node {
	int lch, rch;
	int lmx, rmx, mx, sum;
};
node merge(node o, node a, node b) {
	o.sum = a.sum + b.sum;
	o.lmx = max(a.lmx, a.sum + b.lmx);
	o.rmx = max(b.rmx, b.sum + a.rmx);
	o.mx = max({a.mx, b.mx,a.rmx + b.lmx});
	return o;
}
struct seg : vector<node> {
	int p, t;
	void init(int _t) {
		assign(MAXP, {0, 0, 0, 0, 0, 0});
		p = 1, t = _t;
	}
	int get_new() {
		return ++p;
	}
	node get_id(node a) {
		a.lmx = a.rmx = a.mx = a.sum = 0;
		return a;
	}
	void push(int nd) {
		if(!at(nd).lch) at(nd).lch = get_new();
		if(!at(nd).rch) at(nd).rch = get_new();
		if(t == 1) {
			at(at(nd).lch) = merge(at(at(nd).lch), at(nd), at(at(nd).lch));
			at(at(nd).rch) = merge(at(at(nd).rch), at(nd), at(at(nd).rch));
		}
		else {
			at(at(nd).lch) = merge(at(at(nd).lch),at(at(nd).lch), at(nd));
			at(at(nd).rch) = merge(at(at(nd).rch),at(at(nd).rch), at(nd));
		} 
		at(nd) = get_id(at(nd));
	}
	void modify(int nd, int L, int R, int l, int r, node a) {
		if(l > R || r < L) return;
		if(l <= L && r >= R) {
			if(t == 1) at(nd) = merge(at(nd), a, at(nd));
			else at(nd) = merge(at(nd), at(nd), a);
		} 
		else {
			push(nd);
			int mid = (L + R) / 2;
			modify(at(nd).lch, L, mid, l, r, a);
			modify(at(nd).rch, mid + 1, R, l, r, a);
		}
		return;
	}
	node query(int nd, int L, int R, int id) {
		if(L == R) return at(nd);
		else {
			push(nd);
			int mid = (L + R) / 2;
			if(id <= mid) return query(at(nd).lch, L, mid, id);
			else return query(at(nd).rch, mid + 1, R, id); 
		}
	}
	node query_(int id) {
		return query(1, 1, INF, id);
	}
	void modify_(int id, int val) {
		int l = max(1ll, id - K);
		int r = min(INF, id + K);
//		print(l, r, val);
		int vv = max(val, 0ll);
		modify(1, 1, INF, l, r, {0, 0, vv, vv, vv, val});
		return;
	}
};
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin >> Q >> K;
	seg l, r;
	l.init(1), r.init(2);
	C = 0;
	rep(i, 1, Q) {
		int t, c, d;
		cin >> t;
		if(t == 1) {
			cin >> c >> d, c ^= C;
			l.modify_(c, d);	
		}
		else if(t == 2) {
			cin >> c >> d, c ^= C;
			r.modify_(c, d);
		}
		else {
			cin >> c, c ^= C;
			node a = l.query_(c);
			node b = r.query_(c);
//			print(a.lmx, a.rmx, a.mx);
//			print(b.lmx, b.rmx, b.mx);
			node ans = merge(a, a, b);
			C = ans.mx;
			cout << ans.mx << "\n";
		}
//		print(c);
	}
	return 0;
}