#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
using ll=long long;

ll power(ll a,ll n)
{
	ll res=1;
	
	while(n)
	{
		if(n%2)
		res=(res*a)%MOD;
		
		a=(a*a)%MOD;
		n/=2;
	}
	
	return res;
}

main()
{
	ll t,n,m,k;
	cin>>t;
	
	vector<ll> fact(100001),inv(100001);
	fact[0]=1;
	
	for(int i=1;i<100001;i++)
	fact[i]=(fact[i-1]*i)%MOD;
	
	inv[100000]=power(fact[100000],MOD-2);
	
	for(int i=100000;i>0;i--)
	inv[i-1]=(inv[i]*i)%MOD;
	
	while(t--)
	{
		cin>>n>>m>>k;
		
		ll ans=0,res=1;
		
		for(int i=n;i>=k;i--)
		{	
			ll tmp=(fact[n]*inv[i])%MOD;
			tmp=(tmp*inv[n-i])%MOD;
			
			ans=(ans+tmp*res)%MOD;
			
			res=(res*(m-1))%MOD;
		}
		
		cout<<ans<<endl;
	}

}