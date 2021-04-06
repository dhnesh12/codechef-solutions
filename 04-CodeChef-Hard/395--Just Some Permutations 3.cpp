#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int mod = 1000000007;
const int Maxm = 1000005;

int fac[Maxm];
int t;
int n, m;

int toPower(int a, int p)
{
	int r = 1;
	while (p) {
		if (p & 1) r = ll(r) * ll(a) % ll(mod);
		p >>= 1; a = ll(a) * ll(a) % ll(mod);
	}
	return r;
}

int main()
{
	fac[0] = 1;
	for (int i = 1; i < Maxm; i++)
		fac[i] = ll(fac[i - 1]) * ll(i) % ll(mod);
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &m);
		int res = fac[m - n + 1];
		int delta = 2 * n - m - 1;
		res = ll(fac[m - n + 1]) * ll(toPower(ll(m - n) * ll(m - n + 1) % ll(mod), delta / 2)) % ll(mod) * ll(delta % 2? m - n: 1) % ll(mod);
		printf("%d\n", res);
	}
	return 0;
}