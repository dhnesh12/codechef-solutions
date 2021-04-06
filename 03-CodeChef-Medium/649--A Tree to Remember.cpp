

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

const int N=100005;
vi adj[N+1];int a[N+1];
int Time,tin[N+1],tout[N+1],up[N+1][21],sm[N+1][21],h[N+1];
int ans;int c[N+1];set<int> color[N+1];
set<int> s[N+1];

void dfs(int u,int p)
{
    
    tin[u]=Time++;
    up[u][0]=p;
    sm[u][0]=a[u];
    color[u].insert(c[u]);
    s[c[u]].insert(tin[u]);
    for(int i=1;i<=20;i++)
    {
        up[u][i]=up[up[u][i-1]][i-1];
        sm[u][i]=sm[u][i-1]+sm[up[u][i-1]][i-1];
    }
    for(int v:adj[u])
    {
        if(v!=p)
        {
            h[v]=1+h[u];
            dfs(v,u);
            if(color[u].size()<color[v].size())
                swap(color[u],color[v]);
            for(auto it=color[v].begin();it!=color[v].end();it++)
                color[u].insert((*it));
            color[v].clear();
            
        }
    }
    ans=ans+a[u]*color[u].size();
    tout[u]=Time-1;
}
bool is_ancestor(int u,int v)
{
    return tin[u]<=tin[v]&&tout[u]>=tout[v];
}
int pth(int u,int k)
{
    
    for(int i=20;i>=0;i--)
        if(k>=(1<<i))
        {
            k-=(1<<i);
            u=up[u][i];
        }
    return u;
}
int getsum(int u,int k)
{
    
    int sum=0;
    for(int i=20;i>=0;i--)
    {
        if(k>=(1<<i))
        {
            k-=(1<<i);
            sum+=sm[u][i];
            u=up[u][i];
        }
    }
    return sum;
    
    
}
void add(int u)
{
    
    int C=c[u];
    //s[C].insert(tin[u]);
    int l=0,r=h[u],mid,opt= -1;
    while(r>=l)
    {
        mid=(l+r)/2;
        int lc=pth(u,mid);
        auto it=s[C].lower_bound(tin[lc]);
        if(it==s[C].end())
        {
            l=mid+1;
        }
        else
        {
            int T=(*it);
            if(T>=tin[lc]&&T<=tout[lc])
            {
                opt=lc;
                r=mid-1;
            }
            else
                l=mid+1;
            
        }
        
    }
    if(opt== -1)
    {
        ans=ans+getsum(u,h[u]+1);
    }
    else
        ans=ans+getsum(u,h[u]-h[opt]);
    s[C].insert(tin[u]);
    //cout<<opt<<endl;
}
void remove(int u)
{
    int C=c[u];
    s[C].erase(s[C].find(tin[u]));
    int l=0,r=h[u],mid,opt= -1;
    while(r>=l)
    {
        mid=(l+r)/2;
        int lc=pth(u,mid);
        auto it=s[C].lower_bound(tin[lc]);
        if(it==s[C].end())
        {
            l=mid+1;
        }
        else
        {
            int T=(*it);
            if(T>=tin[lc]&&T<=tout[lc])
            {
                opt=lc;
                r=mid-1;
            }
            else
                l=mid+1;
                
        }
            
    }
    if(opt== -1)
    {
        ans=ans-getsum(u,h[u]+1);
    }
    else
        ans=ans-getsum(u,h[u]-h[opt]);
    //cout<<opt<<" ";
}

void solve()
{
    int n,q;
    cin>>n>>q;
    for(int i=0;i<=n;i++)
    {adj[i].clear();
        s[i].clear();
        color[i].clear();
    }
    int u,v;
    for(int i=0;i<n-1;i++)
    {
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    Time=0;
    for(int i=1;i<=n;i++)
        cin>>c[i];
    for(int i=1;i<=n;i++)
        cin>>a[i];
    ans=0;
    dfs(1,0);
    int x;
    while(q--)
    {
        cin>>u>>x;
        remove(u);
        c[u]=x;
        add(u);
        cout<<ans<<endl;
    }
    
    
    
    
    
    
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





