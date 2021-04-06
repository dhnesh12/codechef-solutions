#include<bits/stdc++.h>
// #pragma optimize("-O3")
// #pragma GCC optimize("Ofast")
// #pragma GCC optimize("unroll-loops")
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,avx,mmx,tune=native")
using namespace std;
#define pb push_back
#define mp make_pair
#define ff first
#define ss second
#define INF 1e9
//#define BIG_INF 1e18
#define vi vector<ll>
#define sz(a) ll((a).size())
#define rep(i, begin, end) for (__typeof(end) i = (begin) - ((begin) > (end)); i != (end) - ((begin) > (end)); i += 1)
// #include <ext/pb_ds/assoc_container.hpp> // Common file
// #include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
// typedef tree<
// ll,
// null_type,
// less<ll>,
// rb_tree_tag,
// tree_order_statistics_node_update>
// ordered_set;
typedef long long ll;
const ll BIG_INF = 4e18;
const ll mod = 1e9 + 7;
 ll fast_exp(ll a, ll b)
{
    if(b <= 0)
       return 1;
    else
    {
       ll res = 1;
       res = fast_exp(a,b/2);
       res = (res*res)%mod;
       if(b%2 == 1)
          res = (res*a)%mod;
       return res;
 
    }
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
 
long long true_rand(long long n) {
    // Returns a random number between 0 and n - 1 inclusive using mt19937.
    uniform_int_distribution<long long> uid(0, n - 1);
    return uid(rng);
}



typedef long double ld;
const long long N = 5e3+1000;
const long double pi = acos(-1.0);
using cd = complex<double>;
const double PI = acos(-1);



ll distribute[600][600][11] = {};
ll dp[600][600][11] = {}; // {level upper, total, d}
ll fact[600] = {};
ll fac_inv[600] = {};
ll nCr[600][600] = {};
ll binom(int n, int r)
{
    if(r > n || r < 0)
        return 0;
    else
    {
        ll ans = fact[n];
        ans = (ans * fac_inv[n-r]) % mod;
        ans = (ans * fac_inv[r]) % mod;
        return ans;
    }
}
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    fact[0] = 1;
    fac_inv[0] = 1;
    for(ll i = 1; i < 600; i++)
    {    
        fact[i] = (i * fact[i-1]) % mod;
        fac_inv[i] = (fast_exp(i,mod-2) * fac_inv[i-1]) % mod;
    }
    for(int n = 0; n < 600; n++)
    {
        for(int r = 0; r <= n; r++)
            nCr[n][r] = binom(n,r);
    }

    for(int i = 1; i <= 10; i++)
        distribute[0][0][i] = 1;

    for(ll d = 2; d <= 10; d++)
    for(ll n = 1; n < 600; n++)
    {   
        for(ll k = 1; k < 600; k++)
        {
            for(ll i = d-1;  i <= n - (d-1) * (k-1); i++)
            {
                if(i >= 1)
                    distribute[n][k][d] = (distribute[n][k][d] + distribute[n - i][k-1][d] * nCr[n][i]) % mod;
            }
        }
    }

    for(ll i = 2; i < 600; i++)
       for(ll d = 1; d <= 10; d++)
       {
            if(i >= d)
                dp[i][i][d] = nCr[599][i];
          
       }


    for(ll d = 2; d <= 10; d++)
    {
        for(ll used = 1; used < 600; used++)
        {
            for(ll total = used; total < 600; total++)
            {
                for(ll extra = 0; extra + total + (d-1) * used < 600; extra++)
                {
                    //ll next_level = (d-1) * used + extra;
                    //ll next_total = total + extra + (d-1) * used;
                    //if(extra + (d-1) * used == 0)
                      // continue;
                    //ll ways_to_distribute = distribute[extra + (d-1) * used][used][d];
                    //ways_to_distribute = (ways_to_distribute * nCr[599 - total][extra + (d-1) * used]) % mod;
                    dp[(d-1) * used + extra][total + extra + (d-1) * used][d] = (dp[(d-1) * used + extra][total + extra + (d-1) * used][d] + ((nCr[599 - total][extra + (d-1) * used] * dp[used][total][d])%mod)*distribute[extra + (d-1) * used][used][d] )% mod;
                }
            }
        }
    }
    // for(int i = 0; i < 6; i++)
    // {
    //     for(int j = 0; j < 6; j++)
    //     {
    //         cout << "(" << i << "," << j << "):"<< dp[i][j][2] << "     ";
    //     }
    //     cout << '\n';
    // }
    ll t;
    cin >> t;
    int cs = 1;
    while(t--)
    {
        ll n, d;
        cin >> n >> d;
        ll ways = 0;
        for(ll level = 0; level <= n ; level++)
        {
            //cout << "level: "<< level << "  dp[level][n]: "<< dp[level][n][d] << "   d:"<< d << '\n'; 
            ways = (ways + dp[level][n][d]) % mod;
        }
        ll over_cnt = binom(599,n);
        ways = (ways * fast_exp(over_cnt,mod-2)) % mod;
        cout << "Case " << cs++ << ": " << ways << '\n';
    }
    //freopen("c.txt","r",stdin);
    
    // cerr<< '\n' << "Time elapsed :" << clock() * 1000.0 / CLOCKS_PER_SEC << " ms\n" ;
    return 0;
       
        
    
    
}










     