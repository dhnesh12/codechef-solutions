#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD3 998244353ll
#define MOD2 1000000009ll
#define MOD 1000000007ll
#define INF 1e16
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<ll,pair<ll,ll>>
// #define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %lld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )
#define MAXN 100005
#include<bits/stdc++.h>
#define x first
#define y second
using namespace std;

// typedef long long ll;
typedef pair<ll,ll> point;
ll cross (point a, point b, point c) { return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);}
vector<point> ConvexHull(vector<point>&p, int n) {
    int sz = 0;
    vector<point> hull(n + n);
    sort(p.begin(), p.end());
    for(int i = 0; i < n; ++i) {
        while (sz > 1 and cross(hull[sz - 2], hull[sz - 1], p[i]) <= 0)
        {
         	--sz;
        }
        hull[sz++] = p[i];
    }
    for(int i = n - 2, j = sz + 1; i >= 0; --i) {
        while (sz >= j and cross(hull[sz - 2], hull[sz - 1], p[i]) <= 0) --sz;
            hull[sz++] = p[i];
    } hull.resize(sz - 1);
    return hull;
}
vector<point> inp,op;
ll ans=0,u,v,w,n;
ll sqr(ll a,ll b)
{
	ll x=op[a].x-op[b].x,y=op[a].y-op[b].y;
	return x*x+y*y;	
}
int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);
    ll t;
    scanf("%lld",&t);
    while(t--)
    {
    	inp.clear(),op.clear();
    	scanf("%lld",&n);
	    for (int i=0;i<n;i++)
	    {
	    	scanf("%lld %lld",&u,&v);
	    	inp.push_back(mp(u,v));
	    }
	   
	    op=ConvexHull(inp,n);
	   	ll ss=op.size();
	   	rep(i,0,ss)
	   		op.pb(op[i]);
	   	ll l=0,max_=0,g=0;
	   	rep(i,0,ss)
	   	{
	   		if(sqr(i,0)>max_)
	   			max_=sqr(i,0),l=i;
	   	}
	   	g=max_;
	   	rep(i,1,ss)
	   	{
	   		while(1)
	   		{
	   			ll a=0,b=0;
		   		a=sqr(l,i);
		   		b=sqr(l+1,i);
		   		if(a>b)
		   			break;
		   		l++;
	   		}
	   		g=max(g,sqr(l,i));
	   	}
	   	printf("%lld\n",g);
	}
}