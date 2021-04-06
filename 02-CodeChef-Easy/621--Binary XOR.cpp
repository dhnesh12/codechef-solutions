#include "bits/stdc++.h"
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.cpp"
#endif

#define pb               push_back
#define ff               first
#define all(x)           (x).begin(),(x).end()
#define FOR(a)           for(auto& ix :a)
#define rep(i,a,b)       for(int i=a;i<b;i++)
#define int              long long
#define lld              long double
#define vi               vector<int>
#define pii              pair<int,int>
#define ss               second
#define si(x)            (int)x.size()
#define pnr(a)           FOR(a){cout<<ix<<" ";}cout<<'\n';
#define pnrx(a)          FOR(a){cout<<ix.ff<<" "<<ix.ss<<'\n';}

const long long inf = 1e18;
const long long mod = 1e9 + 7;
const long long mxn = 3e5 + 5;

vi fact(mxn , 0);

int cal()
{
	fact[0] = 1;
	fact[1] = 1;
	for (int i = 2 ; i < mxn ; i++)
	{
		fact[i] = fact[i - 1] * i;
		fact[i] %= mod;
	}
	return 0;
}
int power(int a, int b) {
	if (b == 0)
		return 1;
	int ans = power(a, b / 2);
	ans = ans % mod;
	ans = (ans * ans) % mod;
	if (b % 2)
		ans = (ans * a) % mod;
	return ans;
}

int invmod(int num) {
	return power(num, mod - 2);
}
int test_case() {
	int n ; cin >> n;

	string sa , sb;
	cin >> sa >> sb;

	int a(0) , b(0) , c(0) , d(0);
	FOR(sa)
	{
		a += (ix == '1');
		b += (ix == '0');
	}

	FOR(sb)
	{
		c += (ix == '1');
		d += (ix == '0');
	}

	int maxo = min(a , d) + min(c , b);
	int maxz = min(a , c) + min( b , d);


	int ans = 0;
	// deb(maxo , maxz);

	for (int i = (n - maxo ) ; i <= maxz ; i += 2)
	{
		int ax = invmod(fact[i]);
		int bx = invmod(fact[n - i]);
		ax = (ax % mod) * (bx % mod);
		ax = ax % mod;

		ans += fact[n] * ax;
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}
signed main() {
	ios::sync_with_stdio(0); cin.tie(0);
	cout << fixed << setprecision(20);
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
	//freopen("out.txt","w",stdout);
#endif
	cal();
	int tests = 1;
	cin >> tests;
	for (int tt = 1 ; tt <= tests ; tt++) {
		test_case();
	}
	return 0 ;
}
