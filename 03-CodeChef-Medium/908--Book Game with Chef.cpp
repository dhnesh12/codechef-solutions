#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")
#define fio ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define inf 1e18+5
#define mod 1000000007
#define MAXN 100005
#define ll long long
#define pb push_back
#define sortv(v) sort(v.begin(),v.end())
#define tc(t) int t;cin>>t;while(t--)
#define copy copy_n
#define fr(i,a,b) for(long long i=a;i<b;i++)
#define frr(i,a,b) for(long long i=a;i>=b;i--)
#define frn(i,a,b,n) for(long long i=a;i<=b;i=i+n)
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) (x*y)/gcd(x,y)
#define ld long double
#define um unordered_map
#define mkp make_pair
#define b_s binary_search
#define nob __builtin_popcount
#define des greater<ll>()
#define fi first
#define se second
ll mul(ll a, ll b, ll p = mod) {return ((a % p) * (b % p)) % p;}
ll add(ll a, ll b, ll p = mod) {return (a % p + b % p) % p;}
void input(ll a[], ll sz) {fr(i, 0, sz) cin >> a[i];}
void print(ll a[], ll sz) {fr(i, 0, sz) {if (i == sz - 1) cout << a[i] << "\n"; else cout << a[i] << " ";}}
ll maxr(ll a[], ll sz) {ll ma; fr(i, 0, sz) {if (i == 0) ma = a[i]; else if (a[i] > ma) ma = a[i];} return ma;}
ll minr(ll a[], ll sz) {ll mi; fr(i, 0, sz) {if (i == 0) mi = a[i]; else if (a[i] < mi) mi = a[i];} return mi;}
ll isprm(ll n) {
    if (n <= 1)  return 0;
    if (n <= 3)  return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}
/*ll spf[MAXN];
void sieve()
{
    spf[1]=1;
    for (ll i=2; i<MAXN; i++)
        spf[i] = i;
    for (ll i=4; i<MAXN; i+=2)
        spf[i] = 2;

    for(ll i=3;i*i<MAXN;i+=2)
    {
        if (spf[i]==i)
        {
            for (int j=i*i;j<MAXN;j+=i)
                if (spf[j]==j)
                    spf[j]=i;
        }
    }
}*/
ll power(ll x, ll y, ll p = mod)
{
    ll res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1; // y = y/2
        x = (x * x) % p;
    }
    return res;
}
ll modInverse(ll n, ll p = mod)
{
    return power(n, p - 2, p);
}
/*ll fac[MAXN];
ll inv[MAXN];
void fact(ll p=mod)
{
    fac[0] = 1;
    for (ll i = 1 ; i < MAXN; i++)
        fac[i] = fac[i - 1] * i % p;
    for(ll i=0;i<MAXN;i++)
    inv[i]=modInverse(fac[i]);
}
ll ncrMod(ll n, ll r, ll p = mod)
{
    if (r == 0)
        return 1;
    return (fac[n] * inv[r] % p *
            inv[n-r] % p) % p;
}*/
//a+b=xor(a,b)+2*(a&b)//
struct comp
{
    bool operator()(const pair<ll, ll> &a,
                    const pair<ll, ll> &b)const
    {
        if (a.fi == b.fi)
        {
            return (a.se > b.se); //second elem in descending
        }
        return (a.first < b.first);//first elem in ascending
    }
};

ll ln,a[20],dp[20][5][5][2];

ll solve(ll i,ll f,ll k,ll y,ll z)
{
    // cout<<i<<" "<<f<<" "<<k<<" "<<y<<"\n";
    if(i>ln)
    return k;
    if(dp[i][f][k][z]!=-1)
    return dp[i][f][k][z];
    ll x=0;
    fr(j,0,10)
    {
        ll h=0,g=0,h2=0;
        if(j>0)
        h2=1;
        if(j==y && y!=0)
        h=1;
        if(y==0 && j==y && z==1)
        h=1;
        if(f==1 && j==a[i])
        g=1;
        if((f==1 && j<=a[i]) || f==0)
        x+=solve(i+1,g,k|h,y,z|h2);
    }
    dp[i][f][k][z]=x;
    return dp[i][f][k][z];
}




int main()
{
    fio;
    tc(t)
    {
        ll n;
        cin>>n;
        ll q=n*10,p=0;
        string s=to_string(n);
        ln=s.length();
        fr(i,0,ln)
        {
            a[i+1]=(ll)s[i]-'0';
        }
        fr(i,0,10)
        {
            memset(dp,-1,sizeof(dp));
            p+=solve(1,1,0,i,0);
            // cout<<i<<" "<<p<<"\n";
        }
        
        // cout<<"pq=="<<p<<" "<<q<<"\n";
        ll g=gcd(p,q);
        p/=g;
        q/=g;
        cout<<p<<"/"<<q<<"\n";
    }
    return 0;
}
