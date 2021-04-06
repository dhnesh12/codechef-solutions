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
vector<int> pfac; // pfac[i] = largest prime factor of i (pfac[i <= 1] = 0)
void genPrimes(int n) {
	pfac = vector<int>(n + 1);
	for (int i = 2; i <= n; ++i) pfac[i] = i;
	for (int i = 2; i <= n; ++i)
		if (pfac[i] == i)
			for (int j = i + i; j <= n; j += i)
				pfac[j] = i;
}
vector<int> listPrimes(int n) {
	genPrimes(n);
	vector<int> primes;
	for (int i = 2; i <= n; ++i)
		if (pfac[i] == i) primes.push_back(i);
	return primes;
}
/* 0 <= n <= 2e9. */
struct DynamicBitset {
	using ull = unsigned long long;
	int n;
	vector<ull> V;
	DynamicBitset(int _n) : n(_n), V((_n + 63) >> 6) {}
	void resize(int _n) { n = _n; V.resize((n + 63) >> 6); }
	void reset() { fill(V.begin(), V.end(), 0); }
	void reset(int p) {
		assert(p < n);
		V[p >> 6] &= ~(1ULL << (p & 63));
	}
	void set() { for (ull& x : V) x = ~0ULL; }
	void set(int p) {
		assert(p < n);
		V[p >> 6] |= 1ULL << (p & 63);
	}
	void flip() { for (ull& x : V) x ^= ~0ULL; }
	void flip(int p) {
		assert(p < n);
		V[p >> 6] ^= 1ULL << (p & 63);
	}
	bool test(int p) const {
		assert(p < n);
		return V[p >> 6] & (1ULL << (p & 63));
	}
	int count() const {
		int ret = 0;
		for (ull x : V) ret += __builtin_popcountll(x);
		return ret;
	}
	DynamicBitset& operator|=(const DynamicBitset& b) {
		assert(b.n == n);
		for (int i = 0; i < V.size(); ++i) V[i] |= b.V[i];
		return *this;
	}
	DynamicBitset& operator&=(const DynamicBitset& b) {
		assert(b.n == n);
		for (int i = 0; i < V.size(); ++i) V[i] &= b.V[i];
		return *this;
	}
	DynamicBitset& operator^=(const DynamicBitset& b) {
		assert(b.n == n);
		for (int i = 0; i < V.size(); ++i) V[i] ^= b.V[i];
		return *this;
	}
	DynamicBitset operator~() const {
		DynamicBitset ret = *this;
		for (ull& x : ret.V) x = ~x;
		return ret;
	}
	friend DynamicBitset operator|(DynamicBitset a, const DynamicBitset& b) { return a |= b; }
	friend DynamicBitset operator&(DynamicBitset a, const DynamicBitset& b) { return a &= b; }
	friend DynamicBitset operator^(DynamicBitset a, const DynamicBitset& b) { return a ^= b; }
	friend string to_string(const DynamicBitset& b) {
		string ret;
		for (int i = 0; i < b.n; ++i) ret += b.test(i) ? '1' : '0';
		return ret;
	}
};
int main() {
	auto ps = listPrimes(7500);
	db(ps.size());
	int T;
	scanf("%d", &T);
	while (T--) {
		int n, c;
		scanf("%d%d", &n, &c);
		int m = 0;
		while (ps[m] * ps[m] <= c) ++m;
		assert(m <= 23);
		vector<int> A(n), numSmallPerBig(c + 1), req(1 << m);
		vector<vector<int>> bigs(m + 1);
		vector<vector<pair<int, int>>> G(m + 1);
		vector<bool> noBigs(1 << m);
		for (int i = (int)ps.size() - 1; i >= m; --i) {
			if (ps[i] > c) continue;
			if (i + 1 < ps.size() && ps[i + 1] <= c) numSmallPerBig[ps[i]] = numSmallPerBig[ps[i + 1]];
			while (ps[numSmallPerBig[ps[i]]] * ps[i] <= c) ++numSmallPerBig[ps[i]];
			bigs[numSmallPerBig[ps[i]]].push_back(ps[i]);
		}
		for (int i = 0; i < n; ++i) {
			scanf("%d", &A[i]);
			int x = A[i];
			int bits = 0;
			for (int j = 0; j < m; ++j) {
				while (x % ps[j] == 0) {
					x /= ps[j];
					bits |= 1 << j;
				}
			}
			int bad = ~bits & ((1 << m) - 1);
			if (x == 1) noBigs[bad] = true;
			else {
				int mxp = numSmallPerBig[x];
				G[mxp].push_back({x, bits});
			}
		}
		for (int j = 0; j < m; ++j)
			for (int k = 0; k < (1 << m); ++k)
				if (!(k & (1 << j))) noBigs[k] = noBigs[k] || noBigs[k ^ (1 << j)];
//		ll val = 0;
		for (int smalls = 1; smalls <= m; ++smalls) {
			reverse(bigs[smalls].begin(), bigs[smalls].end());
//			db(smalls, bigs[smalls].size(), G[smalls].size());
			int mask = (1 << smalls) - 1;
//			val += (ll)smalls * (1LL << smalls) * (smalls < 3 ? 3 : 1);
//			val += (1LL << m) * (smalls < 3 ? 3 : 1);
			if (smalls < 3) {
//				vector<DynamicBitset> sos(1 << smalls, bigs[smalls].size());
				vector<bitset<155>> sos(1 << smalls);
				for (auto& g : G[smalls]) {
					int big = g.first;
					int bits = g.second;
					int bad = ~bits & mask;
					int bigInd = lower_bound(bigs[smalls].begin(), bigs[smalls].end(), big) - bigs[smalls].begin();
					sos[bad].set(bigInd);
				}
				for (int j = 0; j < smalls; ++j)
					for (int k = 0; k < (1 << smalls); ++k)
						if (!(k & (1 << j))) sos[k] |= sos[k ^ (1 << j)];
				for (int k = 0; k < (1 << m); ++k) {
					int need = sos[k & mask].count();
					req[k] += need;
				}
			} else {
				vector<ll> sos(1 << smalls);
				for (auto& g : G[smalls]) {
					int big = g.first;
					int bits = g.second;
					int bad = ~bits & mask;
					int bigInd = lower_bound(bigs[smalls].begin(), bigs[smalls].end(), big) - bigs[smalls].begin();
					sos[bad] |= 1LL << bigInd;
				}
				for (int j = 0; j < smalls; ++j)
					for (int k = 0; k < (1 << smalls); ++k)
						if (!(k & (1 << j))) sos[k] |= sos[k ^ (1 << j)];
				for (int k = 0; k < (1 << m); ++k) {
					int need = __builtin_popcountll(sos[k & mask]);
					req[k] += need;
				}
			}
		}
//		db(val);
		int best = INT_MAX, take = -1;
		for (int i = 0; i < (1 << m); ++i) {
			if (noBigs[i]) continue;
			int tot = req[i] + __builtin_popcount(i);
			if (tot < best) {
				best = tot;
				take = i;
			}
		}
		set<int> ans;
		for (int i = 0; i < m; ++i)
			if (take & (1 << i)) ans.insert(ps[i]);
		for (int i = 0; i < n; ++i) {
			int x = A[i];
			int bits = 0;
			for (int j = 0; j < m; ++j) {
				while (x % ps[j] == 0) {
					x /= ps[j];
					bits |= 1 << j;
				}
			}
			if (!(bits & take)) {
				assert(x > 1);
				ans.insert(x);
			}
		}
		printf("%d\n", (int)ans.size());
		for (int a : ans) printf("%d ", a);
		printf("\n");
	}
}
