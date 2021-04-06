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
const ll hell=1000000009;
const int INF = 1e12;
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

const int N=200005;
const int M=(1<<18)+5;
int bit[M+1];int dp[N+1];
int getparent(int i)
{
    return i- (i& -i);
}
int getnext(int i)
{
    return i+ (i& -i);
}
void update(int i,int v)
{
    while(i<=M)
    {
        bit[i]=(bit[i]+v)%hell;
        i=getnext(i);
    }
}
int getsum(int i)
{
    int ans=0;
    while(i>0)
    {
        ans=(ans+bit[i])%hell;
        i=getparent(i);
    }
    return ans;
}

int query(int l,int r)
{
    
    l++;r++;
    l=max(l,(int)1);
    if(l>r)
        return 0;
    int z=(getsum(r)-getsum(l-1)+hell)%hell;
    return z;
}


void solve()
{
    
    memset(bit,0,sizeof(bit));
    memset(dp,0,sizeof(dp));
    int n,m;
    cin>>n>>m;
    m=(1<<m);
    int a[n+1],pre[n+1];
    for(int i=1;i<=n;i++)
        cin>>a[i];
    pre[0]=0;
    for(int i=1;i<=n;i++)
    { pre[i]=pre[i-1]+a[i];
        pre[i]=pre[i]%m;
    }
    dp[1]=1;
    update(1,1);
    for(int i=2;i<=n+1;i++)
    {
        int x=pre[i-1];
        int z=query(x-m/2+1,x);
        dp[i]=z;
        dp[i]=(dp[i]+query(x+m/2+1,m-1))%hell;
        update(x+1,dp[i]);
    }
    cout<<dp[n+1]<<endl;
    
    
        
    
    
}
int32_t main()
{
    IOS;
    //pre();
    int t;
    t=1;
    cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
