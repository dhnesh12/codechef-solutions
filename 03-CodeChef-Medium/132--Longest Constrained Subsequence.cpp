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

const int N = 1e5 + 101;
const int MEM = 1e7;

int t[MEM], L[MEM], R[MEM], id = 1;

void sett(int x, int z, int v = 0, int l = 0, int r = 1e9) {
	if (l == r) {
		t[v] = z;
		return;
	}
	int m = (l + r) / 2;
	if (x <= m) {
		if (!L[v]) L[v] = id++;
		sett(x, z, L[v], l, m);
	}
	else {
		if (!R[v]) R[v] = id++;
		sett(x, z, R[v], m + 1, r);
	}
	if (L[v]) t[v] = max(t[v], t[L[v]]);
	if (R[v]) t[v] = max(t[v], t[R[v]]);
}

int query(int x, int y, int v = 0, int l = 0, int r = 1e9) {
	if (x <= l && r <= y) 
		return t[v];
	int m = (l + r) / 2;
	int res = 0;
	if (x <= m && L[v]) res = max(res, query(x, y, L[v], l, m));
	if (m < y && R[v]) res = max(res, query(x, y, R[v], m + 1, r));
	return res;
}

int n, a, b;

int main() {
	scanf ("%d", &n);
	int res = 0;
	rep(i, 1, n) {
		scanf ("%d%d", &a, &b);
		a ^= res;
		b ^= res;
		int ja = 1 + query(max(0, a - b), min((int)1e9, a + b));
		sett(a, ja);
		res = max(res, ja);
		printf ("%d\n", res);
	}
		
		
	return 0;
}	
