#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 998244353ll
#define ROD 1000000009ll
#define INF 1e18
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<pair<ll,ll>,ll>
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
#define MAXN 300005
ll n,m,s,t,tt;
vector <ll> vr[MAXN];
ll dist[MAXN][2],visit[MAXN][2],und[MAXN];
queue <pii> qr;
int main()
{
	// freopen("input.txt","r",stdin);	
	scanf("%lld",&tt);
	while(tt--)
	{
		scanf("%lld %lld %lld %lld",&n,&m,&s,&t);
		rep(i,0,n+4)
		{
			vr[i].clear();
			visit[i][0]=visit[i][1]=0;
			dist[i][0]=dist[i][1]=0;
			und[i]=0;
		}
		rep(i,0,m)
		{
			ll x,y;
			scanf("%lld %lld",&x,&y);
			und[x]++,und[y]++;
			vr[x].pb(y);
			vr[y].pb(x);
		}
		visit[t][0]=visit[t][1]=1;
		dist[t][0]=dist[t][1]=0;
		qr.push(mp(t,0));
		qr.push(mp(t,1));
		// cout<<qr.front().fi<<"A";
		while(!qr.empty())
		{
			pii p=qr.front();
			// cout<<p.fi<<" "<<p.se<<"\n";
			qr.pop();
			if(p.se==0) // undirected
			{	
				rep(i,0,vr[p.fi].size())
				{
					ll idx=vr[p.fi][i];
					if(!visit[idx][1])
					{
						visit[idx][1]=1;
						dist[idx][1]=1+dist[p.fi][0];
						qr.push(mp(idx,1));
					}
				}
			}
			else  // directed
			{
				rep(i,0,vr[p.fi].size())
				{
					ll idx=vr[p.fi][i];;
					if(!visit[idx][0])
					{
						und[idx]--;
						if(und[idx]==1)
						{
							qr.push(mp(idx,0));
							visit[idx][0]=1;
						}
						dist[idx][0]=1+dist[p.fi][1];
					}
				}
			}
		}
		// rep(i,1,n+1)
		// {
		// 	cout<<i<<"  "<<visit[i][0]<<" "<<visit[i][1]<<" "<<dist[i][0]<<" "<<dist[i][1]<<"\n";
		// }
		if(visit[s][1])
		{
			printf("%lld\n",dist[s][1]/2+dist[s][1]%2);
		}
		else
			printf("-1\n");
	}	
}