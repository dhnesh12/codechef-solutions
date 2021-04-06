#include<iostream>
#include<bits/stdc++.h>
#define REP(i,n) for (int i = 1; i <= n; i++)
#define fastio ios_base::sync_with_stdio(false);cin.tie(NULL)
#define fo(i,n) for(int i = 0;i < n;i++)
#define pb push_back
#define ff first
#define ss second
#define ii pair<int,int>
#define vi vector<int>
#define vii vector<ii>
#define vl vector<ll>
#define vll vector<pair<ll,ll>>
#define ll long long int
#define INF 1000000000
#define endl '\n'
const double PI = 3.141592653589793238460;
#define debug1(x) cerr << #x << " = " << x << '\n';
#define debug2(x, y) cout << #x << " = " << x << "   " << #y << " = " << y << "\n";
#define debug3(x, y,z) cout << #x << " = " << x << "   " << #y << " = " << y << " "<<#z<<" = "<<z<<"\n";
#define debugarray(arr,n) { cout << "[" ; for(ll i=0;i<n;i++) cout<<arr[i]<<" "; cout<<"] , \n";}
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;
 int mod = 1e9 + 7;
using namespace std;

ll power(ll x, ll y, ll p)
{
    ll res = 1;
    while(y > 0)
    {
        if(y&1) res = res*x % p;
        x = (x*x) % p;
        y >>= 1;
    }
    return res;
}

unsigned long long modInverse(unsigned long long n,  
                                            int p)
{
    return power(n, p - 2, p);
}
 
// Returns nCr % p using Fermat's little
// theorem.
unsigned long long ncr(unsigned long long n,
                                 int r, int p)
{
    // If n<r, then nCr should return 0
    if (n < r)
        return 0;
    // Base case
    if (r == 0)
        return 1;
 
    // Fill factorial array so that we
    // can find all factorial of r, n
    // and n-r
    unsigned long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;
 
    return (fac[n] * modInverse(fac[r], p) % p
            * modInverse(fac[n - r], p) % p)
           % p;
}

int main()
{
    fastio;

    ll n,k; cin >> n >> k;
    while(n != 0)
    {
        ll res = (2LL*  (ncr(n-2, ceil((float)(k+1) / 2) -1,mod) % mod) * (ncr(n-2, floor((k+1)/2) - 1,mod) % mod )) % mod ;
        cout << res << endl;



        cin >> n >> k;
    }
}