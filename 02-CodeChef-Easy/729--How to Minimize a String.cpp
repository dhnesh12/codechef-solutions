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
	   ll n;
	   cin>>n;
	   string str,str1,str2;
	   cin>>str;
	   ll a[26]={0},i,j=0,k;
	   for(i=0;i<str.length();i++)
	   a[str[i]-'A']++;
       
       for(i=0;i<26;i++)
       {
          while(str[j]-'A'==i)
          {cout<<str[j];a[i]--;j++;}
          if(a[i])break;
       }
	   if(i<26)
	   {   
	       ll i1=i,j1=j;
	       for(k=str.length()-1;k>=0;k--)
	       if(str[k]-'A'==i)break;
	       str1+=char(i+'A');
	       for(;j<str.length();j++)
	       if(j!=k)
	       str1+=str[j];
	       
	       for(k=j1+1;k<n;k++)
	       if(str[k]<=str[j1])
	       str2+=str[k];
	       else
	       break;
	       
	       str2+=str[j1];
	       for(;k<n;k++)
	       str2+=str[k];
	       
	       if(str1<str2)
	       cout<<str1;
	       else
	       cout<<str2;
	   }
	   cout<<endl;
	}
	return 0;
}
