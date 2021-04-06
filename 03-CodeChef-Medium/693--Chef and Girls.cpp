#include<bits/stdc++.h>
#define ll long long
using namespace std;
class edge
{
	public:
		ll y,l,r;
		
		edge(ll x,ll v,ll z)
		{
			y=x;l=v;r=z;
		}
};

ll func(ll l1,ll r1,ll l,ll r)
{
	ll s= max(r,r1)-min(l,l1)+1;
	
	return s-(r-l+1);
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    
	ll n,m,x,y,l,r;
	
	cin>>n>>m;
	
	vector<edge*> ve[n+1];
	
	for(ll i=0;i<m;i++)
	{
		cin>>x>>y>>l>>r;
		
		edge *e=new edge(y,l,r);
		
		ve[x].push_back(e);
	}
	ll res[40][40];
	for(ll l=0;l<40;l++)
	{
		for(ll r=0;r<40;r++)
		res[l][r]=(ll)(1e9);
	}
	
	//memset(res,0,sizeof(res));
	for(ll l=1;l<=32;l++)
	{
		for(ll r=l;r<=32;r++)
		{
			for(ll k=0;k<ve[1].size();k++)
			{
				ll sp=func(l,r,ve[1][k]->l,ve[1][k]->r);
				ll ind=ve[1][k]->y;
				
				while(ve[ind].size()!=0)
				{
					sp+=func(l,r,ve[ind][0]->l,ve[ind][0]->r);
					ind=ve[ind][0]->y;
				}
				res[l][r]=min(res[l][r],sp);
			}
		}
	}
	
	for(ll r=1;r<=32;r++)
	{
		for(ll l=1;l<=r;l++)
		{
			for(ll m=l;m<r;m++)
			{
				res[l][r]=min(res[l][r],res[l][m]+res[m+1][r]);
			}
		}
	}
	cout<<res[1][32]<<"\n";
}