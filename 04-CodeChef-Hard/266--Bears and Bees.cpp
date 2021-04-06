#pragma warning(disable:4996)
#pragma comment(linker, "/STACK:336777216")
#pragma GCC optimize("Ofast")

#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <functional>

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
#define int long long int
typedef complex<long double> cd;
const long double pi=acos(-1);
typedef double db;
typedef long double ldb;
typedef pair <int,int> pii;
typedef pair <db,db> pdd;
typedef vector<int> vi;
typedef vector<vector<int> > matrix;

#define m1 make_pair
#define pb push_back
#define flush fflush(stdout)
#define IOS std::ios::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
#define reset(x,v) memset(x,v,sizeof(x))

#define fi first
#define se second
#define endl "\n"
#define debug(x) (cerr << #x << ": " << x << "\n")
#define setbits(x) __builtin_popcount(x)
#define setbitsll(x) __builtin_popcountll(x)
#define all(x) x.begin(),x.end()
#define pii pair<int,int>

inline int gcd(int a,int b){if(a==0) return b;return gcd(b%a,a);}
inline int power(ll a,ll n,ll m){if(n==0)return 1;ll p=power(a,n/2,m);p=(p%m*p%m)%m;if(n%2) return (p%m*a%m)%m;else return p;}
const double EPS = 1e-9;
const ll MOD =998244353;
const ll hell=1000000007;
const int INF = 1e8;
const ll LL_INF = 0x3f3f3f3f3f3f3f3f;
template<typename T>
using ordered_set=tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>;

auto seed = chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937 rng(seed);

double startTime;
double getCurrentTime() {
    return ((double)clock() - startTime) / CLOCKS_PER_SEC;
}
const int dx[] = { -1, 0, 1, 0 };
const int dy[] = { 0, 1, 0, -1 };

const int N=1000005;

int dg[1005];
vi g[1005];

void solve()
{
    
    
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        dg[i]=0;
    }
    for(int i=1;i<=n;i++)
        g[i].clear();
    int u,v;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v;
        g[u].pb(i+1);
        g[v].pb(i+1);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<g[i].size();j++)
        {
            dg[g[i][j]]+=g[i].size()-1;
        }
    }
    int V=0,E=0;
    for(int i=1;i<=m;i++)
    {
        int sz=dg[i];
        V=V+(sz*(sz-1))/2;
    }
    for(int i=1;i<=m;i++)
        dg[i]--;
    for(int i=1;i<=n;i++)
    {
        int sz=g[i].size();int sm=0;
        for(int v:g[i])
        {
            int x=dg[v];
            E=E+x*x*(sz-1)-x*(sz-1);
            E=E+2*x*sm;
            sm+=x;
        }
        
    }
    E=E/2;
    cout<<V<<" "<<E<<endl;
    
    
}


int32_t main()
{
    IOS;
    int t;
    t=1;
    cin>>t;
    while(t--)
    {
        
        solve();
    }
    return 0;
}
