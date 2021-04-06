#include<bits/stdc++.h>
using namespace std;

const int N = 3e5 + 9, mod = 1e9 + 7;

template <int32_t MOD>
struct modint {
    int32_t value;
    modint() = default;
    modint(int32_t value_) : value(value_) {}
    inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
    inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
    inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
    inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
    inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
    modint<MOD> pow(uint64_t k) const {
        modint<MOD> x = *this, y = 1;
        for (; k; k >>= 1) {
            if (k & 1) y *= x;
            x *= x;
        }
        return y;
    }
    modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
    inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
    inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
    inline bool operator == (modint<MOD> other) const { return value == other.value; }
    inline bool operator != (modint<MOD> other) const { return value != other.value; }
    inline bool operator < (modint<MOD> other) const { return value < other.value; }
    inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using mint = modint<mod>;

mint f[N];
mint kth(mint a, mint b, int k) {
	if (k == 1) return a;
	if (k == 2) return b;
	return a * f[k - 2] + b * f[k - 1];
}
struct BIT {
	vector<mint> ta, tb;
	int n;
	void init(int sz) {
		n = sz + 5;
		ta = vector<mint>(n, 0);
		tb = vector<mint>(n, 0);
	}
	void upd(int i, mint a, mint b) {
		while (i < n) {
			ta[i] += a; tb[i] += b;
			i += i & -i;
		}
	}
	void upd(int l, int r, mint a, mint b) {
		if (l > r) return;
		l++; r++;
		upd(l, a, b);
		upd(r + 1, -a, -b);
	}
	mint query(int i) {
		mint sa = 0, sb = 0; int k = i + 1;
		i++;
		while (i) {
			sa += ta[i]; sb += tb[i];
			i -= i & -i;
		}
		return kth(sa, sb, k);
	}
}t[N], pt[N];
vector<int> g[N];
int sz[N];
int tot, done[N], cenpar[N];
void calc_sz(int u, int p) {
    tot ++; sz[u] = 1;
    for (auto v: g[u]) {
        if(v == p || done[v]) continue;
        calc_sz(v, u);
        sz[u] += sz[v];
    }
}
int find_cen(int u, int p) {
    for (auto v: g[u]) {
        if(v == p || done[v]) continue;
        else if(sz[v] > tot / 2) return find_cen(v, u);
    }
    return u;
}
int h, dep[20][N];
void dfs(int u, int p, int l, int d) {
	h = max(h, d);
	dep[l][u] = d;
	for (auto v: g[u]) {
		if (v == p || done[v]) continue;
		dfs(v, u, l, d + 1);
	}
}
int level[N];
int decompose(int u, int p  = 0) {
    tot = 0;
    calc_sz(u, p);
    int cen = find_cen(u, p);
    cenpar[cen] = p;
    done[cen] = 1; level[cen] = level[p] + 1;
    h = 0;
    dfs(cen, p, level[cen], 0);
    int s = h;
    t[cen].init(s + 1);
    for (auto v: g[cen]) {
	    if(v == p || done[v]) continue;
        int c = decompose(v, cen);
        pt[c].init(s + 1);
    }
    return cen;
}
void upd(int v, int k, int a, int b) {
	int child = 0, u = v;
	while (u) {
		int d = dep[level[u]][v];
		mint na = kth(a, b, d + 1), nb = kth(a, b, d + 2);
		t[u].upd(0, k - d, na, nb);
		if(child) pt[child].upd(0, k - d, na, nb);
		child = u;
		u = cenpar[u];
	}
}
mint query(int v) {
	int u = v, child = 0;
	mint ans = 0;
	while (u) {
		ans += t[u].query(dep[level[u]][v]);
		if(child) ans -= pt[child].query(dep[level[u]][v]);
		child = u;
		u = cenpar[u];
	}
	return ans;
}
int32_t main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    f[1] = 1; f[2] = 1 ;
    for (int i = 3; i < N; i++) f[i] = f[i - 1] + f[i - 2];
    int tc; cin >> tc;
    while (tc--) {
    	int n, q; cin >> n >> q;
    	for (int i = 1; i < n; i++) {
    	    int u, v; cin >> u >> v;
    	    g[u].push_back(v);
    	    g[v].push_back(u);
    	}
    	decompose(1);
    	while (q--) {
    		int ty, u; cin >> ty >> u;
    		if (ty == 1) {
    			int k, a, b; cin >> k >> a >> b;
    			upd(u, k, a, b);
    		}
    		else {
    			cout << query(u) << '\n';
    		}
    	}
    	for (int i = 1; i <= n; i++) g[i].clear(), done[i] = 0;
    }
    return 0;
}