#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 998244353ll
#define MOD2 1000000009ll
#define MOD3 1000000007ll
// #define INF 1e9
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<ll,pair<ll,ll>>
#define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %lld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )
#define MAXN 200005
    	const ll INF = 1000*1000*1000;

struct rib {
	ll b, u;
	double c;
	ll f;
	size_t back;
};

void add_rib (vector < vector<rib> > & g, ll a, ll b, ll u, double c) {
	rib r1 = { b, u, c, 0, g[b].size() };
	rib r2 = { a, 0, -c, 0, g[a].size() };
	g[a].push_back (r1);
	g[b].push_back (r2);
}

double eps=1e-9;
int main()
{
	// freopen("input.txt","r",stdin);
	ll test;
	scanf("%lld",&test);

	while(test--)
	{
		ll dishes,days,lim;
		double pr[55][55];	
			
		scanf("%lld %lld %lld",&dishes,&days,&lim);

		ll n=dishes+days+2, m;
		vector < vector<rib> > g (n);  //  ***** INITIALISE *****  initialise n in the last
		ll s=0, t=n-1;  					   //  ***** INITIALISE *****  initialise s,t,k

		// cout<<dishes<<" "<<days<<"\n";
		rep(i,1,dishes+1)
		{
			rep(j,1,days+1)
			scanf("%lf",&pr[i][j]);
		}

		rep(i,1,dishes+1)
		{
			add_rib(g,0,i,1,0);
			rep(j,1,days+1)
			{
				// cout<<-log(pr[i][j])<<" ";
				add_rib(g,i,dishes+j,1,-log(pr[i][j]));
			}
		}
		rep(i,1,days+1)
		{
			add_rib(g,dishes+i,days+dishes+1,1,0);
			add_rib(g,dishes+i,days+dishes+1,lim-1,100);
		}
		// ... чтение графа ...
		// cout<<"SA";
		ll flow = 0;
		double cost = 0,k=INF;
		while (flow < k) {
			// cout<<flow<<" "<<cost<<"   ";
			vector<ll> id (n, 0);
			vector<double> d (n, INF);
			vector<ll> q (n);
			vector<ll> p (n);
			vector<size_t> p_rib (n);
			ll qh=0, qt=0;
			q[qt++] = s;
			d[s] = 0;
			while (qh != qt) {
				ll v = q[qh++];
				id[v] = 2;
				if (qh == n)  qh = 0;
				for (size_t i=0; i<g[v].size(); ++i) {
					rib & r = g[v][i];
					if (r.f < r.u && d[v] + r.c +eps < d[r.b]) {
						d[r.b] = d[v] + r.c;
						if (id[r.b] == 0) {
							q[qt++] = r.b;
							if (qt == n)  qt = 0;
						}
						else if (id[r.b] == 2) {
							if (--qh == -1)  qh = n-1;
							q[qh] = r.b;
						}
						id[r.b] = 1;
						p[r.b] = v;
						p_rib[r.b] = i;
					}
				}
			}
			// cout<<"BB ";
			if (d[t] == INF)  break;
			ll addflow = k - flow;
			// cout<<"SS";
			for (ll v=t; v!=s; v=p[v]) {
				// cout<<v<<" "<<p[v]<<"\n";
				ll pv = p[v];  size_t pr = p_rib[v];
				addflow = min (addflow, g[pv][pr].u - g[pv][pr].f);
			}
			// cout<<"CC ";
			for (ll v=t; v!=s; v=p[v]) {
				ll pv = p[v];  size_t pr = p_rib[v],  r = g[pv][pr].back;
				g[pv][pr].f += addflow;
				g[v][r].f -= addflow;
				cost += g[pv][pr].c * addflow;
			}
			flow += addflow;
		}	
		cost-=(100*(dishes-days));
		// cout<<cost<<" ";
		cost=exp(-cost);
		printf("%0.9lf\n",cost);
		rep(i,1,dishes+1)
		{
			rep(j,0,g[i].size())
			{
				if(g[i][j].f==1)
					printf("%lld ",g[i][j].b-dishes);
			}
		}
		printf("\n");
	}

	// ... вывод результата ...

}

