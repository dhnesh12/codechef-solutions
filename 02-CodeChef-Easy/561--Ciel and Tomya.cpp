/**
   ==============================
   **Bismillahir Rahmanir Rahim**
   ==============================
   @Author:   Alve Rahman
   @DateTime: Mon Feb  8 12:34:47 2021
   ==============================
*/
#include<bits/stdc++.h>
#define db1(x) cout<<#x<<"="<<x<<'\n'
#define db2(x,y) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<'\n'
#define db3(x,y,z) cout<<#x<<"="<<x<<","<<#y<<"="<<y<<","<<#z<<"="<<z<<'\n'
#define rep(i,a,b) for(ll i=a;i<b;i++)
#define sz 15
#define mod 998244353
#define PI 3.14159265
#define EPS 1e-9
using namespace std;
using ll=long long;
const ll inf=1e8;
const ll l=1e8;
 
// int randomize(){
//   return rand()%17+1;
// }

vector<pair<int,int>> adj[sz];
priority_queue<pair<int,int>> pq;
int dist[sz],d,color[sz];
bool vis[sz];

int dijkstra(int st,int en){
  dist[st]=0;
  pq.push({0,st});
  while(!pq.empty()){
    int x=pq.top().second;pq.pop();
    if(vis[x]) continue;
    vis[x]=1;
    for(auto u:adj[x]){
      int y=u.first,w=u.second;
      if(dist[x]+w<dist[y]){
        dist[y]=dist[x]+w;
        pq.push({-dist[y],y});
      }
    }
  }
  return dist[en];
}

int dfs(int st,int en,int tot){
  if(color[st]==1) return 0;
  color[st]=1;
  if(st==en){
    color[st]=2;
    if(tot==d) return 1;
    else return 0;
  }
  int tmp=0;
  for(auto x:adj[st])
    tmp+=dfs(x.first,en,tot+x.second);
  color[st]=2;
  return tmp;
}

void solve(){
  rep(i,0,sz) adj[i].clear();
  while(!pq.empty()) pq.pop();
  fill(dist,dist+sz,inf);
  d=0;
  memset(vis,0,sizeof(vis));
  memset(color,0,sizeof(color));
  int n,m,a,b,c;
  cin>>n>>m;
  rep(i,0,m){
    cin>>a>>b>>c;
    adj[a].push_back({b,c});
    adj[b].push_back({a,c});
  }
  d=dijkstra(1,n);
  memset(vis,0,sizeof(vis));
  cout<<dfs(1,n,0)<<'\n';
}

int main(){
  ios_base::sync_with_stdio(false);cin.tie(NULL);
  // srand(time(NULL));
  int t;
  cin>>t;
  while(t--){
    solve();
  }
  return 0;
}