#include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define endl "\n"
ll mod=1000000007;
ll pow(ll a,ll n)
{
    if(n==0)return 1;
    ll temp=pow(a,n/2);
    temp=temp*temp%mod;
    if(n%2)temp=a*temp%mod;
    return temp;
    
}
ll inverse(ll a)
{
    return pow(a,mod-2);
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
	    ll n,m,w,x,y,z,i;
	    cin>>n>>m;
	    ll a[n+2]={0},b[n+1];
	    
	    for(i=1;i<=n;i++)
	    b[i]=i;
	    
	    while(m--)
	    {
	        cin>>w>>x>>y>>z;
	        if(w==1)
	        {
	            a[x]+=z;a[y+1]-=z;
	        }
	        else
	        {
	            a[x]-=z;a[y+1]+=z;
	        }
	    }
	    b[1]+=a[1];
	    for(i=2;i<=n;i++)
	    {
	        a[i]+=a[i-1];
	        b[i]+=a[i];
	    }
	    ll mi=INT_MAX,ma=INT_MIN;
	    for(i=1;i<=n;i++)
	    {mi=min(mi,b[i]);ma=max(ma,b[i]);}
	    cout<<ma-mi<<endl;
	}
	return 0;
}
