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
typedef pair <int, int> pii;
typedef pair <db, db> pdd;
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

inline ll gcd(ll a,ll b){if(a==0) return b;return gcd(b%a,a);}
inline ll power(ll a,ll n,ll m){if(n==0)return 1;ll p=power(a,n/2,m);p=(p%m*p%m)%m;if(n%2) return (p%m*a%m)%m;else return p;}
const double EPS = 1e-9;
const ll MOD =998244353;
const ll hell=1000000007;
const int INF = 1e16;
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

const int N=105;

int dp[N][N];int mod;int C[105][105];


int fun(int n,int k)
{
    if(k>n)
        return 0;
    else if(n==k)
    {
        return dp[n][k]=1;
    }
    else if(dp[n][k]!= -1)
        return dp[n][k];
    if(k==1)
    {
        dp[n][k]=power(2,(n*(n-1))/2,mod);
        for(int i=2;i<=n;i++)
            dp[n][k]=(dp[n][k]-fun(n,i)+mod)%mod;
        return dp[n][k];
        
    }
    dp[n][k]=0;
    for(int last=1;last<n;last++)
    {
       int z= (fun(n-last,k-1)*fun(last,1))%mod;
        z=(z*C[n-1][last-1])%mod;
        dp[n][k]=(dp[n][k]+z)%mod;
    }
    return dp[n][k];
    
}


void solve()
{
    int n,k;
    cin>>n>>k>>mod;
    memset(dp,-1,sizeof(dp));
    memset(C,0,sizeof(C));
    C[0][0]=1;
    for(int i=1;i<N;i++)
    {
        for(int j=0;j<=i;j++)
        {
          if(j==0)
              C[i][j]=1;
            else
                C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
        }
    }
    
    
    int z=fun(n,k);
    if(k==1)
    {
        z--;
        if(z<0)
            z+=mod;
    }
    cout<<z<<endl;
    
}

int32_t main()
{
    IOS;
    //FILE *fin = freopen("in","r",stdin);
    //FILE *fout = freopen("out","w",stdout);
    int t;
    t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}