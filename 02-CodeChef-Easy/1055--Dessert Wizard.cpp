#include<bits/stdc++.h>
#define ll long long
#define in insert
#define pb push_back
#define endl '\n'
#define ub upper_bound
#define lb lower_bound
#define pf pop_front
#define all(v) (v).begin(),(v).end()
#define fi first
#define se second
#define fast ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);srand(time(0));
using namespace std;
vector<ll> a;
void fun()
{
	int n;cin>>n;
	
	a.resize(n);
	for(auto &i:a)cin>>i;
	
	
	ll premax[n],premin[n],sufmax[n],sufmin[n];
	
	premax[0]=a[0];
	premin[0]=a[0];
	sufmax[n-1]=a[n-1];
	sufmin[n-1]=a[n-1];
	
	for(int i=1;i<n;i++)premax[i]=max(a[i],a[i]+premax[i-1]),premin[i]=min(a[i],a[i]+premin[i-1]);
	
	for(int i=n-2;i>=0;i--)sufmax[i]=max(a[i],a[i]+sufmax[i+1]),sufmin[i]=min(a[i],a[i]+sufmin[i+1]);
	
	/*for(auto i:premax)cout<<i<<" ";
	cout<<endl;
	for(auto i:premin)cout<<i<<" ";
	cout<<endl;
	for(auto i:sufmax)cout<<i<<" ";
	cout<<endl;
	for(auto i:sufmin)cout<<i<<" ";cout<<endl;*/
	ll ans=0;
	for(int i=0;i<n-1;i++)ans=max(premax[i]-sufmin[i+1],ans),ans=max(ans,sufmax[i+1]-premin[i]);
	
	cout<<ans<<endl;
}
int main()
{
    fast;
    int t=1;
    cin>>t;
    while(t--)
    {
    	fun();
	}
}