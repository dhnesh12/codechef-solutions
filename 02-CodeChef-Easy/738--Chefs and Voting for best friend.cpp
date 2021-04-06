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
	    ll n,i,j,sum=0,x=1;
	    cin>>n;
	    ll a[n+1],b[n+1];
	    for(i=1;i<=n;i++)
	    {
	        cin>>a[i];sum+=a[i];
	        if(a[i]>=n)x=0;
	    }
	    vector<ll>v;
	    if(x&&sum==n)
	    {   
	        j=1;
	        for(i=1;i<=n;i++)
	        while(a[i]--)
	        b[j++]=i;
	        
	        for(i=1;i<=n;i++)
	        if(i==b[i]){v.push_back(i);}
	        
	        if(v.size()>1)
	        for(i=0;i<v.size()-1;i+=2)
	        {j=b[v[i]];b[v[i]]=b[v[i+1]];b[v[i+1]]=j;}
	        
	        if(v.size()%2)
	        for(i=1;i<=n;i++)
	        if(b[i]!=v[v.size()-1])
	        {
	            j=b[i];b[i]=b[v[v.size()-1]];b[v[v.size()-1]]=j;break;
	        }
	        for(i=1;i<=n;i++)
	        cout<<b[i]<<" ";cout<<endl;
	    }
	    else
	    cout<<"-1\n";
	}
	return 0;
}
