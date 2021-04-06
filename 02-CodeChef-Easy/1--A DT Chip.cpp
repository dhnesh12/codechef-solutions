#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
using namespace std;
#define hackcyborg shresth_walia
#define all(a) a.begin(), a.end()
#define ll long long
#define ld long double
#define pb push_back
#define mod 1000000007
#define IO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
#define int long long
#define ordered_set tree<int,null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define sz(x) (int)(x).size()
typedef pair<int, int> pii;
typedef vector<int> vi;
ll bp(ll a,ll b)
{
    ll res=1;
    while(b>0)
    {
        if(b&1)
        res=(a*res)%mod;
        a=(a*a)%mod;
        b/=2;
    }
    return res;
}
struct UF {
      vi e;
      UF(int n) : e(n, -1) {}
      bool sameSet(int a, int b) { return find(a) == find(b); }
      int size(int x) { return -e[find(x)]; }
      int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
      bool join(int a, int b) {
            a = find(a), b = find(b);
            if (a == b) return false;
            if (e[a] > e[b]) swap(a, b);
            e[a] += e[b]; e[b] = a;
            return true;
      }
};
struct que
{
      int t,l1,r1,l2,r2;
};
ll n,m,q;
vector<vi> a;
UF Tree(5000000);
void fun(ll x,ll y)
{
      if(a[x][y]==0)
                  {
                        if(x-1>0 && a[x-1][y]==0)
                            Tree.join(((x-1)*m)+y,(x-2)*m+y);
                    if(x+1<=n && a[x+1][y]==0)
                       Tree.join(((x-1)*m)+y,((x)*m)+y);
                    if(y-1>0 && a[x][y-1]==0)
                       Tree.join(((x-1)*m)+y,((x-1)*m)+y-1);
                    if(y+1<=m && a[x][y+1]==0)
                       Tree.join(((x-1)*m)+y,((x-1)*m)+y+1);
                  }
}
main()
{
   IO
   cin>>n>>m>>q;
   a.resize(n+1, vector<int>(m+1,0));
   vector<que> ad;
   while(q--)
   {  que u;
           cin>>u.t>>u.l1>>u.r1>>u.l2>>u.r2;
            if(u.t==1)
           {for(int x=u.l1;x<=u.l2;x++)
             {
               a[x][u.r1]=1;
               a[x][u.r2]=1;
             }
            for(int x=u.r1;x<=u.r2;x++)
             {
               a[u.l1][x]=1;
               a[u.l2][x]=1;
             }
           }
           ad.pb(u);
   }
   for(int x=1;x<=n;x++)
   {
          for(int y=1;y<=m;y++)
          {
                fun(x,y);
          }
   }
   reverse(all(ad));
   vector<string> as;
   for(auto it : ad)
   {
            if(it.t==2)
            {
                     if(Tree.sameSet(((it.l1-1)*m)+it.r1,((it.l2-1)*m)+it.r2))
                        as.pb("YES");
                      else
                        as.pb("NO");
            }
            else
            {
                   for(int x=it.l1;x<=it.l2;x++)
             {
               a[x][it.r1]=0;
               fun(x,it.r1);
               a[x][it.r2]=0;
               fun(x,it.r2);
             }
            for(int x=it.r1;x<=it.r2;x++)
             {
               a[it.l1][x]=0;
               fun(it.l1,x);
               a[it.l2][x]=0;
               fun(it.l2,x);
             }
            }
   }
   reverse(all(as));
   for(auto it : as)
     cout<<it<<"\n";
}