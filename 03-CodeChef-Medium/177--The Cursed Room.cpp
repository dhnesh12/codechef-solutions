//The best is yet to come...
 #include <iostream>
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
#define inf 1000000000000
#define mod 1000000007
#define pb push_back
#define mp make_pair
#define all(v) v.begin(),v.end()
#define S second
#define F first
#define boost1 ios::sync_with_stdio(false);
#define boost2 cin.tie(0);
#define mem(a,val) memset(a,val,sizeof a)
#define endl "\n"
#define maxn 100001

struct Edge 
{
  ll from, to, cap, flow, index;
  Edge(ll from, ll to, ll cap, ll flow, ll index) :
  from(from), to(to), cap(cap), flow(flow), index(index) {}
};

struct PushRelabel
{
  ll N;
  vector<vector<Edge> > G;
  vector<ll> excess;
  vector<ll> dist, active, count;
  queue<int> Q;

  PushRelabel(ll N) : N(N), G(N), excess(N), dist(N), active(N), count(2*N) {}

  void AddEdge(ll from, ll to, ll cap) {
    G[from].push_back(Edge(from, to, cap, 0, G[to].size()));
    if (from == to) G[from].back().index++;
    G[to].push_back(Edge(to, from, 0, 0, G[from].size() - 1));
  }

  void Enqueue(ll v) {
    if (!active[v] && excess[v] > 0) { active[v] = true; Q.push(v); }
  }

  void Push(Edge &e) {
    ll amt=min(excess[e.from], e.cap - e.flow);
    if (dist[e.from] <= dist[e.to] || amt == 0) return;
    e.flow += amt;
    G[e.to][e.index].flow -= amt;
    excess[e.to] += amt;
    excess[e.from] -= amt;
    Enqueue(e.to);
  }

  void Gap(ll k) {
    for (ll v = 0; v < N; v++) {
      if (dist[v] < k) continue;
      count[dist[v]]--;
      dist[v] = max(dist[v], N+1);
      count[dist[v]]++;
      Enqueue(v);
    }
  }

  void Relabel(ll v) {
    count[dist[v]]--;
    dist[v] = 2*N;
    for (ll i = 0; i < G[v].size(); i++)
      if (G[v][i].cap - G[v][i].flow > 0)
    dist[v] = min(dist[v], dist[G[v][i].to] + 1);
    count[dist[v]]++;
    Enqueue(v);
  }

  void Discharge(ll v) {
    for (ll i = 0; excess[v] > 0 && i < G[v].size(); i++) Push(G[v][i]);
    if (excess[v] > 0) {
      if (count[dist[v]] == 1)
    Gap(dist[v]);
      else
    Relabel(v);
    }
  }

  ll GetMaxFlow(ll s, ll t) {
    count[0] = N-1;
    count[N] = 1;
    dist[s] = N;
    active[s] = active[t] = true;
    for (ll i = 0; i < G[s].size(); i++) {
      excess[s] += G[s][i].cap;
      Push(G[s][i]);
    }

    while (!Q.empty()) {
      int v = Q.front();
      Q.pop();
      active[v] = false;
      Discharge(v);
    }

    ll totflow = 0;
    for (ll i = 0; i < G[s].size(); i++) totflow += G[s][i].flow;
    return totflow;
  }
  vector<vector<Edge> > build(){
    return G;
  }
};

int main()
{
    boost1;boost2;
    ll i,j,n,m,t,x,y;   
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        PushRelabel network(n+m+2);
        for(i=1;i<=n;i++)
        network.AddEdge(0,i,1);
        for(i=1;i<=m;i++)
        network.AddEdge(i+n,n+m+1,1);
        while(1)
        {
            cin>>x>>y;
            if(x==0 && y==0)
            break;
            network.AddEdge(x,y+n,1);
        }
        cout<<network.GetMaxFlow(0,n+m+1)<<endl;
    } 
    return 0;
}
