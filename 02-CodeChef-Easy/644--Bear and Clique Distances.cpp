                    //S.G.N.//
#include <bits/stdc++.h>
using namespace std;
typedef vector< long long > vi;
typedef long long ll;
#define sz(a) int((a).size())
#define pb push_back
#define all(c) (c).begin(),(c).end()
#define endl "\n"
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define fr(n) for(ll i=0;i<n;i++)
#define tr(a) for(auto it=a.begin();it!=a.end();it++)
#define N 998244353445 
#define PI 3.1415926535897932384
#define F first
#define S second
#define mp make_pair
#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define mod 1000000007
ll n,k,m,x,s;
vector<pair<ll,ll>> v[100001];
ll dist[100001];
ll dist2[100001];
ll vis[100001];
void dijkstra(ll i){
                                                // set the vertices distances as infinity
               // set all vertex as unvisited
    dist[i] = 0;
    set < pair < ll,ll > > s;          // multiset do the job as a min-priority queue

    s.insert({0 , i});                          // insert the source node with distance = 0

    while(!s.empty()){

        pair <ll,ll> p = *s.begin();        // pop the vertex with the minimum distance
        s.erase(s.begin());

        ll x = p.S; ll wei = p.F;
        if( vis[x] ) continue;                  // check if the popped vertex is visited before
         vis[x] = true;

        for(int i = 0; i < v[x].size(); i++){
            ll e = v[x][i].F; ll w = v[x][i].S;
            if(dist[x] + w < dist[e]  ){            // check if the next vertex distance could be minimized
                dist[e] = dist[x] + w;
                s.insert({dist[e],  e} );           // insert the next vertex with the updated distance
            }
        }
    }
}
void dijkstra2(ll i){
                                                // set the vertices distances as infinity
               // set all vertex as unvisited
    dist2[i] = 0;
    set < pair < ll,ll > > s;          // multiset do the job as a min-priority queue

    s.insert({0 , i});                          // insert the source node with distance = 0

    while(!s.empty()){

        pair <ll,ll> p = *s.begin();        // pop the vertex with the minimum distance
        s.erase(s.begin());

        ll x = p.S; ll wei = p.F;
        if( vis[x] ) continue;                  // check if the popped vertex is visited before
         vis[x] = true;

        for(int i = 0; i < v[x].size(); i++){
            ll e = v[x][i].F; ll w = v[x][i].S;
            if(dist2[x] + w  < dist2[e]  ){            // check if the next vertex distance could be minimized
                dist2[e] = dist2[x] + w;
                s.insert({dist2[e],  e} );           // insert the next vertex with the updated distance
            }
        }
    }
}
void solve()
{ 
cin>>n>>k>>x>>m>>s;
fr(100001)
dist[i]=1000000000000000,dist2[i]=1000000000000000,vis[i]=0,v[i].clear();
fr(m)
{
  ll a,b,c;
  cin>>a>>b>>c;
  v[a].pb({b,c});
  v[b].pb({a,c});
}
dijkstra(s);
ll mn=1000000000000000;
ll idx;
fr(n+1)
{
  vis[i]=0;
  if(i>=1&&i<=k&&dist[i]<mn)
    mn=dist[i],idx=i;
}
rep(i,1,n+1)
{
  if(i<=k&&i!=idx)
  {
  tr(v[i])
  {
    ll a=it->first;
    ll b=it->second;
    v[idx].pb({a,b+x});
    
  }
}
  else if(i>k)
  {
    tr(v[i])
    {
      ll a=it->first;
    ll b=it->second;
    if(a<=k&&a!=idx)
      it->first=idx,it->second+=x;

    }
  }
  
}
rep(i,1,n+1)
{
  if(i<=k&&i!=idx)
    v[i].clear();
  
}
dijkstra2(s);
rep(i,1,n+1)
{
  if(i<=k)
  {
    cout<<min(dist[i],dist[idx]+x)<<" ";
  }
  else
  cout<<min(dist2[i],dist[i])<<" ";
}
cout<<endl;
}
int main()
{
  
  #ifndef ONLINE_JUDGE
     * freopen("input.txt", "r", stdin);
      freopen("output.txt", "w", stdout);
  #endif
  FAST
  ll test;
//test=1;
  cin>>test;
  while(test--)
  {
    
    solve();
  }
  return 0;
}
