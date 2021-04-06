#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 1000000007ll
#define INF 1e18
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<pair<ll,ll>,pair<ll,ll>>
#define pii pair<ll,ll>
#define fi first
#define se second
#define MAXN 1000005
ll n,m;
vector <pii> vr[1005];
bool visit[1005][1005];
ll ar[1005][1005];
char str[1005][1005];
queue <pii> qr;
int main()
{
	pii p;
	scanf("%lld %lld",&n,&m);
	rep(i,0,n)
	{
		scanf(" %s",str[i]);
		rep(k,0,m)
		{
			ar[i][k]=INF;
			if(str[i][k]=='D')
			{
				qr.push(mp(i,k));
				ar[i][k]=0;
				visit[i][k]=true;
			}
			if(str[i][k]=='@')
				p=mp(i,k);

		}
	}
	while(!qr.empty())
	{	
		pii p=qr.front();
		qr.pop();
		//cout<<p.fi<<" "<<p.se<<"\n";
		visit[p.fi][p.se]=1;
		rep(i,-1,2)
		rep(j,-1,2)
		{
			if(!i&&!j)
				continue;
			if(!(0<=i+p.fi&&i+p.fi<n&&0<=j+p.se&&j+p.se<m))
				continue;
			if(visit[i+p.fi][j+p.se])
				continue;
			ar[i+p.fi][j+p.se]=ar[p.fi][p.se]+1;
			visit[i+p.fi][j+p.se]=true;
			qr.push(mp(i+p.fi,j+p.se));
		}
	}
	// rep(i,0,n)
	// {
	// 	rep(j,0,m)
	// 	cout<<ar[i][j]<<" ";
	// 	cout<<"\n";
	// }
	memset(visit,0,sizeof(visit));
	ll ans=1+ar[p.fi][p.se],f=0;
	visit[p.fi][p.se]=1;
	vr[ans-1].pb(p);
	while(1)
	{
		//cout<<ans<<" ";
		ans--;
		rep(i,0,vr[ans].size())
		qr.push(vr[ans][i]);

		while(!qr.empty())
		{
			pii p=qr.front();
			//cout<<p.fi<<" "<<p.se<<"\n";
			qr.pop();
			if(str[p.fi][p.se]=='$')
			{
				printf("%lld",ans);
				return 0;
			}
			visit[p.fi][p.se]=true;
			rep(i,-1,2)
			rep(j,-1,2)
			{
				if(!i&&!j)
					continue;
				if(!(0<=i+p.fi&&i+p.fi<n&&0<=j+p.se&&j+p.se<m))
					continue;
				if(visit[i+p.fi][j+p.se])
					continue;
				visit[i+p.fi][j+p.se]=true;
				if(ar[i+p.fi][j+p.se]<ans)
					vr[ar[i+p.fi][j+p.se]].pb(mp(i+p.fi,j+p.se));
				else
					qr.push(mp(i+p.fi,j+p.se));
			}
		}
	}
}