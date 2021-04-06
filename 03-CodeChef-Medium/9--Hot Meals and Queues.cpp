#include <bits/stdc++.h>
using namespace std;
#ifdef LOCAL
string to_string(string s) { return '"' + s + '"'; }
string to_string(const char* s) { return to_string(string(s)); }
string to_string(bool b) { return to_string(int(b)); }
string to_string(vector<bool>::reference b) { return to_string(int(b)); }
string to_string(char b) { return "'" + string(1, b) + "'"; }
template <typename A, typename B>
string to_string(pair<A, B> p) { return "(" + to_string(p.first) + ", " + to_string(p.second) + ")"; }
template <typename A>
string to_string(A v) {
	string res = "{";
	for (const auto& x : v) res += (res == "{" ? "" : ", ") + to_string(x);
	return res + "}";
}
void debug() { cerr << endl; }
template <typename Head, typename... Tail>
void debug(Head H, Tail... T) {
	cerr << " " << to_string(H);
	debug(T...);
}
#define db(...) cerr << "[" << #__VA_ARGS__ << "]:", debug(__VA_ARGS__)
#else
#define db(...) 42
#endif
typedef long long ll;
typedef long double ld;
struct SegTree {
	struct Node {
		ll mx = 0; // Set default value here
		int leftMaxima = 0;
		ll prop = 0;
		// Used for updates and propagation.
		void apply(int s, int e, ll v) {
			mx += v;
			prop += v;
		}
	};
	int start, end;
	vector<Node> tree;
	inline void push(int sn, int s, int e) {
		if (tree[sn].prop) {
			int m = (s + e) >> 1, lsn = sn * 2, rsn = sn * 2 + 1;
			tree[lsn].apply(s, m, tree[sn].prop);
			tree[rsn].apply(m + 1, e, tree[sn].prop);
			tree[sn].prop = 0;
		}
	}
	int getBigger(int sn, int s, int e, ll v) {
		if (s == e) return tree[sn].mx > v;
		int m = (s + e) >> 1, lsn = sn * 2, rsn = sn * 2 + 1;
		push(sn, s, e);
		if (tree[rsn].mx <= v) return getBigger(lsn, s, m, v);
		return tree[sn].leftMaxima + getBigger(rsn, m + 1, e, v);
	}
	inline Node combine(const Node& a, const Node& b, int lsn, int s, int m) {
		Node res;
		res.mx = max(a.mx, b.mx);
		res.leftMaxima = getBigger(lsn, s, m, b.mx);
		return res;
	}
	template <typename T>
	void build(int sn, int s, int e, const vector<T>& v) {
		if (s == e) {
			tree[sn].mx = v[s];
			return;
		}
		int m = (s + e) >> 1, lsn = sn * 2, rsn = sn * 2 + 1;
		build(lsn, s, m, v);
		build(rsn, m + 1, e, v);
		tree[sn] = combine(tree[lsn], tree[rsn], lsn, s, m);
	}
	template <typename... T>
	void update(int sn, int s, int e, int qs, int qe, const T&... v) {
		if (qs <= s && e <= qe) {
			tree[sn].apply(s, e, v...);
			return;
		}
		int m = (s + e) >> 1, lsn = sn * 2, rsn = sn * 2 + 1;
		push(sn, s, e);
		if (qs <= m) update(lsn, s, m, qs, qe, v...);
		if (qe > m) update(rsn, m + 1, e, qs, qe, v...);
		tree[sn] = combine(tree[lsn], tree[rsn], lsn, s, m);
	}
	void query(int sn, int s, int e, int qs, int qe, const function<void(Node&, int, int, int)>& f) {
		if (qs <= s && e <= qe) return f(tree[sn], sn, s, e);
		int m = (s + e) >> 1, lsn = sn * 2, rsn = sn * 2 + 1;
		push(sn, s, e);
		if (qe > m) query(rsn, m + 1, e, qs, qe, f);
		if (qs <= m) query(lsn, s, m, qs, qe, f);
	}
	template <typename T>
	SegTree(const vector<T>& v) {
		int n = v.size();
		int maxs = n == 1 ? 2 : 1 << (33 - __builtin_clz(n - 1));
		tree.resize(maxs);
		start = 0;
		end = n - 1;
		build(1, start, end, v);
	}
	void query(int qs, int qe, const function<void(Node&, int, int, int)>& f) {
		if (qs > qe) return;
		query(1, start, end, qs, qe, f);
	}
	template <typename... T>
	void update(int qs, int qe, const T&... v) {
		update(1, start, end, qs, qe, v...);
	}
};
int main() {
	int n;
	scanf("%d", &n);
	vector<int> A(n);
	for (int i = 0; i < n; ++i) {
		scanf("%d", &A[i]);
		A[i] -= i;
	}
	SegTree st(A);
	auto solve = [&](int l, int r) {
		ll curMax = LLONG_MIN;
		int ans = r - l + 1;
		st.query(l, r, [&](SegTree::Node& x, int sn, int s, int e) {
			ans -= st.getBigger(sn, s, e, curMax);
			curMax = max(curMax, x.mx);
		});
		printf("%d\n", ans);
	};
	solve(0, n - 1);
	int q;
	scanf("%d", &q);
	while (q--) {
		int t, l, r;
		scanf("%d%d%d", &t, &l, &r);
		--l;
		--r;
		if (t == 1) {
			solve(l, r);
		} else {
			int w;
			scanf("%d", &w);
			st.update(l, r, w);
		}
	}
}