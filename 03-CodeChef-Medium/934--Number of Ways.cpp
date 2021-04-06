#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define M 1000000007
ll f[2000005];
void fact(){
    f[0]=1;
    f[1]=1;
    for(ll i=2;i<=2000004;i++){
        f[i]=(f[i-1]*i)%M;
    }
}
ll power(ll x, ll y, ll p)
{
    ll res = 1;
    x = x % p; 
    while (y > 0) 
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
long long modInverse(ll n)
{
    return power(n, M-2, M);
}
ll nCrM(ll n, ll r)
{
    if (n < r)
        return 0;
    if (r == 0 or r == n)
        return 1;
    return (f[n] * ((modInverse(f[r]) * modInverse(f[n - r]))%M) ) % M;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    fact();
    ll t;
    cin >> t;
    while(t--){
        ll n,k;
        cin >> n >> k;
        ll x = 0;
        for(ll i=1;i<n;i++){
            ll add = ((nCrM(k+i,i)*2ll)%M*(n-i))%M;
            x = (x+add)%M;
        }
        x = (x+n)%M;
        cout << x << "\n";
    }
    return 0;
}

