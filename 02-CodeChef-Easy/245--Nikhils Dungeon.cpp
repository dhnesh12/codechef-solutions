#include <bits/stdc++.h>

// loops
#define rep(i, n) for(int i=0; i<n; i++)
#define repA(i, a, n) for(int i=a; i<n; i++)
#define repD(i, a, n) for(int i=a; i>=n; i--)
#define trav(it, ctr) for(auto it=ctr.begin(); it!=ctr.end(); it++)
#define travR(it, ctr) for(auto it=ctr.rbegin(); it!=ctr.rend(); it++)

// I/O
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL)
#define p(x) cout<<x<<"\n"
#define pp(x, y) cout<<x<<" "<<y<<"\n"
#define lbr cout<<"\n"

// container and contants
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define INF 1e18

// namespaces
using namespace std;

// typedefs
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef long long int ll;
typedef map<int, int> mii;
typedef unsigned long long ull;
typedef priority_queue<int> pq;

// global constants
const int mod=1e9+7, N=5000;
ll n, m, u, v, w, T;
vector<vii> adj;
map<ll, ll> parent;
 
// Dijkstra routine
ll Dijkstra(ll s, ll e)
{
  n=adj.size();
  vi dist(n+1, INF);
  dist[s] = 0;
  priority_queue< ii, vector<ii>, greater<ii> > pq;
  pq.push(ii(0, s));
  while(!pq.empty())
  {
    ii front = pq.top();
    pq.pop();
    ll d = front.first, u = front.second;
    if (d > dist[u])
      continue;
    for(ll j=0; j < (ll)adj[u].size(); j++)
    {
      ii v = adj[u][j];
      if (dist[u] + v.second < dist[v.first])
      {
        parent[v.first]=u;
        dist[v.first] = dist[u] + v.second;
        pq.push(ii(dist[v.first], v.first));
      }
    }
  }
 
  // ll key=n;
  // vi seq;
  // if(parent.find(n)!=parent.end())
  // {
  //   while(1)
  //   {
  //     seq.push_back(key);
  //     if(key==1)
  //     break;
  //     key=parent[key];
  //   }
  //   for(ll i=seq.size()-1; i>-1; i--)
  //     cout<<seq[i]<<" ";
  //   cout<<"\n";
  // }
  // else
  // {
  //   cout<<"-1\n";
  // }
  return dist[e];
}
// int main()
// {
//   cin>>n>>m;
  // adj.assign(n+1, vii());
  // for (ll i = 0; i < m; i++)
  // {
  //   cin>>u>>v>>w;
  //   adj[u].push_back(ii(v, w));                              // directed graph
  //   adj[v].push_back(ii(u, w));
  // }
  // Dijkstra(1);
  // return 0;
// }
int main()
{
    FIO;
    int k, x, y;
    cin>>n>>m;
    int grid[n][m], count[n][m], st=1;
    map<int, ii> countToCell;
    rep(i, n){
    	rep(j, m){
	    	cin>>grid[i][j];
	    	countToCell[st]={i, j};
	    	count[i][j]=st++;
	    }
    }
    ll cost[st][st];
    repA(u, 1, st){
        repA(v, 1, st){
            if(u==v)
                cost[u][v]=0;
            else
                cost[u][v]=INT_MAX;
        }
    }
    cin>>x>>y>>T;
    // vi adj[st];
    adj.assign(st, vii());
    rep(i, n){
    	rep(j, m){
    		u=count[i][j];
    		// Left
    		if(j-1>=0){
    			v=count[i][j-1];
    			cost[u][v]=grid[i][j-1];
    			cost[v][u]=grid[i][j];
    			adj[u].pb(ii(v, cost[u][v]));
    			adj[v].pb(ii(u, cost[v][u]));
    		}
    		// Right 
    		if(j+1<m){
    			v=count[i][j+1];
    			cost[u][v]=grid[i][j+1];
    			cost[v][u]=grid[i][j];
    			adj[u].pb(ii(v, cost[u][v]));
    			adj[v].pb(ii(u, cost[v][u]));
    		}
    		// Up
    		if(i-1>=0){
    			v=count[i-1][j];
    			cost[u][v]=grid[i-1][j];
    			cost[v][u]=grid[i][j];
    			adj[u].pb(ii(v, cost[u][v]));
    			adj[v].pb(ii(u, cost[v][u]));
    		}
    		// Down
    		if(i+1<n){
    			v=count[i+1][j];
    			cost[u][v]=grid[i+1][j];
    			cost[v][u]=grid[i][j];
    			adj[u].pb(ii(v, cost[u][v]));
    			adj[v].pb(ii(u, cost[v][u]));
    		}
    	}
    }
    // repA(u, 1, st){
    // 	cost[u][u]=0;
    // 	repA(v, 1, st){
    // 		repA(w, 1, st){
    // 			cost[u][v]=min(cost[u][v], cost[u][w]+cost[w][v]);
    // 		}
    // 	}
    // }
    // repA(u, 1, st){
    // 	cost[u][u]=0;
    // 	repA(v, 1, st){
    // 		repA(w, 1, st){
    // 			cost[u][v]=min(cost[u][v], cost[u][w]+cost[w][v]);
    // 		}
    // 	}
    // }
    // /*
    // repA(u, 1, st){
    //     repA(v, 1, st){
    //         cout<<u<<" "<<v<<" ";
    //         p(cost[u][v]);
    //     }
    // }
    // */
    // p(cost[1][count[x-1][y-1]]+grid[0][0]);
    int taken=Dijkstra(1, count[x-1][y-1])+grid[0][0];
    if(taken<=T){
        p("YES");
        p(T-taken);
    }
    else
    p("NO");
    return 0;
}