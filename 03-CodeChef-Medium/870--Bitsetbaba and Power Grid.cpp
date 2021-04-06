//   Author: ABHINASH GIRI
//#pragma GCC target ("avx2")
//#pragma GCC optimization ("O3")
//#pragma GCC optimization ("unroll-loops")
//#pragma GCC target ("sse4")
#include "bits/stdc++.h"
using namespace std;
#define fast ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr)
#define PI (2*acos(0.0))
#define sz(x)           ( (ll) (x).size())
#define setbits(x)      __builtin_popcountll(x)
#define zrobits(x)      __builtin_ctzll(x)
#define pos_rt_stbt(x)   (__builtin_ffsll(x))   // return position of rightmost set bit ( 1 indexing ) pos_rt_stbt(10) = 2 ( 1010 )
#define ps(x,y)         fixed<<setprecision(y)<<x
#define w(t)            int t; cin>>t; while(t--)
#define nl "\n"
#define yes cout<<"YES\n"
#define no cout<<"NO\n"
#define all(v) (v).begin(),(v).end()
#define clr(v) memset(v,0,sizeof(v));
#define sqr(x) ((x) * (x))
typedef long long int ll;
typedef vector<int> vi;
typedef vector<long long int> vll;
typedef vector<vll> vvll;
typedef vector<string> vs;
typedef pair<ll, ll> pll;
typedef vector<pair<ll, ll>> vpll;
const long long int inf = 1e18;
const long long int mod = 1e9 + 7;
const long long int MOD =  998244353;
//----------------------------------------------------------------------------------------------------------------------
// Debug
#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; }; sim > rge<c> range(c i, c j) { return rge<c> {i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0); sim > char dud(...);
struct debug {
#ifdef ABHI
    eni( != ) cerr << boolalpha << i; ris;
    }
    eni( == ) ris << range(begin(i), end(i));
    }
    sim, class b dor(pair < b, c > d) {ris << "(" << d.first << ", " << d.second << ")";}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstring-plus-int"
    sim dor(rge<c> d) {*this << "["; for (auto it = d.b; it != d.e; ++it) *this << ", " + 2 * (it == d.b) << *it; ris << "]";}
#pragma clang diagnostic pop
#else
    sim dor(const c&) { ris; }
#endif
};
vector<char*> tokenizer(const char* args) {
    char *token = new char[111]; strcpy(token, args); token = strtok(token, ", ");
    vector<char*> v({token});
    while ((token = strtok(NULL, ", "))) v.push_back(token);
    return reverse(v.begin(), v.end()), v;
}
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-parameter"
void debugg(vector<char*> args) { cerr << "\b\b "; }
#pragma clang diagnostic pop
template <typename Head, typename... Tail>
void debugg(vector<char*> args, Head H, Tail... T) {
    debug() << " [" << args.back() << ": " << H << "] ";
    args.pop_back(); debugg(args, T...);
}
#define harg(...) #__VA_ARGS__
#ifdef ABHI
#define deb(...) { debugg(tokenizer(harg(__VA_ARGS__, \b\t-->Line)), __VA_ARGS__, __LINE__); cerr << endl;}
#else
#define deb(...) { }
#endif
/// --------------------------------------------------------------------------------------------------------------------

#define ptvs(v) for(auto &item :v) cout<<item<<" ";cout<<"\n";
#define pt(x) cout<<((x))<<"\n";
#define pt2(x,y) cout<<(x)<<" "<<(y)<<"\n";
#define cinvll(v,start,end) vll v(end+1);for(auto i=start;i<=end;i++) {cin>>v[i];}
//***********************************************************************************************
// Fast Exponentiation power(a,b) ==> a to the power b
template <typename T>
T  power(T  a, T  b) {
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    else {
        T  res = (power(a, b / 2));
        if (b % 2)
        {
            return (res * res * a);
        }
        else
        {return res * res;}
    }
}

// Fast Modular Exponentiation  power(a,b,m) ==> (a to the power b) modulo m
template <typename T>
T  power(T  a, T  b, T modulo)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    else {
        T  res = (power(a, b / 2, modulo) % modulo);
        if (b % 2)
        {
            return ((((res % modulo) * (res % modulo)) % modulo) * (a % modulo)) % modulo;
        }
        else
        {return ((res % modulo) * (res % modulo)) % modulo;}
    }
}
// G C D
template <typename T>
T  gcd(T  a, T  b) {
    if (b == 0)
    {return a;}
    return gcd(b, a % b);
}

inline ll ceil(ll a, ll b) {    return a / b + (a % b == 0 ? 0 : 1);  }

void factorial(vll &fact, ll n)
{
    fact.resize(n + 1, 1);
    fact[0] = 1;
    fact[1] = 1;
    for (int i = 2; i <= n ; ++i)
    {
        fact[i] = ((fact[i - 1] % mod) * (i % mod)) % mod;
        //cout<<" fact "<<i<<" "<<fact[i]<<nl;
    }
}

ll mod_inv(ll a) {    return (power<ll>(a, mod - 2, mod)) % mod;    }
ll ncr(ll n, ll r, vll &fact)
{
    if (r > n or n < 0 or r < 0) return 0LL;
    return  (((fact[n] % mod) * (mod_inv(fact[n - r]) % mod)) % mod * (mod_inv(fact[r]) % mod)) % mod;
}
ll NCR(ll n, ll r, vll &fact, vll &inv)
{
    if (r > n or n < 0 or r < 0) return 0LL;
    return  (((fact[n] % mod) * (inv[n - r]) )) % mod * (inv[r]) % mod;
}
void modI(vll &inv, ll n, vll &fact)
{
    inv.resize(n + 1, 1);
    inv[n] = mod_inv(fact[n]);
    for (int i = n - 1; i >= 0 ; --i)
    {
        inv[i] = ((inv[i + 1]) % mod * ((i + 1)  % mod)) % mod;
    }
}


int main()
{
    fast;
    w(t)
    {
        ll m,k;
        cin>>k>>m;
        cinvll(v,0,m-1);
        vll basis={};
        for (int i = 0; i <m ; ++i)
        {
            ll x=v[i];
            for(auto curr:basis)
            {
                x=min(x,x^curr);
            }
            if(x)basis.push_back(x);
        }
        ll d = (1ll<<k)/(1ll<<sz(basis));
        pt(d);


    }



    return 0;
}









