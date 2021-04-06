#include "bits/stdc++.h"
using namespace std;

#define pb  push_back
#define mp  make_pair
#define ll  long long
#define itr iterator

typedef pair<ll,ll> pii;

const ll MAX=2e5+9;
const ll INF=1e12;
const ll mod=1e9+7;

vector<pii> vec;

ll N,K,W,res,cur,arr[MAX],tem[55],prefix[MAX][55],suffix[MAX][55];

void cal(int l,int r)
{
	for(int A=l;A<=r;A++)
		for(int B=0;B<K;B++)
			prefix[A][B]=0,
			suffix[A][B]=0;
	prefix[l][0]++;
	prefix[l][arr[l]%K]++;
	for(int A=l+1;A<=r;A++)
	{
		for(int B=0;B<K;B++)
			tem[B]=0;
		for(int B=0;B<K;B++)
		{
			tem[(arr[A]+B)%K]+=prefix[A-1][B];
			tem[(arr[A]+B)%K]%=mod;
		}
		for(int B=0;B<K;B++)
			prefix[A][B]=(prefix[A-1][B]+tem[B])%mod;
	}
	for(int B=0;B<K;B++)
		tem[B]=0;
	suffix[r][arr[r]%K]++;
	tem[arr[r]%K]++;
	for(int A=r-1;A>=l;A--)
	{
		suffix[A][arr[A]%K]++;
		suffix[A][arr[A]%K]%=mod;
		for(int B=0;B<K;B++)
		{
			suffix[A][(arr[A]+B)%K]+=tem[B];
			suffix[A][(arr[A]+B)%K]%=mod;
		}
		for(int B=0;B<K;B++)
		{
			tem[B]+=suffix[A][B];
			tem[B]%=mod;
		}
	}
	return ;
}

ll exclude()
{	
	for(int A=1;A<=N;A++)
		for(int B=0;B<K;B++)
			prefix[A][B]=0;
	prefix[1][0]++;
	prefix[1][arr[1]%K]++;
	for(int A=2;A<=N;A++)
	{
		for(int B=0;B<K;B++)
			tem[B]=0;
		for(int B=0;B<K;B++)
		{
			tem[(arr[A]+B)%K]+=prefix[A-1][B];
			tem[(arr[A]+B)%K]%=mod;
		}
		for(int B=0;B<K;B++)
			prefix[A][B]=(tem[B]+prefix[A-1][B])%mod;
	}
	return (prefix[N][0]-1+mod)%mod;
}

signed main()
{
	ios_base::sync_with_stdio(false);

	int tc;
	cin>>tc;
	while(tc--)
	{
		res=0;
		vec.clear();
		cin>>N>>K>>W;
		for(int A=1;A<=N;A++)
			cin>>arr[A];
		if(W>0)
		{
			for(int A=1;A<=N;A+=W)
			{
				cal(A,min(A+W-1,N));
				vec.pb(mp(A,min(A+W-1,N)));
			}
			for(int B=0;B<vec.size()-1;B++)
			{
				for(int C=vec[B].second;C>=vec[B].first;C--)
				{
					for(int D=0;D<K;D++)
					{
						cur=suffix[C][D];
						if(C+W-1>vec[B].second)
							cur=(cur*prefix[min(C+W-1,N)][(K-D)%K])%mod;			
						else if(D>0)
							cur=0;
						res=(res+cur)%mod;
					}
				}
			}
			res=(res+prefix[N][0]-1+mod)%mod;
		}	
		res=(exclude()-res+mod)%mod;
		cout<<res<<"\n";
	}
	return 0;
}