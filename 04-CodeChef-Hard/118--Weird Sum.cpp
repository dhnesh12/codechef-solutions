#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
map<int,int>mtp;
const ll mod=998244353;
ll ans[10000999];
inline ll power(ll x,ll y)
{
    ll temp;
    if( y == 0)
        return 1;
    temp = power(x, y/2);
    if (y%2 == 0)
        return ((temp%mod)*(temp%mod))%mod;
    else
        return ((x%mod)*(temp%mod)*(temp%mod))%mod;
}
inline void fact(ll n)
{
	mtp.clear();
    while (n%2 == 0)
    {
        mtp[2]++;
        n = n/2;
    }
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        while (n%i == 0)
        {
            mtp[i]++;
            n = n/i;
        }
    }
    if (n > 2)
        mtp[n]++;
}
int mark[10000009];
void pre()
{
	for(ll i=2;i<sqrt(10000000);i++)
	{
		for(ll j=i*i;j<10000000;j=j*i)
		{
			if(mark[j]==0)
				mark[j]=i;
			//cout<<j<<" ";
		}
		//cout<<endl;
	}
    for(ll n=2;n<10000009;n++)
    {
    	if(mark[n]!=0)
    	{
    			ans[n]=(ans[n-1]+mark[n])%mod;
    	}
    	else
    	{
    		ans[n]=(ans[n-1]+n)%mod;
    	}
    }
}
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
    pre();
	int t;
	cin>>t;
	while(t--)
	{
		ll n;
		cin>>n;
		cout<<ans[n]<<endl;
	}
	return 0;
}
