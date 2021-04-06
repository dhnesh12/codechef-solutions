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

typedef pair <int, int> ii;
typedef long long ll;

const int Maxn = 100005;

int myvers[Maxn];
vector <ii> val;
vector <int> L, R;
int N, M, A, B, C, D;
int a[Maxn];

ii Union(const ii &a, const ii &b)
{
	if (a.first > b.first)
		return a.second > b.first? ii(a.first, a.second): ii(a.first, b.first);
	return a.first > b.second? ii(b.first, a.first): ii(b.first, b.second);
}

int getLst() { return int(val.size()) - 1; }

int addNode() { 
	val.push_back(ii(0, 0));
	L.push_back(-1); R.push_back(-1);
}

void Clear(int v, int l, int r)
{
	if (l == r) val[v] = ii(a[l], 0);
	else {
		int m = l + r >> 1;
		addNode(); L[v] = getLst(); Clear(L[v], l, m);
		addNode(); R[v] = getLst(); Clear(R[v], m + 1, r);
		val[v] = Union(val[L[v]], val[R[v]]);
	}
}

ii Get(int v, int l, int r, int a, int b)
{
	if (l == a && r == b) return val[v];
	else {
		int m = l + r >> 1;
		if (b <= m) return Get(L[v], l, m, a, b);
		if (m + 1 <= a) return Get(R[v], m + 1, r, a, b);
		return Union(Get(L[v], l, m, a, m), Get(R[v], m + 1, r, m + 1, b));
	}
}

void Update(int v, int v2, int l, int r, int x, int va)
{
	if (l == r) val[v] = ii(va, 0);
	else {
		int m = l + r >> 1;
		L[v] = L[v2]; R[v] = R[v2];
		if (x <= m) { addNode(); L[v] = getLst(); Update(L[v], L[v2], l, m, x, va); }
		else { addNode(); R[v] = getLst(); Update(R[v], R[v2], m + 1, r, x, va); }
		val[v] = Union(val[L[v]], val[R[v]]);
	}
}

int main()
{
	scanf("%d %d %d %d %d %d", &N, &M, &A, &B, &C, &D);
	for (int i = 0; i < N; i++)
		scanf("%d", &a[i]);
	addNode(); myvers[0] = getLst(); Clear(myvers[0], 0, N - 1);
	int q; scanf("%d", &q);
	int r1 = 0, r2;
	for (int i = 1; i <= q; i++) {
		int qi, qj; scanf("%d %d", &qi, &qj);
		int t = (ll(A) * r1 + D) % i;
		ii got = Get(myvers[t], 0, N - 1, qi, qj);
		r1 = got.first, r2 = got.second;
		printf("%d %d\n", r1, r2);
		int ind = (ll(B) * r1 + D) % N, v = (ll(C) * r2 + D) % M;
		addNode(); myvers[i] = getLst(); Update(myvers[i], myvers[i - 1], 0, N - 1, ind, v);
	}
	return 0;
}