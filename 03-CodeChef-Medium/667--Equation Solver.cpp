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

const int N=2000005;
bool p[N+1];int f[N+1];int u[N+1];
void pre()
{
    for(int i=1;i<=N;i++)
    {
        f[i]=1;
        u[i]=1;
    }
    for(int i=2;i<=N;i++)
        if(!p[i])
        {
            for(int j=i;j<=N;j+=i)
            {
                f[j]*=2;
                p[j]=1;
                u[j]= -u[j];
                if(!(j%(i*i)))
                    u[j]=0;
            }
        }
}
int coprimepairs(int n)
{
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        int z=n/i;
        z=z*z;
        ans=ans+z*u[i];
    }
    return ans;
    
}

void solve()
{
 
    int a,b,c;
    cin>>a>>b>>c;
    int ans=0;
    for(int g=1;g<=N;g++)
    {
        int z=c*g+a;
        int y=g-b;
        if(y==0)
        {
            if(!z)
            {
                cout<<-1<<endl;
                return;
            }
            continue;
        }
        if(!(z%(abs(y))))
        {
            z=z/y;
            if(z>0&&(!(z%g)))
            {
                z=z/g;
                ans=ans+f[z];
            }
        }
    }
    cout<<ans<<endl;
    
    
    
}


int32_t main()
{
    IOS;
    pre();
    int t;
    t=1;
    cin>>t;
    while(t--)
    {
        
        solve();
    }
    return 0;
}




