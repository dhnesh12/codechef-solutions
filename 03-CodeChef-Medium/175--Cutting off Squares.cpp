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
typedef long double ld;

int t;
int a, b;
ll res;

ll Get(int a, int b)
{
	if (a == 0) return 0;
	return b / a - 1 + Get(b % a, a);
}

int getNim(int a, int b)
{
	if (a == 0) return 0;
	int nim = getNim(b % a, a);
	if (b / a - 1 >= nim) return b / a;
	return b / a - 1;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &a, &b);
		res = 0;
		ll pw = Get(a, b);
		res += 1 + ll(pw * (log(2.0l) / log(10.0l)) + 1e-11l);
		int nim = getNim(a, b);
		if (nim > 0) res += 5;
		else res += 6;
		if (pw == 0) res++;
		else res += 1 + ll((pw - 1) * (log(2.0l) / log(10.0l)) + 1e-11l);
		printf("%lld\n", res);
	}
	return 0;
}