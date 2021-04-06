#include <cstdio>
#include <iostream>
#define MN 4010000

int h[MN], nxt[2 * MN], to[2 * MN], K = 0;

void ins(int u, int v) {nxt[++K] = h[u]; h[u] = K; to[K] = v;}
 
int lazy[MN]; 

struct val
{
	int Min, cnt;
	val(){}
	val(int a, int b) {Min = a; cnt = b;}
	val operator + (val a)
	{
		if(Min < a.Min) return *this;
		else if(Min == a.Min) return val(Min, cnt + a.cnt);
		else return a;
	}
}t[MN];

void add(int x, int v) {t[x].Min += v; lazy[x] += v;}

void pushdown(int x)
{
	if(lazy[x])
	{
		add(x << 1, lazy[x]);
		add(x << 1 | 1, lazy[x]);
		lazy[x] = 0;
	}
}

void build(int x, int l, int r)
{
	t[x] = val(0, r - l + 1); lazy[x] = 0;
	if(l == r) return;
	int mid = l + r >> 1;
	build(x << 1, l, mid); build(x << 1 | 1, mid + 1, r);
}

void modify(int x, int l, int r, int L, int R, int v)
{
	if(l == L && r == R) {add(x, v); return;}
	pushdown(x); int mid = l + r >> 1;
	if(R <= mid) modify(x << 1, l, mid, L, R, v);
	else if(L > mid) modify(x << 1 | 1, mid + 1, r, L, R, v);
	else modify(x << 1, l, mid, L, mid, v), modify(x << 1 | 1, mid + 1, r, mid + 1, R, v);
	t[x] = t[x << 1] + t[x << 1 | 1];
}

val query(int x, int l, int r, int L, int R)
{
	if(l == L && r == R) return t[x];
	pushdown(x); int mid = l + r >> 1;
	if(R <= mid) return query(x << 1, l, mid, L, R);
	else if(L > mid) return query(x << 1 | 1, mid + 1, r, L, R);
	else return query(x << 1, l, mid, L, mid) + query(x << 1 | 1, mid + 1, r, mid + 1, R);
}

int main()
{
	int T; scanf("%d", &T);
	while(T--)
	{
		int n; scanf("%d", &n);
		long long ans = 0;
		for(int i = 1; i <= n; i++) h[i] = 0; K = 0;
		build(1, 1, n);
		for(int i = 1; i < n; i++)
		{
			int u, v; scanf("%d%d", &u, &v);
			ins(u, v); ins(v, u);
		}
		for(int i = 1; i <= n; i++)
		{
			modify(1, 1, n, 1, i, 1);
			for(int j = h[i]; j; j = nxt[j]) 
				if(to[j] < i) modify(1, 1, n, 1, to[j], -1);
			val v = query(1, 1, n, 1, i);
			if(v.Min == 1) ans += v.cnt;
		}
		printf("%lld\n", ans);
	}
}