//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("O2")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimization ("unroll-loops")

#include <bits/stdc++.h>

#define         endl     "\n"
#define          EPS     1E-9
#define           PI     acos(-1)
#define        sq(x)     ((x)*(x))
#define           ln     length
#define            F     first
#define            S     second
#define           MP     make_pair
#define           MT     make_tuple
#define           PB     push_back
#define           PF     push_front
#define          PPB     pop_back
#define          PPF     pop_front
#define       ODD(x)     (((x)&1LL) ? (1):(0))
#define       all(v)     (v).begin(), (v).end()
#define    UNIQUE(v)     (v).erase(unique(all(v)), (v).end())
#define     f0(i, n)     for (i = (0); i <  (n); ++i)
#define     f1(i, n)     for (i = (1); i <= (n); ++i)
#define fab(i, a, b)     for (i = (a); i <= (b); ++i)
#define  fr(i, b, a)     for (i = (b); i >= (a); --i)

using namespace std;

/*
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
    tree_order_statistics_node_update> indexed_set;
//*/
typedef long long int     ll;
#define int               long int
typedef vector<ll>        vll;
typedef pair<ll, ll>      pll;
//typedef tuple<ll, ll, ll> tll;

inline    bool          compare(ll x, ll y)     { return x > y; }
template <typename T> T binaryExpo(T n, T p)    { if (p == 0) { return 1LL;   } if (p&1) { return  n*binaryExpo(n, p - 1);     } T ret = binaryExpo(n, p/2) ; return ret * ret;     }
template <typename T> T bigMod(T n, T p, T m)   { if (p == 0) { return 1LL%m; } if (p&1) { return (n%m*bigMod(n, p - 1, m))%m; } T ret = bigMod(n, p/2, m)%m; return (ret * ret)%m; }
template <typename T> T modInv(T n, T m)        { return bigMod(n, m - 2, m); }

const ll maxN = 2e5+10; const ll maxB =      320; const ll  INF =     9187201950435737471; const int  INF_I =  2139062143;
const ll maxA = 1e6+10; const ll MOD  =    1e9+7; const ll mINF =    -9187201950435737472; const int mINF_I = -2139062144;

//int dx[8] = { 0,   1,  1,  1,  0,  -1, -1, -1};
//int dy[8] = {-1,  -1,  0,  1,  1,   1,  0, -1};
//              N   NE   E  SE   S   SW   W   NW
//int dx[4] = { 0,       1,      0,      -1    };
//int dy[4] = {-1,       0,      1,       0    };
//int row, column;
bool FILE_PRINT = 0;

#define      mark(x)     (marked[(x)>>6] |= (1L<<(((x)%64)>>1)))
#define        on(x)     (marked[(x)>>6] &  (1L<<(((x)%64)>>1)))
int marked[//(maxA>>6) // only for odd numbers
    +2];
vector<ll>prime;

//* function prototypes
void sieve(ll n);
bool is_prime(ll num);
//*/

#ifndef ONLINE_JUDGE
#endif // ONLINE_JUDGE
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ###################################################################################################################
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//map<ll, string>res = {{0, "No"}, {1, "Yes"}};
//ll arr[maxN+10];
ll w[maxN];
set<ll>adj[maxN+10];
bool vis[maxN+10];

ll dfs(ll curr, ll parity)
{
    if (vis[curr] == 1) return 0;
    if (__builtin_parityll(w[curr]) != parity) return 0;
    vis[curr] = 1;
    ll ret = 1;
    for (ll ad : adj[curr])
    {
        ret += dfs(ad, parity);
    }
    return ret;
}

signed main()
{
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout.precision(15); cout << fixed;
#ifndef ONLINE_JUDGE
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout); FILE_PRINT = 1;
#endif // ONLINE_JUDGE

    //sieve(maxA);
    ll number_of_test_cases = 1, test_case;
    cin >> number_of_test_cases;
    for (test_case = 1; test_case <= number_of_test_cases; test_case++)
    {
    	ll i, j, k, l, m, n, query_type, q; ll a, b, c, x, y, z;

    	cin >> n >> m;
    	f1(i, n) cin >> w[i];
    	f1(i, n) adj[i].clear();
    	f0(i, m)
    	{
    	    cin >> a >> b;
    	    adj[a].insert(b);
    	    adj[b].insert(a);
    	}
#ifndef ONLINE_JUDGE
        if (test_case == 1 and not FILE_PRINT) cout << "################ OUTPUT ################\n";
#endif // ONLINE_JUDGE
    	//cout << "Case "  << test_case << ": ";

        //
        ll odd = 0, even = 0;
        memset(vis, 0, sizeof vis);
        f1(i, n) odd = max(odd, dfs(i, 1));
        memset(vis, 0, sizeof vis);
        f1(i, n) even = max(even, dfs(i, 0));

        cin >> q;
        f0(i, q)
        {
            cin >> query_type >> k;
            ll ans = -1;
            if (query_type == 1)
            {
                if (__builtin_parityll(k) == 1) ans = even;
                else ans = odd;
            }
            else
            {
                if (__builtin_parityll(k) == 1) ans = odd;
                else ans = even;
            }
            cout << ans << endl;
        }

    }
#ifndef ONLINE_JUDGE
    cerr << "\n........................   execution time : " << 1.0*clock()/CLOCKS_PER_SEC << " s";
#endif // ONLINE_JUDGE
    return 0;
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ###################################################################################################################
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~









bool is_prime(ll num) { return (num > 1 && (num == 2 || (ODD(num) && !on(num))) ); }
void sieve(ll n)
{
    ll i, j; mark(1);
    for (i = 3; i*i <= n; i += 2) { if (!on(i)) { for (j = i*i; j <= n; j += i+i) mark(j); } }
    prime.clear(); prime.push_back(2);
    for (i = 3; i <= n; i += 2) { if (is_prime(i)) prime.push_back(i); }
}

