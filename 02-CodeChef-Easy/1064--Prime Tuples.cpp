#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const ll inf = 1e15;
const ll mod = 1000000007;
vector<vector<ll>>adj;
//map<ll, vector<ll>>adj;
vector<ll>prime;
void sieve()

{

  prime.resize(10000001,1);

  prime[0]=0;

  for(ll i=2;i<=10000000;i++)

  if(prime[i])

  for(ll j=i*i;j<=10000000;j+=i)

  prime[j]=0;

}
vector<ll>ans(1000006,0);
void solve()
{
	ll n;
	cin>>n;
	/*for(int i=0; i<20; i++)
	    cout<<ans[i]<<" ";*/
	cout<<ans[n]<<"\n";
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
    ll ignore = 1;
    sieve();
    cin>>ignore;
    for(int i=4; i<=1000005; i++)
	{
	    if(prime[i-2] == 1 && prime[i] == 1)
	        ans[i] = ans[i-1]  +1;
	    else
	        ans[i] = ans[i-1];
	}
   
    while(ignore--)
    {
    	solve();
    	
	}
}