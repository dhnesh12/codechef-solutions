/** I can do this all day **/

#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;

typedef long long                   ll;
typedef long double                 ld;
typedef pair<int,int>               pii;
typedef pair<ll,ll>                 pll;
#define all(x)                      (x).begin(),(x).end()
#define F                           first
#define S                           second
#define Mp                          make_pair
#define SZ(x)			    		(int)x.size()
#define fast_io                     ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define file_io                     freopen("in.txt" , "r+" , stdin) ; freopen("out.txt" , "w+" , stdout);

const int N = 1e6 + 10;
const ll mod = 1e9 + 7;
const ll mod2 = 998244353;
const ll inf = 8e18;
const int LOG = 22;

ll pw(ll a , ll b, ll M)  { return (!b ? 1 : (b & 1 ? (a * pw(a * a % M, b / 2, M)) % M : pw(a * a % M, b / 2, M))); }

bool TYPE = 1;
struct Line
{///k -> shib m -> arz az mabda p -> noghte shoro baze mofid
	mutable ll k, m, p;
	bool operator<(const Line& o) const { return TYPE ? k < o.k : p < o.p; }
};
 
struct CHT : multiset<Line>
{
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	static const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { /* floored division */ return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y)
	{
		if (y == end()) return x->p = inf, 0;
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m)
	{
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}
	ll query(ll x)
	{
		assert(!empty());
		TYPE = 0 ; auto l = *lower_bound({0 , 0 , x}); TYPE = 1;
		return l.k * x + l.m;
	}
} cht;

int n, q, last[N];

ll now[N], speed[N];

int main()
{
	scanf("%d%d", &n, &q);
	while(q --)
	{
		int tp; scanf("%d", &tp);
		switch(tp)
		{
			case 1:
				int T, id, NS;
				scanf("%d%d%d", &T, &id, &NS);
				now[id] += 1ll * (T - last[id]) * speed[id];
				last[id] = T;
				speed[id] = NS;
				cht.add(NS, now[id] - 1ll * NS * T);
				break;
			case 2:
				scanf("%d", &T);
				printf("%lld\n", cht.query(T));
				break;
		}
	}
    return 0;
}

/** test corner cases(n = 1?) watch for overflow or minus indices **/

