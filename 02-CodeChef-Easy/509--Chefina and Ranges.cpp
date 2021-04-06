#include<bits/stdc++.h>
#define ll  long long
#define pb push_back
#define mkp make_pair
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL);
#define pi 3.14159265359
#define all(x) x.begin(),x.end()
#define zer(x) memset(x,0,sizeof x)
//PLEASE DON'T HACK I AM POOR :(
using namespace std;
vector<ll>arr(1e5);
int main()
{
	fastio
	ll t;
	cin>>t;
	while(t--)
	{
		ll i,j,k,l,m,n;
		cin>>n;
		vector<pair<ll,ll> >arr(n);
		for(i=0;i<n;i++)cin>>arr[i].first>>arr[i].second;
		sort(all(arr));
		ll ans=1e18;
		set<pair<ll,ll> >q;
		set<pair<ll,ll> >::iterator it;
		for(i=0;i<n;i++)
		{
			ll flag=1;
			while(!q.empty()&&flag)
			{
				it=q.begin();
				ll num=(*it).first;
				if(num<arr[i].first)
				{
					q.erase(it);
				}
				else flag=0;
			}
		ll common=(ll)q.size();
		if(common!=i)
		{
			ans=min(ans,common);
		}
		q.insert({arr[i].second,i});
		}
		if(ans==1e18)ans=-1;
		cout<<ans<<"\n";
	}
    return 0;
}
	