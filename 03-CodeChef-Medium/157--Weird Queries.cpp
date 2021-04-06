#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair <int, int> ii;

const int mod = 1000000007;
const int MaxA = 100005;
const int Maxm = 500005;

int fac[MaxA];
int m, q;
int A[Maxm];
vector <ii> my[MaxA];

int toPower(int a, int p)
{
	int res = 1;
	while (p) {
		if (p & 1) res = ll(res) * a % mod;
		p >>= 1; a = ll(a) * a % mod;
	}
	return res;
}

int Inv(int a) { return toPower(a, mod - 2); }

int Get(int ind, int a, int b)
{
	int res = my[ind][b].second;
	if (a >= 0) res = ll(res) * Inv(my[ind][a].second) % mod;
	return res;
}

int main()
{
	fac[0] = 1;
	for (int i = 1; i < MaxA; i++)
		fac[i] = ll(i) * fac[i - 1] % mod;
	scanf("%d %d", &m, &q);
	for (int i = 0; i < m; i++) {
		scanf("%d", &A[i]);
		for (int j = 0; j <= A[i]; j++)
			my[j].push_back(ii(i, fac[A[i] - j]));
	}
	for (int i = 0; i < MaxA; i++)
		for (int j = 1; j < my[i].size(); j++)
			my[i][j].second = ll(my[i][j].second) * my[i][j - 1].second % mod;
	while (q--) {
		int l, r, n, k; scanf("%d %d %d %d", &l, &r, &n, &k);
		if (n == 0) { printf("1\n"); continue; }
		ll fir = ll(k - 1) * (n - 1);
		ll sec = ll(k - 1) * (n - 1) + ll(n);
		if (sec >= MaxA) { printf("0\n"); continue; }
		int lef2 = lower_bound(my[sec].begin(), my[sec].end(), ii(l, 0)) - my[sec].begin() - 1;
		int rig2 = lower_bound(my[sec].begin(), my[sec].end(), ii(r + 1, 0)) - my[sec].begin() - 1;
		if (rig2 - lef2 != r - l + 1) { printf("0\n"); continue; }
		int res = Inv(Get(sec, lef2, rig2));
		int lef1 = lower_bound(my[fir].begin(), my[fir].end(), ii(l, 0)) - my[fir].begin() - 1;
		int rig1 = lower_bound(my[fir].begin(), my[fir].end(), ii(r + 1, 0)) - my[fir].begin() - 1;
		res = ll(res) * Get(fir, lef1, rig1) % mod;
		res = ll(res) * Inv(fac[n]) % mod;
		printf("%d\n", res);
	}
	return 0;
}