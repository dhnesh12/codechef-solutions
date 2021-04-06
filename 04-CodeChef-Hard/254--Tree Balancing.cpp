#include <bits/stdc++.h>
#define ll long long
#define pll pair<ll,ll>
#define vec vector
using namespace std;

const ll INF = 1e18;

struct S {
	ll cl, cr, lazy;
	map<ll,ll> l, r;
	vec<vec<pll>> e;
	S() {cl = cr = lazy = 0;}
	inline void balance() {
		while (cl > cr) {
			auto it = --l.end();
			ll take = min((cl-cr)/2, it->second);
			it->second -= take;
			cl -= take;
			r[it->first] += take;
			cr += take;
			if (it->second == 0) l.erase(it);
		}
		while (cr > cl) {
			auto it = r.begin();
			ll take = min((cr-cl)/2, it->second);
			it->second -= take;
			cr -= take;
			l[it->first] += take;
			cl += take;
			if (it->second == 0) r.erase(it);
		}
	}
	inline void add(ll pos, ll val) {
		pos -= lazy;
		if (cr>0 && pos<r.begin()->first) {
			l[pos] += val;
			cl += val;
		}
		else {
			r[pos] += val;
			cr += val;
		}
	}
	inline void remove(ll pos, ll val) {
		pos -= lazy;
		auto il = l.find(pos);
		if (il != l.end()) {
			ll take = min(il->second, val);
			il->second -= take;
			val -= take;
			cl -= take;
			if (il->second == 0) l.erase(il);
		}
		auto ir = r.find(pos);
		if (ir != r.end()) {
			ll take = min(ir->second, val);
			ir->second -= take;
			val -= take;
			cr -= take;
			if (ir->second == 0) r.erase(ir);
		}
	}
	inline bool discard(ll val) {
		e.push_back(vec<pll>());
		while (cl > val) {
			auto it = l.begin();
			ll take = min(cl - val, it->second);
			it->second -= take;
			cl -= take;
			e.back().push_back({it->first, take});
			if (it->second == 0) l.erase(it);
		}
		while (cr > val) {
			auto it = --r.end();
			ll take = min(cr - val, it->second);
			it->second -= take;
			cr -= take;
			e.back().push_back({it->first, take});
			if (it->second == 0) r.erase(it);
		}
	}
	inline void restore() {
		for (auto x : e.back()) {
			if (x.first < r.begin()->first) {
				l[x.first] += x.second;
				cl += x.second;
			}
			else {
				r[x.first] += x.second;
				cr += x.second;
			}
		}
		e.pop_back();
	}
	inline ll middle() {return lazy + r.begin()->first;}
	inline int outside(ll pos, ll val) {
		pos -= lazy;
		if (cl < val) return 0;
		if (pos <= l.begin()->first) return 1;
		if (pos >= (--r.end())->first) return 2;
		return 0;
	}
	void debug() {
		cout << middle() << ' ' << lazy << ' ' << cl << ' ' << cr << '\n';
		cout << "L ";
		for (auto x : l) cout << '(' << x.first << ',' << x.second << ')' << ' '; cout << '\n';
		cout << "R ";
		for (auto x : r) cout << '(' << x.first << ',' << x.second << ')' << ' '; cout << '\n';
	}
};

vec<vec<ll>> adj, edg;
vec<S*> s;
vec<int> sz, big, par, ord;

inline int other(int e, int u) {
	if (edg[e][0] == u) return edg[e][1];
	else return edg[e][0];
}

void dfs() {
	stack<pll> st;
	st.push({0, 0});
	while (!st.empty()) {
		int u = st.top().first;
		int tp = st.top().second;
		st.pop();
		if (tp == 0) {
			st.push({u, 1});
			for (int e : adj[u]) {
				int v = other(e, u);
				if (v == par[u]) continue;
				par[v] = u;
				st.push({v, 0});
			}
		}
		else {
			int mx = 0;
			for (int e : adj[u]) {
				int v = other(e, u);
				if (v == par[u]) continue;
				sz[u] += sz[v];
				if (mx < sz[v]) {
					big[u] = e;
					mx = sz[v];
				}
			}
			ord.push_back(u);
		}
	}
}

void dfa(int u) {
	for (int e : adj[u]) {
		int v = other(e, u);
		if (v == par[u]) continue;
		s[v]->discard(edg[e][3]);
		s[v]->lazy += edg[e][2];
	}
	if (big[u] < 0) {
		s[u] = new S();
		s[u]->add(0, 2*INF);
		s[u]->balance();
	}
	else {
		s[u] = s[other(big[u], u)];
		for (int e : adj[u]) {
			int v = other(e, u);
			if (v == par[u] || e == big[u]) continue;
			for (auto &x : s[v]->l) s[u]->add(x.first + s[v]->lazy, x.second);
			for (auto &x : s[v]->r) s[u]->add(x.first + s[v]->lazy, x.second);
		}
		s[u]->balance();
	}
}

vec<ll> tar;
ll res;
void dfb(int u) {
	if (big[u] != -1) {
		for (int e : adj[u]) {
			int v = other(e, u);
			if (v == par[u] || e == big[u]) continue;
			for (auto &x : s[v]->l) s[u]->remove(x.first + s[v]->lazy, x.second);
			for (auto &x : s[v]->r) s[u]->remove(x.first + s[v]->lazy, x.second);
		}
		s[u]->balance();
	}
	for (int e : adj[u]) {
		int v = other(e, u);
		if (v == par[u]) continue;
		int stt = s[v]->outside(tar[u], edg[e][3]);
		s[v]->lazy -= edg[e][2];
		if (stt == 1) edg[e][4] = tar[u] - s[v]->l.begin()->first - s[v]->lazy;
		else if (stt == 2) edg[e][4] = tar[u] - (--s[v]->r.end())->first - s[v]->lazy;
		else edg[e][4] = edg[e][2];
		res += edg[e][3] * abs(edg[e][2] - edg[e][4]);
		s[v]->restore();
		s[v]->balance();
		tar[v] = tar[u] - edg[e][4];
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	#ifdef LOCAL
		freopen("in1.txt", "r", stdin);
		freopen("in2.txt", "w", stdout);
	#endif
	int tt;
	cin >> tt;
	while (tt--) {
		int n;
		cin >> n;
		if (n == 1) {
			cout << 0 << '\n';
			continue;
		}
		adj = vec<vec<ll>>(n);
		edg = vec<vec<ll>>(n-1, vec<ll>(5));
		for (int i=0; i<n-1; i++) {
			for (int j=0; j<4; j++) cin >> edg[i][j];
			adj[--edg[i][0]].push_back(i);
			adj[--edg[i][1]].push_back(i);
		}
		
		sz = vec<int>(n, 1);
		big = vec<int>(n, -1);
		par = vec<int>(n, -1);
		ord.clear();
		s = vec<S*>(n);
		res = 0;
		dfs();
		for (int u : ord) dfa(u);
		reverse(ord.begin(), ord.end());
		tar = vec<ll>(n);
		tar[0] = s[0]->middle();
		for (int u : ord) dfb(u);
		
		cout << res << '\n';
		for (int i=0; i<n-1; i++) cout << edg[i][4] << '\n';
	}
}