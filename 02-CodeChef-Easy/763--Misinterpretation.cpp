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
	    ll n,p=26,c=0,i,j;
	    cin>>n;
	    bool a[n+1]={false};
	    for(i=1;i<=n;i++)
	    {
	        if(a[i]==false)
	        {
	            c++;j=i;
	            while(a[j]==false)
	            {
	                a[j]=true;
	                if(j<=n/2)
	                j=j*2;
	                else
	                j=2*(j-n/2-1)+1;
	            }
	        }
	    }
	    cout<<pow(p,c)<<endl;
	}
	return 0;
}
