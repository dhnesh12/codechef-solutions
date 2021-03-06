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
const int INF = 1e17;
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

const int N=2005;

vector<pair<int,int>> adj[N];bool visited[N];
int d[N][N];int D[N][N];

void dijastra(int u)
{
    d[u][u]=0;
    set<pair<int,int>> s;
    s.insert(m1(d[u][u],u));
    pair<int,int> pr;
    while(!s.empty())
    {
        pr=(*s.begin());
        s.erase(s.begin());
        int U=pr.se;
        for(int i=0;i<adj[U].size();i++)
        {
            int v=adj[U][i].fi;int w=adj[U][i].se;
            if(d[u][v]>(d[u][U]+w))
            {
                if(s.find(m1(d[u][v],v))!=s.end())
                    s.erase(s.find(m1(d[u][v],v)));
                d[u][v]=d[u][U]+w;
                s.insert(m1(d[u][v],v));
            }
        }
        
    }
}
void falsedijastra(int u)
{
    D[u][u]=0;
    set<pair<int,int>> s;
    s.insert(m1(D[u][u],u));
    pair<int,int> pr;
    memset(visited,0,sizeof(visited));
    
    while(!s.empty())
    {
        pr=(*s.begin());
        visited[pr.se]=1;
        s.erase(s.begin());
        int U=pr.se;int mn=INF;
        for(int i=0;i<adj[U].size();i++)
        {
          if(!visited[adj[U][i].fi])
            mn=min(mn,adj[U][i].se);
        }
        for(int i=0;i<adj[U].size();i++)
        {
            if(adj[U][i].se==mn&&(!visited[adj[U][i].fi]))
            {
                int v=adj[U][i].fi;int w=adj[U][i].se;
                if(D[u][v]>(D[u][U]+w))
                {
                    if(s.find(m1(D[u][v],v))!=s.end())
                        s.erase(s.find(m1(D[u][v],v)));
                    D[u][v]=D[u][U]+w;
                    s.insert(m1(D[u][v],v));
                }
            }
        }
    }
    
}

void solve()
{
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        { d[i][j]=INF;
            D[i][j]=INF;
        }
    int u,v,w;
    for(int i=0;i<m;i++)
    {
        cin>>u>>v>>w;
        adj[u].pb(m1(v,w));
    }
    for(int i=1;i<=n;i++)
        dijastra(i);
    for(int i=1;i<=n;i++)
        falsedijastra(i);
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(d[i][j]==D[i][j])
                ans++;
        }
    cout<<ans<<endl;
    
    
    
}

int32_t main()
{
    IOS;
    //FILE *fin = freopen("in","r",stdin);
    //FILE *fout = freopen("out","w",stdout);
    
    int t;
    t=1;
    // cin>>t;
    while(t--)
    {
        solve();
    }
    return 0;
}
