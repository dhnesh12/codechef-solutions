#include<bits/stdc++.h>
using namespace std ;
#define ll long long 
#define pb push_back
#define F first
#define S second
#define endl "\n"
#define pii pair<int,int> 
#define fast ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
ll power(ll b,ll e,ll m)
{
	if(e==0) return 1;
	if(e&1) return b*power(b*b%m,e/2,m)%m;
	return power(b*b%m,e/2,m);
}
ll power( ll b, ll e)
{
	if(e==0) return 1;
	if(e&1) return b*power(b*b,e/2);
	return power(b*b,e/2);
}
bool intersect(int a,int b,int c,int d)
{
	if(d<a || c>b)
		return false;
	return true;
}
int main()
{
	fast
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		int l[n],r[n],v[n];
		map<int,vector<pair<int,int>>> m;
		for(int i=0;i<n;i++)
		{
			cin>>l[i]>>r[i]>>v[i];
			m[v[i]].pb({l[i],r[i]});
		}
		int f=1;
		for(auto i:m)
		{
			set<int>s;
			for(auto j:m[i.F])
				{s.insert(j.F);s.insert(j.S);}
			map<int,int> mm;
			for(auto j:s)
			{
				for(auto k:m[i.F])
				{
					if(j>=k.F && j<=k.S)
					{
						mm[j]++;
					}
				}
			}
			for(auto j:mm)
			{
				if(j.S>2)
				{
					f=0;
					break;
				}
			}
			if(f==0)
				break;
		}
		if(f) cout<<"YES";
		else cout<<"NO";
		cout<<endl;
		

	}
	return 0;
}
