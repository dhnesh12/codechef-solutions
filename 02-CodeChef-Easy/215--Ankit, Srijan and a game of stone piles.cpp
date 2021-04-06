#include<bits/stdc++.h>
#define pb push_back 
#define ff first
#define ss second
#define MOD 1000000007
#define ll long long int
#define P pair<ll,ll>
 
using namespace std;
 
 
ll add(ll x,ll y)
{
    x += y;
    while(x >= MOD) x -= MOD;
    while(x < 0) x += MOD;
    return x;
}
 
ll mul(ll x,ll y)
{
    return (x * 1ll * y) % MOD;
}
 
ll binpow(ll x,ll y)
{
    ll z = 1;
    while(y)
    {
        if(y & 1) z = mul(z,x);
        x = mul(x,x);
        y >>= 1;
    }
    return z;
}
 
ll inv(ll x)
{
    return binpow(x, MOD - 2);
}
 

ll divide(ll x,ll y)
{
    return mul(x, inv(y));
}

ll fact[100007];

map<ll,ll> mm;


int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(NULL);
   
    
    int t;
    cin>>t;

    
    fact[0]=1;
    for(ll i=1;i<=100000;i++)
    	fact[i]=mul(fact[i-1],i);

    
    while(t--)
    {

    	  mm.clear();
          ll n,m=0;
          cin>>n;

         
          for(int i=0;i<n;i++)
          {
          	 ll y;
          	 cin>>y;
          	 mm[y]++;
          	 if(y==1)
          	 	m++;
          }

          if(n==mm[1])
          {
               if(n%2)
                    cout<<1<<"\n";
               else
                    cout<<0<<"\n";
               continue;
          }
 


          ll K=1;
          for(auto it=mm.begin();it!=mm.end();it++)
          	  if(it->first!=1)
          	  	K=mul(K,fact[it->second]);

          ll ans=0;
          
          
          for(ll r=0;r<=m;r++)
          {
          	 ll a=divide(fact[n-r],mul(fact[m-r],K));
             if(r%2==0)
          	 ans=add(ans,a);
          	 else
          	 ans=add(ans,-a);
          }

          cout<<ans<<"\n";
    }

    return 0;
}
