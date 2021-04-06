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
int main() {
	// your code goes here
		                             ios::sync_with_stdio(0);
                                     cin.tie(0),cout.tie(0);
	ll t;
	cin>>t;
	while(t--)
	{   
	    ll x,y,ans=0;
	    cin>>x>>y;
	    
	    if(x==0)
	    {
	        if(y%2==0)ans=1;
	    }
	    else if(y==0)
	    {
	        if(x>0)
	        {
	          if(x%2)ans=1;   
	        }
	        else
	        {
	            if(x%2==0)ans=1;
	        }
	    }
	    else if(x>0&&y>0)
	    {
	        if((x%2&&y<=x+1)||(y%2==0&&x<y))ans=1;
	    }
	    else if(x<0&&y>0)
	    {
	        if((x%2==0&&y<=-x)||(y%2==0&&-x<=y))ans=1;
	    }
	    else if(x<0&&y<0)
	    {
	        if((x%2==0&&-y<=-x)||(y%2==0&&-x<=-y))ans=1;
	    }
	    else if(x>0&&y<0)
	    {
	        if((x%2&&-y<x)||(y%2==0&&x<=-y+1))ans=1;
	    }
	    
	    if(ans)
	    cout<<"YES\n";
	    else
	    cout<<"NO\n";
	}
	return 0;
}
