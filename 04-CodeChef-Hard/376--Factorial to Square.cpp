#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define ss(x) (int) x.size()
#define cat(x) cerr << #x << " = " << x << endl
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define per(i, l, r) for (int i = r; l <= i; --i)

using ll = long long;
using namespace std;
 
const int N = 3005; 
const int M = 1 << 19;
 
int n, MOD, small[N], big[N], s, b; 
bool sieve[N];
int dp[M], ndp[M];

int msb(int mask) {
	assert(mask);
	return 31 - __builtin_clz(mask);
}

bool good(int mask, int a) {
	ll val = a;
	rep(i, 0, s - 1) {
		if (mask >> i & 1)
			val *= small[i + 1];
		if (val > n) return false;
	}
	return val <= n;
}
 
void solve() {
	s = b = 0;
	scanf ("%d%d", &n, &MOD);
	rep(i, 1, n) sieve[i] = false;
	rep(i, 2, n) {
		if (!sieve[i]) {
			int r = 0;
			int j = i;
			while (j <= n) {
				r += n / j;
				j *= i;
			}
			if (r & 1) {
				if (i * i <= n)
					small[++s] = i;
				else
					big[++b] = i;
			}
			
			rep(j, 1, n / i)
				sieve[i * j] = true;
		}
	}
	memset(dp, 0, sizeof dp);
	int m = (1 << s);
	rep(mask, 0, m - 1) {
		if (!mask) {
			dp[mask] = 2 % MOD;
			continue;
		}
		for (int nmask = mask; nmask; nmask = ((nmask - 1) & mask)) 
			if (msb(nmask) == msb(mask) && good(nmask, 1))
				dp[mask] = (dp[mask] + dp[mask ^ nmask]) % MOD;
	}
	rep(i, 0, b - 1) {
		memset(ndp, 0, sizeof ndp);
		rep(mask, 0, m - 1) {
			for (int nmask = mask; 1; nmask = ((nmask - 1) & mask)) {
				if (good(nmask, big[i + 1])) {
					ndp[mask] = (ndp[mask] + dp[mask ^ nmask]) % MOD;
				}
				if (!nmask) break;
			}
		}
		rep(mask, 0, m - 1) dp[mask] = ndp[mask];
	}
	printf ("%d\n", dp[m - 1]);
}
 
int main() {
	srand(time(0));
	int T;
	scanf ("%d", &T);
	while (T--) 
		solve();
	
	return 0;
}
