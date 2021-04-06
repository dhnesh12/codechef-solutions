#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int mod = 1000000007;

int t;
ll n, m;

int toPower(int a, ll p)
{
	int res = 1;
	while (p) {
		if (p & 1ll) res = ll(res) * a % mod;
		p >>= 1ll; a = ll(a) * a % mod;
	}
	return res;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%lld %lld", &n, &m);
		int res;
		if (n % 2 == 0 && m % 2 == 0)
			res = toPower(toPower(2, n), m); 
		else if (n % 2 == 1 && m % 2 == 1)
			res = 2ll * toPower(toPower(2, n - 1), m - 1) % mod;
		else {
			if (n % 2) swap(n, m);
			res = 2ll * toPower(toPower(2, m - 1), n) % mod;
		}
		printf("%d\n", res);
	}
	return 0;
}