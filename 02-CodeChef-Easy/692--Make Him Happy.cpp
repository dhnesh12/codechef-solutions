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
	ll t=1;
	//cin>>t;
	while(t--)
	{   
	    ll n,k,ans=1;
	    cin>>n>>k;
	    ll a[n],i,j;
	    for(i=0;i<n;i++)
	    cin>>a[i];
	    
	    i=1;j=n-2;
	    unordered_set<ll>s;s.insert(a[0]);s.insert(a[n-1]);
	    
	    if(a[0]*2==k||a[0]+a[n-1]!=k)
	    {
	    while(i<j)
	    {
	       
	       if(a[i]*2!=k&&s.find(k-a[i])!=s.end())
	       break;
	       s.insert(a[i]);
	       
	       if(a[j]*2!=k&&s.find(k-a[j])!=s.end())
	       break;
	       s.insert(a[j]);
	       
	       i++;j--;
	    }
	    
	    if(i==j)
	    {
	         if(a[i]*2!=k&&s.find(k-a[i])!=s.end())
	         cout<<i+1<<endl;
	         else
	         cout<<"-1\n";
	         
	    }
	    else if(i<j)
	    cout<<i+1<<endl;
	    else
	    cout<<"-1\n";
	    }
	    else
	    cout<<"1\n"<<endl;
	    
	}
	return 0;
}
