#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

typedef long long ll;

int t;
int L, R, k;
ll n;

ll Get(ll n, ll d)
{
	if (n < d) return 0;
	ll lst = n / d - 1;
	return lst * (lst + 1) / 2 * d + (n / d) * (n % d + 1);
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %lld", &L, &R, &k, &n);
		ll sz = (R - L) / k;
		printf("%lld ", sz + 1);
		int lef = 0, rig = R - L;
		ll all = Get(R - L - ll(k - 1) * sz, sz);
		while (lef <= rig) {
			int mid = lef + rig >> 1;
			ll cur = all - Get(mid - 1 - ll(k - 1) * sz, sz);
			if (cur >= n) lef = mid + 1;
			else rig = mid - 1;
		}
		lef--;
		if (lef < 0) printf("0 0\n");
		else {
			ll a1 = R - lef;
			n -= (all - Get(lef - ll(k - 1) * sz, sz));
			ll a2 = a1 + k - 1 + n;
			printf("%lld %lld\n", a1, a2);
		}
	}
	return 0;
}