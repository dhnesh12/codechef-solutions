#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 998244353ll
#define MOD2 1000000009ll
#define MOD3 1000000007ll
#define INF 1e16
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
#define MAXN 100005
struct comp{
	bool operator () (pii a,pii b) const
	{
		// return true;	
		if(a.fi==b.fi)
		{
			return a.se<b.se;
		}
		else
		{	
			return a.fi>b.fi;
		}
	}	
};
set <pii,comp> sr;
set <pii> qr;
map <ll,ll> fr;
ll t,n,k,ar[MAXN];
set <ll> temp;
int main()
{
	scanf("%lld",&t);
	while(t--)
	{
		// clear the air
		fr.clear();
		sr.clear(); 
		qr.clear();

		bool ok=1;
		scanf("%lld %lld",&n,&k);
		k=n/k;
		rep(i,0,n)
		{
			scanf("%lld",&ar[i]);
			fr[ar[i]]++;
			if(fr[ar[i]]>k)
				ok=0;
		}
		if(!ok)
		{
			printf("-1\n");
			continue;
		}

		for(auto x: fr)
		{
			sr.insert(mp(x.se,x.fi));
			qr.insert(mp(x.fi,x.se));
		}

		ll x;
		rep(i,0,k)
		{
			temp.clear();
			for(auto a: sr)
			{
				if(a.fi+i==k)
					temp.insert(a.se);
				else
					break;
			}
			for(auto a: qr)
			{
				if(temp.find(a.fi)!=temp.end())
					continue;
				if(temp.size()==n/k)
					break;
				temp.insert(a.fi);
			}
			for(auto a: temp)
			{
				printf("%lld ",a);
				x=fr[a];
				sr.erase(mp(x,a));
				qr.erase(mp(a,x));
				fr[a]--;
				if(x-1)
				{
					sr.insert(mp(x-1,a));
					qr.insert(mp(a,x-1));
				}
			}
		}
		printf("\n");
	}
}