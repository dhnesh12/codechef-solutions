#include<bits/stdc++.h>

#define fr(i,lb,ub) for(ll i=lb;i<=(ll)ub;i++)
#define rf(i,ub,lb) for(ll i=ub;i>=(ll)lb;i--)
#define sll(n) scanf("%lld",&n)

#define ll long long int
#define f first
#define s second
#define pb push_back
#define PII pair<ll,ll>
#define mp(a,b) make_pair(a,b)
#define MOD 1000000007
#define N 1000005
#define LN 20
#define inf 100000000000000000LL
using namespace std;

ll n, bridges, par[N], bl[N], comp[N], sz[N];
ll bsz[N];
ll cu, vis[N];
void init()
{
	for (ll i = 0; i < N; i++) {
		bl[i] = comp[i] = i;
		sz[i] = 1;
		bsz[i] = 1;
		par[i] = -1;
		vis[i] = 0;
	}
	cu = 0;
	bridges = 0;
}
ll get (ll u)
{
	if (u == -1) return -1;
	return (bl[u] == u) ? u : bl[u] = get (bl[u]);
}
ll get_comp (ll u)
{
	u = get (u);
	return comp[u] == u ? u : comp[u] = get_comp (comp[u]);
}
void make_root (ll u)
{
	u = get (u);
	ll root = u, child = -1;
	while (u != -1) {
		ll p = get (par[u]);
		par[u] = child;
		comp[u] = root;
		child = u;
		u = p;
	}
	sz[root] = sz[child];
}

ll ans = 0;
vector<ll>va, vb;
void merge_path (ll a, ll b)
{
	++cu;
	va.clear();
	vb.clear();
	ll lca = -1;
	ll val = 0;
	while (1) {
		if (a != -1) {
			a = get (a);
			va.pb (a);
			if (vis[a] == cu) {
				lca = a;
				break;
			}
			vis[a] = cu;
			a = par[a];
		}
		if (b != -1) {
			b = get (b);
			vb.pb (b);
			if (vis[b] == cu) {
				lca = b;
				break;
			}
			vis[b] = cu;
			b = par[b];
		}
	}
	for (auto w : va) {
		bl[w] = lca;
		if (w == lca) break;
		val += bsz[w];
		ans += (bsz[w] * (bsz[w] - 1)) / 2;
		--bridges;
	}
	for (auto w : vb) {
		bl[w] = lca;
		if (w == lca) break;
		ans += (bsz[w] * (bsz[w] - 1)) / 2;
		val += bsz[w];
		--bridges;
	}
	ans += (bsz[lca] * (bsz[lca] - 1)) / 2;
	bsz[lca] += val;
	ans -= (bsz[lca] * (bsz[lca] - 1)) / 2;
}

void add_edge (ll a, ll b)
{
	a = get (a);
	b = get (b);
	if (a == b) return;
	ll ca = get_comp (a);
	ll cb = get_comp (b);
	if (ca != cb) {
		++bridges;
		if (sz[ca] > sz[cb])
			swap (a, b), swap (ca, cb);
		make_root (a);
		par[a] = comp[a] = b;
		ans += sz[cb] * sz[a];
		sz[cb] += sz[a];
	} else {
		merge_path (a, b);
	}
}

int main()
{
	ll t;
	//scanf ("%lld", &t);
	t = 1;
	while (t--) {
		init();
		ll n, m;
		scanf ("%lld%lld", &n, &m);
		for (ll i = 0; i < m; i++) {
			ll a, b;
			scanf ("%lld%lld", &a, &b);
			add_edge (a, b);
			printf ("%lld\n", ans);
		}
	}
	return 0;
}
