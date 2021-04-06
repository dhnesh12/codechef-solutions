#include <bits/stdc++.h>
using namespace std;
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define endl "\n"
#define int long long
#define fore(i, l, r) for(int i = l; i < r; i++)
#define sz(a) a.size()
#define x first
#define y second
#define rev(s) reverse(s.begin(),s.end())
#define all(a) (a).begin(), (a).end()
#define pb push_back
#define mp make_pair
typedef long double ld;
typedef pair<int, int> pi;
const int N=998244353;
//fast Expo
int fastExpo(int aa,int bb) // aa^bb
{
    int res=1;
    while(bb>0)
    {
        if(bb&1)
        {
            res=(res*aa)%N;
        }
        aa=(aa*aa)%N;
        bb=bb>>1;
    }
    return res;
}
// modular multiplicative inverse
int mmi(int nn)
{
    return fastExpo(nn,N-2);
}
//calculating factorial up to 1e6
const int ramramaramnamshamnam=1e6+1;
int facti[ramramaramnamshamnam];
void facto()
{
    facti[0]=1;
    fore(i,1,1e6+1)
    {
        facti[i]=(facti[i-1]*i)%N;
    }
}
vector<int>adj[100001];
int vis[100001];
void dfs(int node)
{
    vis[node]=1;
    for(auto child:adj[node])
    {
        if(vis[child]==0) dfs(child);
    }
}
//write graph input function
void graph(int vertex,int edge)
{
    for(int i=1;i<=vertex;i++) adj[i].clear();
    memset(vis,0,sizeof vis);
    for(int i=1;i<=edge;i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
}
//solve
void solve() {
  int n,k;
  cin>>n>>k;
  set<int>s;
  fore(i,0,n)
  {
      int u;
      cin>>u;
      s.insert(u);
  }
  int ans=-1;
  int xx = n+k;
  for(int i=0;i<=xx;i++)
  {
      if(s.count(i))
        continue;
      else
      {
          if(k==0)
          {
              ans=i;
              break;
          }
          else
          {
              k--;
          }
      }
  }
  if(ans==-1)
  {
      auto itr = s.rbegin();
      int temp = *itr;
      ans=temp+1;
  }
  cout<<ans<<endl;
}
int32_t main()
{
    IOS;
    cout << fixed << setprecision(15);
    int T=1;
    cin>>T;
    while(T--) solve();
}
