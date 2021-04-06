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
	ll t=1;
	//cin>>t;
	while(t--)
	{   
	    ll n,m,l,e1=0,e2=0;
	    cin>>n>>m;
	    ll a[n+1][m+1],i,j,k;
	    for(i=1;i<=n;i++)
	    for(j=1;j<=m;j++)
	    cin>>a[i][j];
	    cin>>l;
	    while(l--)
	    {
	        cin>>i>>j;
	        
	        if(e1!=-1&&i>0&&i<=n&&j>0&&j<=m)
	        e1+=a[i][j];
	        else
	        e1=-1;
	        
	        k=i;i=j;j=k;
	        
	        if(e2!=-1&&i>0&&i<=n&&j>0&&j<=m)
	        e2+=a[i][j];
	        else
	        e2=-1;
	    }
	    cout<<max(e1,e2)<<endl;
	}
	return 0;
}
