#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define endl "\n"
ll mod=1000000007;
ll power(ll a,ll n)
{
    if(n==0)return 1;
    ll temp=power(a,n/2);
    temp=temp*temp%mod;
    if(n%2)temp=a*temp%mod;
    return temp;
    
}
ll inverse(ll a)
{
    return power(a,mod-2);
}
ll gcd(ll a,ll b)
{
    if(b==0)return a;
    return gcd(b,a%b);
}
void dfs(ll u,vector<ll>v[],bool vis[])
{
    vis[u]=true;
    for(ll x:v[u])
    {
        if(vis[x]==false)
        dfs(x,v,vis);
    }
}
int main() {
	// your code goes here
		                             ios::sync_with_stdio(0);
                                     cin.tie(0),cout.tie(0);
	ll t;
	cin>>t;
	while(t--)
	{   
	    ll l,r,i,j,ans=0;
	    cin>>l>>r;
	    if(l==1)ans++;
	    for(i=2;i<=r;i*=2)
	    {
	     if(i>=l&&i<=r)
	       ans++;
	        
	      for(j=i*3;j<=r;j*=3)
	      if(j>=l&&j<=r)
	       ans++;
	      
	        
	    }
	    cout<<ans<<endl;
	    
	}
	return 0;
}
