//bs:-program
#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,ssse3,sse4.1,sse4.2,avx,avx2")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
using namespace __gnu_pbds;

#define all(x) begin(x), end(x)
#define sz(x) ((int) (x).size())
#define x first
#define y second
typedef long long ll;
typedef long double ld;

#define ts(x) auto x = chrono::high_resolution_clock::now()
#define delta(a, b) (chrono::duration<double>((b) - (a)).count())

template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

template<typename T>
using normal_queue = priority_queue<T, vector<T>, greater<T>>;

const int MOD = 1e9 + 7, MAX_N = 1 << 18, MAX_CACHED = 2e6;

int cached2[MAX_CACHED];

int n, k;
int a[MAX_N];
int np;

inline int fpow2(ll i) {
	if (i < MAX_CACHED)
		return cached2[i];
	if (i == 0)
		return 1;
	ll res = fpow2(i / 2);
	res *= res;
	if (i & 1)
		res *= 2;
	return int(res % MOD);
}

ll dc_v[20];

inline void prepare_dc(int k) {
	for (int bits = 0; bits < 20; ++bits) {
		dc_v[bits] = fpow2(ll(k - 1) * (np - 1) + ll(bits) * k);
	}
	if (!(k & 1))
		for (int i = 0; i < 20; ++i)
			dc_v[i] = -dc_v[i];
}

int getdelta(int k, int i) {
	ll res = 0;
	for (int bits = 20; bits--; )
		if (i >> bits & 1)
			res += fpow2(ll(k - 1) * (np - 1) + ll(bits) * k);
	return int(res % MOD);
}

int getsdelta(int k, int i) {
	int res = getdelta(k, i);
	if (k & 1 || !res)
		return res;
	return -res + MOD;
}

int getgenerator(int k) {
	if (k == 1) {
		return 0;
	}
	ll res = getgenerator(k / 2);
	ll res2 = 0;
	ll currdelta = 0;
	prepare_dc(k / 2);
	for (int i = 0; i < n; ++i) {
		ll curr = (res + currdelta) % MOD;
		res2 += curr * curr % MOD;
		int it = 0;
		while (i >> it & 1)
			currdelta -= dc_v[it], ++it;
		currdelta += dc_v[it];
	}
	res = res2 % MOD;
	if (k & 1) {
		prepare_dc(k - 1);
		currdelta = 0;
		res2 = 0;
		for (int i = 0; i < n; ++i) {
			res2 += (res + currdelta) % MOD * i % MOD;
			int it = 0;
			while (i >> it & 1)
				currdelta -= dc_v[it], ++it;
			currdelta += dc_v[it];
		}
	}
	return int(res2 % MOD);
}

ll states[2][20];

signed main() {
	// freopen("input2.txt", "r", stdin);
	// freopen("output.txt", "w", stdout);
	ts(startTS);
	ios::sync_with_stdio(0);
	cin.tie(0);
	cached2[0] = 1;
	for (int i = 1; i < MAX_CACHED; ++i) {
		cached2[i] = cached2[i - 1] * 2;
		if (cached2[i] >= MOD)
			cached2[i] -= MOD;
	}
	int tests;
	cin >> tests;
	while (tests--) {
		cin >> n >> k;
		for (int i = 0; i < n; ++i)
			cin >> a[i];
		if (k == 0) {
			for (int i = 0; i < n; ++i)
				cout << a[i] << " ";
			cout << "\n";
			continue;
		}

		np = __builtin_ctzll(n);
		ll gcnt = ll(getgenerator(k)) * (accumulate(a, a + n, 0ll) % MOD) % MOD;
		// cout << gcnt << "\n";
		// cout << gcnt << "\n";
		fill(states[0], states[2], 0);
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < 20; ++j) {
				states[1 - (i >> j & 1)][j] += a[i];
			}
		}
		// cout << states[0][0] << "\n";
		for (int i = 0; i < 2; ++i)
			for (int j = 0; j < 20; ++j)
				states[i][j] %= MOD;
		for (int i = 0; i < n; ++i) {
			ll res = 0;
			for (int j = 0; j < 20; ++j)
				res += fpow2(ll(k - 1) * (np - 1) + ll(j) * k) * states[0][j];
			// cout << i << " " << res << " " << gcnt << "\n";
			res %= MOD;
			if (!(k & 1))
				res = -res;
			// cout << gcnt << " " << res << "\n";
			cout << ((gcnt + res) % MOD + MOD) % MOD << " ";
			for (int j = 0; j < 20; ++j)
				if (((i ^ (i + 1)) >> j & 1))
					swap(states[0][j], states[1][j]);
		}
		cout << "\n";
	}
	ts(finishTS);
	// cerr << delta(startTS, finishTS) << "\n";
	return 0;
}