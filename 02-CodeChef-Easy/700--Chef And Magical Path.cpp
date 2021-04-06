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
	    ll n,m;
	    cin>>n>>m;
	    if(n==1||m==1)
	    {
	        if(max(n,m)==2)
	        cout<<"Yes\n";
	        else
	        cout<<"No\n";
	    }
	    else if(n%2==0||m%2==0)
	    cout<<"Yes\n";
	    else
	    cout<<"No\n";
	     
	    
	}
	return 0;
}
