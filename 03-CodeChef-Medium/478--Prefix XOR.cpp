# include <bits/stdc++.h>

# define R register
# define ll long long
# define meow(cat...) fprllf(stderr, cat)

const ll MaxN = 5e5 + 10;
const ll Max = MaxN << 4;
 
struct node
{
	ll lc, rc;
	ll cnt, sum;
};

ll n, q, cnt, ans, a[MaxN], f[MaxN], rt[MaxN], c[40][2];

struct SegmentTree
{
	node t[Max];
	void insert(ll &rt, ll pre, ll l, ll r, ll val)
	{
		rt = ++cnt, t[rt].cnt = t[pre].cnt + 1;
		t[rt].lc = t[pre].lc, t[rt].rc = t[pre].rc;
		t[rt].sum = t[pre].sum + val;
		if(l == r) return (void) "xzakioi";
		ll mid = (l + r) >> 1;
		if(val <= mid) insert(t[rt].lc, t[pre].lc, l, mid, val);
		else insert(t[rt].rc, t[pre].rc, mid + 1, r, val);
	}
	ll query_cnt(ll u, ll v, ll l, ll r, ll ql, ll qr)
	{
		if(ql <= l && r <= qr) 
			return t[v].cnt - t[u].cnt;
		ll mid = (l + r) >> 1, ret = 0;
		if(ql <= mid) 
			ret += query_cnt(t[u].lc, t[v].lc, l, mid, ql, qr);
		if(qr > mid) 
			ret += query_cnt(t[u].rc, t[v].rc, mid + 1, r, ql, qr);
		return ret;
	}
	ll query_sum(ll u, ll v, ll l, ll r, ll ql, ll qr)
	{
		if(ql <= l && r <= qr) 
			return t[v].sum - t[u].sum;
		ll mid = (l + r) >> 1, ret = 0;
		if(ql <= mid) 
			ret += query_sum(t[u].lc, t[v].lc, l, mid, ql, qr);
		if(qr > mid) 
			ret += query_sum(t[u].rc, t[v].rc, mid + 1, r, ql, qr);
		return ret;
	}
} T; 

ll read()
{
 	ll x = 0;
	char ch = getchar();
	while(ch > '9' || ch < '0') ch = getchar();
	while('0' <= ch && ch <= '9')
		x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
	return x;
}

signed main()
{
	n = read();
	memset(c, 0x3f, sizeof(c));
	for(ll i = 1; i <= n; i++)
		a[i] = read(), a[i] ^= a[i - 1];
	for(ll i = n; i; i--)
	{
		f[i] = n;
		for(ll j = 30; ~j; j--)
			f[i] = std::min(f[i], c[j][!!(a[i - 1] & (1 << j))] - 1);
		for(ll j = 30; ~j; j--)
			if((a[i] & (1 << j)) ^ (a[i - 1] & (1 << j)))
			{	c[j][!!(a[i] & (1 << j))] = std::min(c[j][!!(a[i] & (1 << j))], i); break; }
	}
	for(ll i = 1; i <= n; i++)
		T.insert(rt[i], rt[i - 1], 1, n, f[i]);
	q = read(), ans = 0;
	while(q--)
	{
		ll l = (read() + ans) % n + 1; 
		ll r = (read() + ans) % n + 1;
		if(l > r) std::swap(l, r); 
		ans = T.query_sum(rt[l - 1], rt[r], 1, n, 1, r) +  
				T.query_cnt(rt[l - 1], rt[r], 1, n, r + 1, n) * r
				  - (l + r) * (r - l + 1) / 2 + (r - l + 1);
		printf("%lld\n", ans); 
	} 
	return 0;
} 
