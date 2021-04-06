#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 500;
const ll INF = (1LL << 60);
const int prm[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

ll mul_mod(ll a, ll b, ll mod) {
    ll ret = 0;
    while( b ) {
        if( b & 1 ) ret = (ret + a)%mod;
        a = (a + a)%mod;
        b >>= 1;
    }
    return ret;
}
ll pow_mod(ll b, ll p, ll mod) {
    ll ret = 1;
    while( p ) {
        if( p & 1 ) ret = mul_mod(ret, b, mod);
        b = mul_mod(b, b, mod);
        p >>= 1;
    }
    return ret;
}
bool Miller_Rabin(ll x, ll y, ll z) {
    ll pw = pow_mod(y, z, x);
    if( pw == 1 || pw == x-1 ) return true;
    for(;z!=x-1;z<<=1) {
        pw = mul_mod(pw, pw, x);
        if( pw == x-1 ) return true;
        else if( pw == 1 ) return false;
    }
    return false;
}
bool Prime_Test(ll x) {
	if( x == 1 ) return false;
    for(int i=0;i<10;i++)
        if( x == prm[i] ) return true;
        else if( x % prm[i] == 0 ) return false;
    ll k = x-1;
    while( k % 2 == 0 ) k /= 2;
    for(int i=0;i<10;i++)
        if( !Miller_Rabin(x, prm[i], k) ) return false;
    return true;
}

struct FlowGraph{
	#define MAXV 2*MAXN
	#define MAXE MAXV*MAXV
	struct edge{
		int to; ll cap, flow;
		edge *nxt, *rev;
	}edges[MAXE + 5], *adj[MAXV + 5], *cur[MAXV + 5], *ecnt;
	void clear() {
		ecnt = edges;
		for(int i=0;i<=MAXV;i++)
			adj[i] = NULL;
	}
	void addedge(int u, int v, ll c) {
		edge *p = (++ecnt), *q = (++ecnt);
		p->to = v, p->cap = c, p->flow = 0;
		p->nxt = adj[u], adj[u] = p;
		q->to = u, q->cap = 0, q->flow = 0;
		q->nxt = adj[v], adj[v] = q;
		p->rev = q, q->rev = p;
//		printf("! %d %d %lld\n", u, v, c);
	}
	int d[MAXV + 5], s, t, n;
	int que[MAXV + 5], hd, tl;
	bool relabel() {
		for(int i=0;i<=n;i++)
			d[i] = n + 5, cur[i] = adj[i];
		d[que[hd = tl = 1] = t] = 0;
		while( hd <= tl ) {
			int x = que[hd++];
			for(edge *p=adj[x];p;p=p->nxt)
				if( p->rev->cap > p->rev->flow && d[x] + 1 < d[p->to] )
					d[que[++tl] = p->to] = d[x] + 1;
		}
		return !(d[s] == t + 5);
	}
	ll aug(int x, ll tot) {
		if( x == t ) return tot;
		ll sum = 0;
		for(edge *&p=cur[x];p;p=p->nxt) {
			if( p->cap > p->flow && d[p->to] + 1 == d[x] ) {
				ll del = aug(p->to, min(tot - sum, p->cap - p->flow));
				sum += del, p->flow += del, p->rev->flow -= del;
				if( sum == tot ) break;
			}
		}
		return sum;
	}
	ll max_flow(int _s, int _t) {
		s = _s, t = _t; ll flow = 0;
		while( relabel() )
			flow += aug(s, INF);
		return flow;
	}
}G;

bool tag[MAXN + 5];
void dfs(int x) {
	tag[x] = true;
	for(FlowGraph::edge *p=G.adj[x];p;p=p->nxt)
		if( p->cap > p->flow && !tag[p->to] ) dfs(p->to);
}

map<ll, int>mp;
ll u[MAXN + 5], c[MAXN + 5]; int N;
int d[MAXN + 5], a[MAXN + 5][MAXN + 5];
void dfs2(int x, int p) {
	d[x] = p;
	for(int i=1;i<=N;i++)
		if( d[i] == -1 && a[x][i] )
			dfs2(i, p^1);
}
int main() {
	scanf("%d", &N);
	for(int i=1;i<=N;i++)
		scanf("%lld%lld", &u[i], &c[i]), mp[u[i]] = i;
	G.clear(), G.s = 0, G.n = G.t = N + 1;
	for(int i=1;i<=N;i++)
		for(int j=1;j<=N;j++)
			if( u[i] > u[j] && u[i] % u[j] == 0 && Prime_Test(u[i]/u[j]) )
				a[i][j] = a[j][i] = true;
	for(int i=1;i<=N;i++) d[i] = -1;
	for(int i=1;i<=N;i++)
		if( d[i] == -1 ) dfs2(i, 0);
	for(int i=1;i<=N;i++) {
		if( d[i] ) {
			G.addedge(G.s, i, c[i]);
			for(int j=1;j<=N;j++)
				if( a[i][j] ) G.addedge(i, j, INF);
		}
		else G.addedge(i, G.t, c[i]);
	}
	G.max_flow(G.s, G.t);
	ll ans = INF; G.relabel();
	for(int i=1;i<=N;i++)
		if( (!d[i]) && G.d[i] != G.n + 5 ) ans = min(ans, u[i]);
	dfs(G.s);
	for(int i=1;i<=N;i++)
		if( d[i] && tag[i] ) ans = min(ans, u[i]);
	if( ans != INF ) printf("Bran %lld\n", ans);
	else puts("Tyrion");
}