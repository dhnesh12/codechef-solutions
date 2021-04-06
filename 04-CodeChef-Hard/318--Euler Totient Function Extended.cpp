#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;

#define fastio() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define test() int t;cin>>t;for(int test=1;test<=t;test++)
#define pb push_back
#define nl cout<<"\n"
#define F first
#define S second
#define all(x) x.begin(),x.end()

template<class C> void min_self( C &a, C b ){ a = min(a,b); }
template<class C> void max_self( C &a, C b ){ a = max(a,b); }

const ll MOD = 1000000007;
ll mod( ll n, ll m=MOD ){ n%=m;if(n<0)n+=m;return n; }

const int MAXN = 1e5+5;
const int LOGN = 21;
const ll INF = 1e14;
int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

template<class T1, class T2> void add( T1 &x, T2 y, ll m = MOD )
{
    x += y;
    if( x >= m )
        x -= m;
}

template<class T1, class T2> void sub( T1 &x, T2 y, ll m = MOD )
{
    x -= y;
    if( x < 0 )
        x += m;
}


template<class T> class Math
{
public:
    vector<T>fact,invfact;
    Math()
    {

    }
    Math( int n, T m = MOD )
    {
        fact.resize(n);
        invfact.resize(n);
        fact[0] = invfact[0] = 1;
        for(int i=1;i<n;i++)
        {
            fact[i] = mod( i * fact[i-1], m );
            invfact[i] = modinv( fact[i], m );
        }
    }
    T modinv( T x, T m = MOD )
    {
        return expo(x,m-2,m);
    }
    T expo( T base, T exp, T m = MOD )
    {
        T res = 1;
        while( exp )
        {
            if( exp&1 )
                res = mod( res*base, m );
            base = mod( base*base, m );
            exp >>= 1;
        }
        return res;
    }
    T choose( T n, T k, T m = MOD )
    {
        if( k < 0 || k > n ) return 0;
        T ans = fact[n];
        ans = mod( ans * invfact[n-k], m );
        ans = mod( ans * invfact[k], m );
        return ans;
    }
};

class Lagrange
{
public:
    ll SZ;
    int MODULO;
    Math<ll> m;
    Lagrange(int N, int md = MOD)
    {
        SZ = N;
        m = Math<ll>(SZ);
        MODULO = md;
    }
    ll interpolate( vector<ll> &y, ll x )
    {
        vector<ll> pref_prod(SZ), suff_prod(SZ);
        pref_prod[0] = mod(x,MODULO);
        suff_prod[SZ-1] = mod(x-SZ+1,MODULO);
        for(int i=1;i<SZ;i++)
        {
            pref_prod[i] = mod( pref_prod[i-1] * (x-i), MODULO );
            suff_prod[SZ-1-i] = mod( suff_prod[SZ-i] * (x-SZ+1+i) , MODULO );
        }

        ll ans = 0;
        for(int i=0;i<SZ;i++)
        {
            ll num = 1;
            if( i )
                num = mod( num * pref_prod[i-1], MODULO );
            if( i+1 < SZ )
                num = mod( num * suff_prod[i+1], MODULO );

            ll denom = mod( m.fact[i] * m.fact[SZ-1-i], MODULO );
            if( (SZ-1-i)%2 )
                denom = mod( -denom, MODULO );

            ll now = mod( num * m.modinv(denom, MODULO), MODULO );
            now = mod( now * y[i], MODULO );
            add( ans, now, MODULO );
        }
        return ans;
    }
};

ll dp[505][1005];

int main() 
{
    #ifdef gupta_samarth
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    fastio();

    auto factorize = [&]( ll n )
    {
        vector<array<ll,2>> ans;
        int cnt = 0;
        for(int x : {2,3,5})
        {
            cnt = 0;
            while( n % x == 0 )
            {
                n /= x;
                cnt++;
            }
            if( cnt )
                ans.pb({x,cnt});
        }
        static array<int, 8> increments = {4, 2, 4, 2, 4, 6, 2, 6};
        int i = 0;
        for(ll d=7;d*d<=n;d+=increments[i++])
        {
            cnt = 0;
            while( n % d == 0 )
            {
                cnt++;
                n /= d;
            }
            if( cnt )
                ans.pb({d,cnt});
            if( i == 8 )
                i = 0;
        }
        if( n > 1 )
            ans.pb({n,1});
        return ans;
    };

    Math<ll> m(1);

    test()
    {
        ll n,k;
        cin>>n>>k;

        vector<array<ll,2>> prime_fac = factorize(n);

        vector<ll> y(k+3);
        for(int i=1;i<k+3;i++)
        {
            y[i] = y[i-1];
            add( y[i], m.expo(i,k) );
        }
        Lagrange l(k+3);

        auto contribution = [&](ll d)
        {
            ll mu = 1;
            for( auto x : prime_fac )
            {
                ll p = x[0];
                ll cnt = 0, temp = d;
                while( temp % p == 0 )
                {
                    cnt++;
                    temp /= p;
                }
                if( cnt >= 2 )
                {
                    mu = 0;
                    break;
                }
                if( cnt )
                    mu *= -1;
            }

            ll now = m.expo(d,k);
            now = mod( now * mu );

            ll f = l.interpolate(y, n/d);
            now = mod( now * f );

            // cout<<"contribution for "<<d<<" "<<f,nl;
            return now;
        };

        ll ans = 0;
        for(ll d=1;d*d<=n;d++)
        {
            if( n % d == 0 )
            {
                add( ans, contribution(d) );
                if( d != n/d )
                    add( ans, contribution(n/d) );
            }
        }
        cout<<ans,nl;
    }


    // cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}
