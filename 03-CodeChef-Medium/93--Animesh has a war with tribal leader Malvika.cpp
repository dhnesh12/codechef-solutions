#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int Maxn = 100005;
const int mod = 1000000007;

int fac[Maxn];
int t;
int n;
map <int, int> M;
map <int, int> O;

int main()
{
	fac[0] = 1;
	for (int i = 1; i < Maxn; i++)
		fac[i] = ll(i) * fac[i - 1] % mod;
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		M.clear(); O.clear();
		for (int i = 0; i < n; i++) {
			int a; scanf("%d", &a);
			M[a]++;
		}
		for (map <int, int>::iterator it = M.begin(); it != M.end(); it++)
			for (int j = 0; j < it->second; j++)
				O[2 * j - it->second + 1]++;
		int res = 1;
		for (map <int, int>::iterator it = O.begin(); it != O.end(); it++)
			res = ll(res) * fac[it->second] % mod;
		printf("%d\n", res);
	}
	return 0;
}