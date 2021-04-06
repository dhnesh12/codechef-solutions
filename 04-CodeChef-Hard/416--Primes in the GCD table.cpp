
/*
 Linear Sieve + drichlet + harmonic jumping
 
 
 */

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
const int INF = 1e18;
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

const int N = 1e6+5;
#define MAXN 10000005
int mark[MAXN+1],prime[MAXN+1],sz;
int u[MAXN+1];map<int,int>mp;


void linearsieve()
{
    u[1]=1;
    for(int i=2;i<=MAXN;i++)
    {
        if(!mark[i])
        {
            u[i]= -1;
            prime[sz++]=i;
        }
        for(int j=0;j<sz && (prime[j]*i)<=MAXN ;j++)
        {
            mark[i*prime[j]]=1;
            if(!(i%prime[j]))
            {
                u[i*prime[j]]=0;
                break;
            }
            u[i*prime[j]]= -u[i];
        }
        
    }
    for(int i=2;i<=MAXN;i++)
    {
        mark[i]=(!mark[i]);
        mark[i]+=(mark[i-1]);
        u[i]+=u[i-1];
    }
    
}
int f(int n)
{
    if(n<=MAXN)
        return u[n];
    if(mp.find(n)!=mp.end())
        return mp[n];
    int ans=1;
    for(int l=2,r;l<=n;l=r+1)
    {
        r=n/(n/l);
        ans=ans-(r-l+1)*f(n/l);
    }
    return mp[n]=ans;
}

int g(int n,int m)
{
    int ans=0,r1,r2;
    for(int l=1,r;l<=n;l=r+1)
    {
        r1=n/(n/l);
        r2=m/(m/l);
        r=min(r1,r2);
        ans=ans+(f(r)-f(l-1))*(n/l)*(m/l);
    }
    return ans;

}

void solve()
{
    int n,m;
    cin>>n>>m;
    if(n>m)
        swap(n,m);
    int ans=0,r1,r2;
    for(int l=1,r;l<=n;l=r+1)
    {
        r1=n/(n/l);
        r2=m/(m/l);
        r=min(r1,r2);
        ans=ans+(mark[r]-mark[l-1])*g(n/l,m/l);
    }
    cout<<ans<<endl;
    
    
}




int32_t main()
{
    IOS;
    
    linearsieve();
    startTime=clock();
    int t;
    t=1;
     cin>>t;
    while(t--)
    {
        solve();
    }
    //cout<<getCurrentTime()<<endl;
    return 0;
}

