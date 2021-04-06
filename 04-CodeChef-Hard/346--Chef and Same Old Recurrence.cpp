#include <bits/stdc++.h>
using namespace std;
#define ll long long
const ll N = 10000005;
ll mod = (ll)(1e9 + 7);
ll n,k,a,b,apow[N],bkpow[N],modinverse[N];
ll twon[2*N];

ll power(ll a, ll m)
{
    ll m0 = m;
    ll y = 0, x = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1)
    {
        // q is quotient
        ll q = a / m;
        ll t = m;
 
        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
        t = y;
 
        // Update y and x
        y = x - q * y;
        x = t;
    }
 
    // Make x positive
    if (x < 0)
       x += m0;
 
    return x;
}
 
void twonfun()
{
     twon[0]=1;
     for(ll i=1;i<(2*N);i++)
        twon[i] = (twon[i-1]*i)%mod;
}
 
void afun()
{
     apow[0]=1;
         
     for(ll i=1;i<N;i++)
         apow[i] = (apow[i-1]*a)%mod;
     
}
 
void bkfun()
{
     ll p = (b*k)%mod;
     bkpow[0]=1;
     for(ll i=1;i<N;i++)
        bkpow[i] = (bkpow[i-1]*p)%mod;
     
}
 
void modinversefun()
{
    modinverse[N-1] = power(twon[N-1],mod)%mod;
    
    for(ll i = N - 2;i>=0;i--)
        modinverse[i] = (modinverse[i+1]*(i+1))%mod;
}
 
 
int main()
{
    ios_base::sync_with_stdio(0);
	cin.tie(NULL);
	cout.tie(NULL);
	scanf("%lld%lld%lld%lld",&n,&k,&a,&b);
  
     
    twonfun();
    afun();
    bkfun();
    modinversefun();
    ll ans=0;
    ll p = (b*k)%mod;
    for(ll i=0;i<n;i++)
    {
        
        ll above = (((twon[n-1+i]*apow[n-1-i])%mod)*bkpow[i])%mod;
        ll below = (((modinverse[n-1-i]*modinverse[i+1])%mod)*modinverse[i])%mod;
        
        ans +=  (above*below)%mod;
        ans%=mod;
        
    }
    
    ans=(ans*k)%mod;
    printf("%lld",ans);
} 