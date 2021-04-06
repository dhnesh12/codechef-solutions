#include <bits/stdc++.h>
#define ll long long int
#define pb push_back
#define mp make_pair
using namespace std;

int main() {
ll t;
cin>>t;
while(t--)
{
	ll n;
	cin>>n;
	ll a[n];
	ll b[n];
	vector<pair<ll,ll>>v;
	vector<ll>v1;
	for(ll i=0;i<n;i++)
{
    ll a;
    cin>>a;
    v1.pb(a);
}
	for(ll i=0;i<n;i++)
{	ll a;
cin>>a;
v.pb(mp(a,i));
}
ll c=0;
for(ll i=0;i<n;i++)
{
    if(v1[i]==v[i].first)
    {
        ll f=0;
        for(ll j=0;j<i;j++)
        {
            if(v1[j]!=v1[i]&&v[j].first!=v1[i])
            {
                swap(v[j],v[i]);
                f=1;
                break;
            }
        }
    
    if(f==0)
    {
        for(ll j=i+1;j<n;j++)
        {
            if(v[j].first!=v1[i])
            {
                swap(v[j],v[i]);
                f=1;
                break;
            }
        }
    }
    if(f==0)
    c++;
    }
}
cout<<c<<endl;
for(ll i=0;i<n;i++)
cout<<v[i].second+1<<" ";
cout<<endl;
}
	return 0;
}
