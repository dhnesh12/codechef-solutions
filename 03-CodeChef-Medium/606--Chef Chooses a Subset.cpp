//#include <ext/pb_ds/assoc_container.hpp> 
 //#include <ext/pb_ds/tree_policy.hpp>
// #include <bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <map>
#include <valarray>
#include <iterator>
#include <functional>
#include <limits>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <stack>
using namespace std;
#define IOS ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define trace(x) cerr << #x << ": " << x << " " << endl;

typedef int64_t ll;
 
#define endl '\n'
#define int ll
ll mod=1e9+7;
ll mod1=1e9+5;
ll power(ll a,ll b)
{
    if(b==0) return 1;
    else if(b%2==0)
        return power(((((a)%mod)*((a)%mod))%mod),b/2)%mod;
    else return (((a)%mod)*(power(((((a)%mod)*((a)%mod))%mod),b/2)%mod))%mod;
}
inline ll inverse(ll a,ll md) {
  a %= md;
  if (a < 0) a += md;
  ll b = md, u = 0, v = 1;
  while (a) {
    ll t = b / a;
    b -= t * a; swap(a, b);
    u -= t * v; swap(u, v);
  }
  assert(b == 1);
  if (u < 0) u += md;
  return u;
}
  
  
 //using namespace __gnu_pbds;
 //#define ordered_set tree<pair<int,int>, null_type,less<pair<int,int>>, rb_tree_tag,tree_order_statistics_node_update>
//find_by_order(k)  returns iterator to kth element starting from 0;
//order_of_key(k) returns count of elements strictly smaller than k;
//erase,insert same as normal set
// mt19937 mrand(chrono::high_resolution_clock::now().time_since_epoch().count()); for randomized solution
const int ce=1e9+7;
ll fast_mod(ll input)
{
    return input < ce ? input : input%ce;
}
#define pi acos(-1)
int par[100001];
vector<int> v[100001];
int a[100001],sz[100001],st[100001];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        a[i]=i,sz[i]=1,st[i]=i;
    }
}
int root(int i)
{
    while(i!=a[i])
    {
        a[i]=a[a[i]];
        i=a[i];
    }
    return i;
}
void un(int p,int q)
{
    int x=root(p);
    int y=root(q);
    if(x==y)
        return ;
    if(sz[x]<sz[y])
    {
        a[x]=a[y];
        sz[y]+=sz[x];
        st[y]&=st[x];
    }
    else
    {
        a[y]=a[x];
        sz[x]+=sz[y];
        st[x]&=st[y];
    }
}
void dfs(int u,int pari)
{
    for(auto i:v[u])
    {
        if(i==pari)
            continue;
        par[i]=u;
        dfs(i,u);
    }
}
int32_t main()
{
    IOS
    #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    #endif    
    
    int t;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        for(int i=1;i<=n;i++)
            v[i].clear();
        par[1]=1;
        init(n);
        for(int i=1;i<=n-1;i++)
        {
            int x,y;
            cin>>x>>y;
            v[x].push_back(y);
            v[y].push_back(x);
        }
        dfs(1,0);
        int ans=n;
        bool vis[n+1];
        memset(vis,false,sizeof(vis));   
        for(int i=1;i<=n;i++)
        {
            for(int j=i;j<=n;j=(j+1)|i)
            {
                vis[j]=1;
            }
            for(int j=i;j<=n;j=(j+1)|i)
            {
                if(vis[par[j]])
                {
                    un(j,par[j]);
                }
            }            
            for(int j=i;j<=n;j=(j+1)|i)
            {
                if(a[j]==j)
                {
                    ans=max(ans,sz[j]*st[j]);
                }
            }
            for(int j=i;j<=n;j=(j+1)|i)
            {
                vis[j]=0;
                a[j]=j,sz[j]=1,st[j]=j;
            }
            
        }
        cout<<ans<<endl;
    }
}       
