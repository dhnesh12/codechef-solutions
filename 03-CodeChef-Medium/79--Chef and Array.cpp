#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ss(x) (int)x.size()
#define cat(x) cerr << #x << " = " << x << endl
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, l, r) for (int i = r; l <= i; --i)
#define all(x) x.begin(), x.end()

using ll = long long;
using namespace std;

const int N = 2e5 + 505;
const int MOD = 1e9 + 7;

struct FenTree {
	ll F[N];
	void init() {
		memset(F, 0, sizeof F);
	}
	void add(int x, ll del) {
		for (x++; x < N; x += x & -x)
			F[x] = (F[x] + del) % MOD;
	}
	ll query(int x) {
		ll res = 0;
		for (x++; 0 < x; x -= x & -x)
			res = (res + F[x]) % MOD;
		return res;
	}
	ll qw(int l, int r) {
		return query(r) - query(l - 1);
	}
} A, B, C;

int n, a[N], q;
ll k, b[N], vals[N];

int lower(ll x) {
	return lower_bound(vals + 1, vals + q + 1, x) - vals;
}

int upper(ll x) {
	return upper_bound(vals + 1, vals + q + 1, x) - vals;
}

ll C2(ll x) {
	return x * (x - 1) / 2 % MOD;
}

void solve() {
	q = 0;
	vals[++q] = 0;
	vals[++q] = -1e18;
	scanf ("%d%lld", &n, &k);
	rep(i, 1, n) {
		scanf ("%d", a + i);
		b[i] = b[i - 1] + a[i];
		vals[++q] = b[i];
	}
	sort(vals + 1, vals + q + 1);
	q = unique(vals + 1, vals + q + 1) - vals - 1;
	
	ll res = 0;
	
	A.init();
	A.add(lower(0), 1);
	rep(i, 1, n) {
		int p = upper(b[i] - k);
		res += A.qw(p, N - 1) * (n - i + 1) % MOD;
		res %= MOD;
		A.add(lower(b[i]), i + 1);
	}
	
	A.init();
	B.init();
	A.add(lower(0), C2(1));
	B.add(lower(0), 1);
	
	rep(i, 1, n) {
		int p = upper(b[i] - k);
		(res += A.qw(p, N - 1)) % MOD;
		(res += C2(n - i + 1) * B.qw(p, N - 1) % MOD) % MOD;
		A.add(lower(b[i]), C2(i + 1));
		B.add(lower(b[i]), 1);
	}
	
	A.init();
	B.init();
	C.init();
	
	rep(i, 1, n) {
		int p = lower(k - (b[n] - b[i - 1])) - 1;
		ll tmp = 0;
		tmp += (ll) i * i % MOD * A.qw(0, p) % MOD;
		tmp += (ll) i * B.qw(0, p) % MOD;
		tmp += C.qw(0, p);
		
		tmp %= MOD;
		while (tmp < 0) tmp += MOD;
		
		A.add(lower(b[i]), 1);
		B.add(lower(b[i]), -(2 * (i - 1) + 1));
		C.add(lower(b[i]), (ll)(i - 1) * i);
	
		res += tmp * ((MOD + 1) / 2) % MOD;
		res %= MOD;
	}	
		
	if (res < 0) res += MOD;
	printf ("%lld\n", res);
}

int main() {
	int T;
	scanf ("%d", &T);
	while (T--)
		solve();
	
	return 0;
}
