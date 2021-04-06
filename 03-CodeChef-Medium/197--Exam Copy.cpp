#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> ii;

const int Maxn = 100005;
const int Maxm = 19;
const int Inf = 1000000000;

int n, m;
int L[Maxn], R[Maxn];
ii best[Maxn][Maxm];
int D;

ii Union(const ii &a, const ii &b)
{
	if (a.first > b.first) return a;
	else if (a.first < b.first) return b;
	else return ii(a.first, a.second + b.second);
}

ii Get(int l, int r)
{
	ii res = ii(0, 0);
	for (int i = Maxm - 1; i >= 0; i--) if (l + (1 << i) <= r + 1) {
		res = Union(res, best[l][i]);
		l += 1 << i;
	}
	return res;
}

int main()
{
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++) {
		int k; scanf("%d", &k);
		best[i][0] = ii(k, 1);
	}
	for (int i = 1; i <= n; i++)
		L[i] = R[i] = i;
	for (int i = 1; i <= m; i++) {
		int l, r; scanf("%d %d", &l, &r);
		R[l] = max(R[l], r);
		L[r] = min(L[r], l);
	}
	int mxR = 0;
	for (int i = 1; i <= n; i++) {
		mxR = max(mxR, R[i]);
		R[i] = mxR;
	}
	int mnL = n;
	for (int i = n; i > 0; i--) {
		mnL = min(mnL, L[i]);
		L[i] = mnL;
	}
	for (int j = 1; j < Maxm; j++)
		for (int i = 1; i + (1 << j) <= n + 1; i++)
			best[i][j] = Union(best[i][j - 1], best[i + (1 << j - 1)][j - 1]);
	scanf("%d", &D);
	for (int i = 1; i <= n; i++) {
		int lef1 = max(1, i - D);
		int rig1 = L[i] - 1;
		ii val = ii(0, 0);
		if (lef1 <= rig1) val = Union(val, Get(lef1, rig1));
		int lef2 = R[i] + 1;
		int rig2 = min(n, i + D);
		if (lef2 <= rig2) val = Union(val, Get(lef2, rig2));
		if (val.first <= best[i][0].first) printf("-1\n");
		else printf("%d %d\n", val.first, val.second);
	}
	return 0;
}