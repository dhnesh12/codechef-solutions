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
const ll MOD=998244353;
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

const int N=100005;
vi s;int C[3][3];int dp[100][3];int ans[3];

void cal()
{
    
    int n=s.size();
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<s[i];j++)
        {
            
            int d=C[s[i]][j];
            for(int k=0;k<3;k++)
            {
                ans[(d*k)%3]=(ans[(d*k)%3]+dp[i][k])%hell;
            }
        }
    }
    ans[1]+=1;
    
    
    
}

void solve()
{
    int n;
    cin>>n;
    int x=n;
    s.clear();
    ans[0]=ans[1]=ans[2]=0;
    while(x>0)
    {
        s.pb(x%3);
        x=x/3;
    }
    reverse(s.begin(),s.end());
    int l=s.size();
    memset(dp,0,sizeof(dp));
    dp[0][1]=1;
    for(int i=1;i<l;i++)
    {
        int d=s[i-1];
        for(int j=0;j<3;j++)
        {
            for(int k=0;k<3;k++)
                dp[i][(C[d][j]*k)%3]=(dp[i][(C[d][j]*k)%3]+dp[i-1][k])%hell;
        }
    }
    cal();
    int re=(ans[1]+2*ans[2])%hell;
    cout<<re<<endl;
}



int32_t main()
{
    IOS;
    C[0][0]=1;C[1][0]=1;C[1][1]=1;C[2][0]=1;C[2][1]=2;C[2][2]=1;
    int t;
    t=1;
    cin>>t;
    while(t--)
    {
        
        solve();
    }
    return 0;
}
