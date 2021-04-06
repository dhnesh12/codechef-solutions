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
//typedef vector<vector<int> > matrix;

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

const int N=100050;

int f[N+1];int inf[N+1];

int odd[N+1];int cnt[N+1];int pro1[N+1];int pro2[N+1];
vi qry[N+1];

void pre()
{
    f[0]=1;
    for(int i=1;i<=N;i++)
        f[i]=(f[i-1]*i)%hell;
    inf[N]=power(f[N],hell-2,hell);
    for(int i=N-1;i>=0;i--)
        inf[i]=(inf[i+1]*(i+1))%hell;
}

void solve()
{
    for(int i=0;i<=N;i++)
    { pro1[i]=1;
        pro2[i]=1;
    }
    int n;
    cin>>n;
    int a[n];
    for(int i=0;i<n;i++)
        cin>>a[i];
    int q;
    cin>>q;
    int s;
    for(int i=0;i<q;i++)
    {
        cin>>s;
        s=min(s,N-1);
        qry[s].pb(i);
    }
    for(int i=0;i<n;i++)
    {
        int x=a[i]-1;
        if(!x)
        {
            odd[1]+=1;
            cnt[1]+=1;
        }
        else
        {
            for(int l=1,r;l<=x;l=r+1)
            {
                 r=x/(x/l);
                int z=x/l;
                z++;
                cnt[l]+=z;
                cnt[r+1]-=z;
                if(z%2)
                {
                    odd[l]+=1;
                    odd[r+1]-=1;
                }
                pro1[l]=(pro1[l]*inf[z])%hell;
                pro1[r+1]=(pro1[r+1]*f[z])%hell;
                z=z/2;
                pro2[l]=(pro2[l]*inf[z])%hell;
                pro2[r+1]=(pro2[r+1]*f[z])%hell;
            }
            cnt[x+1]+=1;
            odd[x+1]+=1;
        }
    }
    for(int i=1;i<=N;i++)
    {
        cnt[i]+=cnt[i-1];
        odd[i]+=odd[i-1];
        pro1[i]=(pro1[i-1]*pro1[i])%hell;
        pro2[i]=(pro2[i-1]*pro2[i])%hell;
    }
    int inv2=power(2,hell-2,hell);int re[q];
    for(int i=1;i<N;i++)
    {
        if(qry[i].empty())
            continue;
        int tl=f[cnt[i]];
        tl=(tl*pro1[i])%hell;
        int ans=tl,palin;
        if(odd[i]<=1)
        {
             palin=f[cnt[i]/2];
            palin=(palin*pro2[i])%hell;
        }
        else
            palin=0;
        ans=(ans+palin)%hell;
        ans=(ans*inv2)%hell;
        for(int j:qry[i])
            re[j]=ans;
    }
    for(int i=0;i<q;i++)
        cout<<re[i]<<endl;
    
    
    
    
}


int32_t main()
{
    IOS;
   
    pre();
    int t;
    t=1;
    //cin>>t;
    while(t--)
    {
        
        solve();
    }
   
    return 0;
}
