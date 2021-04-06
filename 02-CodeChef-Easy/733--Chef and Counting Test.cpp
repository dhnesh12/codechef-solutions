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
	    string str,str1;
	    cin>>str;
	    ll i,j=0,ans=0;
	    for(i=1;i<str.length();i++)
	    {
	        if(str[i-1]==str[i])
	        continue;
	        ans+=(i-j)*(i-j-1)/2;
	        j=i;
	    }
	    ans+=(i-j)*(i-j-1)/2;
	    str1+=str[0];
	    for(i=1;i<str.length();i++)
	    {
	        if(str[i]!=str[i-1])
	        str1+=str[i];
	    }
	    for(i=1;i<str1.length()-1;i++)
	    if((str1[i-1]==str1[i+1])&&str1[i]!=str1[i+1])ans++;
	    cout<<ans<<endl;
	}
	return 0;
}
