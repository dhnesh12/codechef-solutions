#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define pb push_back
#define mp make_pair
#define ss(x) (int) x.size()
#define fi first
#define se second
#define cat(x) cerr << #x << " = " << x << endl
#define rep(i, j, n) for (int i = j; i <= n; ++i)
#define per(i, j, n) for (int i = n; j <= i; --i)
#define all(x) x.begin(), x.end()
#define ull unsigned long long
 
using namespace std;		

int n;
ll a[15];
ll b[1 << 15];

ll dp[20][20];
ll dp2[20];

#define pc(x) __builtin_popcountll(x)

void solve() {
	scanf ("%d", &n);
	rep(i, 0, n - 1)
		scanf ("%lld", a + i);
	
	rep(i, 0, (1 << n) - 1)
		b[i] = (1LL << 60) - 1;
	
	ll answer = 0;	
		
	rep(mask, 1, (1 << n) - 1) {
		ll bit = __builtin_ctzll(mask);
		b[mask] = b[mask ^ (1 << bit)] & a[bit];
		ll A = (1LL << pc(b[mask]));
		if (pc(mask) % 2 == 0)
			answer -= A * dp2[pc(mask)];
		else 
			answer += A * dp2[pc(mask)];
	}
	printf ("%lld\n", answer);
	
}

int main() {	
	rep(i, 0, 19) {
		dp[i][0] = dp[i][i] = 1;
		rep(j, 1, i)
			dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
	}
	
	rep(i, 1, 19)
		for (int j = 1; j <= i; j += 2)
			dp2[i] += dp[i][j];
	int T;
	scanf ("%d", &T);
	while (T--) solve();
	return 0;
}	
