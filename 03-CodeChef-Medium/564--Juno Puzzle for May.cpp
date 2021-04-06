#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <algorithm>
using namespace std;

typedef long long ll;

const int mod = 1000000007;
const int Maxn = 105;

int t;
ll v;
int n;
ll p[Maxn], q[Maxn];
ll a0, b0, c0, m0;
ll a1, b1, c1, m1;

ll toPower(ll a, ll p)
{
	a %= mod;
	ll res = 1;
	while (p) {
		if (p & 1) res = res * a % mod;
		p >>= 1; a = a * a % mod;
	}
	return res;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%lld %d", &v, &n);
		scanf("%lld %lld %lld %lld %lld %lld", &p[0], &p[1], &a0, &b0, &c0, &m0);
		scanf("%lld %lld %lld %lld %lld %lld", &q[0], &q[1], &a1, &b1, &c1, &m1);
		for (int i = 2; i < n; i++) {
			p[i] = (ll(a0) * a0 % m0 * p[i - 1] + ll(b0) * p[i - 2] + ll(c0)) % m0;
			q[i] = (ll(a1) * a1 % m1 * q[i - 1] + ll(b1) * q[i - 2] + ll(c1)) % m1;
		}
		ll a = v % mod;
		ll pw = 1;
		bool one = false;
		for (int i = 0; i < n; i++) {
			ll L = ll(p[i]) * m1 + ll(q[i]);
			if (L == 0) one = true;
			pw = L % (mod - 1) * pw % (mod - 1);
		}
		if (one) printf("1\n");
		else if (a == 0) printf("0\n");
		else printf("%lld\n", toPower(a, pw));
	}
	return 0;
}