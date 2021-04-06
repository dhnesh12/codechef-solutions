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
 
using namespace std;		

const int MOD = 1e9 + 7;

void add(int &a, int b) {
	a += b;
	if (a >= MOD) a -= MOD;
}

ll n;

ll sumar(ll first, ll del, ll cnt) {
	if (cnt <= 0) return 0;
	ll end = first + (cnt - 1) * del;
	return (first + end) % MOD * ((MOD + 1) / 2) % MOD * (cnt % MOD) % MOD;
}

ll comb(ll n) {
	return (n % MOD) * ((n - 1) % MOD) % MOD * ((n - 2) % MOD) % MOD * ((MOD + 1) / 2) % MOD * ((MOD + 1) / 3) % MOD;
}

string s;

bool ispal(int l, int r) {
	int n = r - l + 1;
	rep(i, 0, n - 1)
		if (s[l + i] != s[r - i])
			return false;
	return true;
}

void solve() {
	scanf ("%lld", &n);
	vector <ll> groups;
	ll p = 1;
	ll m = n;
	while (m) {
		groups.pb(min(m, p));
		m -= min(m, p);
		if (m)
			groups.pb(min(m, p));
		m -= min(m, p);
		p *= 2;
	}
	
	/*int brut = 0;
	s.clear();
	rep(i, 0, ss(groups) - 1) {
		rep(j, 1, groups[i])
			s.pb((i % 2 == 0 ? 'a' : 'b'));
	}
	rep(i, 0, n - 1)
		rep(l, 0, i)
			rep(r, l, i)
				brut += ispal(l, r);
	cat(brut);*/
		
	int answer = 0;
	ll sum = 0;
	rep(i, 0, ss(groups) - 1) {
		sum += groups[i];
		add(answer, comb(groups[i] + 2));
		
		int x = groups[i] % MOD;
		add(answer, 1LL * x * (x + 1) % MOD * ((MOD + 1) / 2) % MOD * ((n - sum) % MOD) % MOD);
		
		if (i == 0 || i == ss(groups) - 1) continue;
		
		ll k = min(groups[i - 1], groups[i + 1]);
		add(answer, sumar(n - sum, -1, k));
	}
		
	printf ("%d\n", answer);
}

int main() {	
	int T;
	scanf ("%d", &T);
	while (T--) solve();
	
	return 0;
}	
