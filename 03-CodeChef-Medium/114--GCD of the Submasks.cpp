#include<iostream>
#include<vector>
using namespace std;
typedef long long ll;
ll gcd(ll n)
{
	ll res=1;
	while(1)
	{
		if(n&1) 
		break;
		res<<=1;
	n>>=1;
	}
	return res;
}
ll power(ll x,ll y,ll d)
{
	 ll res=1;
	 while(y>0)
	 {
	 	if(y&1)
	 	res=((res%d)*(x%d))%d;
	 	x=((x%d)*(x%d))%d;
	 	y>>=1;
	 }
	 res%=d;
	 return res;
}
int main() {
	// your code goes here
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	ll d=998244353;
	ll dp[1000001];
	dp[0]=0;
	for(ll i=1;i<1000001;++i)
	{
		if(i%2)
		dp[i]=i%d;
		else
		dp[i]=power(i,gcd(i),d)%d;
		
		dp[i]=(dp[i]+dp[i-1])%d;
	}
	ll t;cin>>t;
	while(t--)
	{
	 	 ll n;cin>>n;
	 	 cout<<dp[n]<<"\n";
	}
	return 0;
}
