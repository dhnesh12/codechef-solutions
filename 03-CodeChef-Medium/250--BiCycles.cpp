#include<bits/stdc++.h>
using namespace std;

const int maxN = 5e4+7, maxM = 5e4+7;
namespace HopcroftKarp {
  int n;
  int vis[maxN], level[maxN], ml[maxN], mr[maxM];
  vector<int> edge[maxN]; // constructing edges for left part only

  void init(int nn) {      // n = nodes in left part
    n = nn;
    for (int i = 1; i <= n; ++i) edge[i].clear();
  }

  void add(int u, int v) {
    edge[u].push_back(v);
  }

  bool dfs(int u) {
    vis[u] = true;
    for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
      int v = mr[*it];
      if (v == -1 || (!vis[v] && level[u] < level[v] && dfs(v))) {
        ml[u] = *it;
        mr[*it] = u;
        return true;
      }
    }
    return false;
  }

  int matching() { // n for left
    memset(vis, 0, sizeof vis);
    memset(level, 0, sizeof level);
    memset(ml, -1, sizeof ml);
    memset(mr, -1, sizeof mr);

    for (int match = 0;;) {
      queue<int> que;
      for (int i = 1; i <= n; ++i) {
        if (ml[i] == -1) {
          level[i] = 0;
          que.push(i);
        } else level[i] = -1;
      }
      while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
          int v = mr[*it];
          if (v != -1 && level[v] < 0) {
            level[v] = level[u] + 1;
            que.push(v);
          }
        }
      }
      for (int i = 1; i <= n; ++i) vis[i] = false;
      int d = 0;
      for (int i = 1; i <= n; ++i) if (ml[i] == -1 && dfs(i)) ++d;
      if (d == 0) return match;
      match += d;
    }
  }
}

const int N = 1e5+7;
vector<int> adj[N];
int col[N], id[N];

void dfs(int u, int cc) {
    col[u] = cc;
    for (int v: adj[u])
        if (col[v] == -1)
            dfs(v, !cc);
}

bool vis[N];
vector<int> cycle;
void go(int u, int xx) {
    cycle.push_back(u);
    vis[u] = 1;
    for (int i=0; i<3; i++)
        if (i!=xx && !vis[adj[u][i]])
            go(adj[u][i], xx);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    int t;
    cin>>t;

    while (t--) {
        int n;
        cin>>n;

        for (int i=1; i<=n; i++)    adj[i].clear(), col[i] = -1;

        for(int i=1; i<=3*n/2; i++) {
            int u, v;
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }

        vector<int> left, right;
        for (int i=1; i<=n; i++) {
            if (col[i] == -1)   dfs(i, 0);
            if (!col[i])    left.push_back(i),  id[i] = left.size();
            else            right.push_back(i), id[i] = right.size();
        }
        assert(left.size() == n/2 && right.size() == n/2);

        for (int xx=2;xx>0;xx--) {
            HopcroftKarp::init(n/2);
            for (int x: left) {
                for (int i=0; i<=xx; i++)
                    HopcroftKarp::add(id[x], id[adj[x][i]]);
            }

            int mm = HopcroftKarp::matching();

            for (int x: left) {
                int other = right[HopcroftKarp::ml[id[x]]-1];
                for (int i=0; i<=xx; i++)
                    if (adj[x][i] == other) swap(adj[x][i], adj[x][xx]);
                for (int i=0; i<=xx; i++)
                    if (adj[other][i] == x) swap(adj[other][i], adj[other][xx]);
            }
        }

        vector<vector<int>> ans;
        for (int xx = 0; xx < 3; xx++) {
            fill(vis, vis+n+1, 0);

            for (int i=1; i<=n; i++) {
                if (vis[i]) continue;
                cycle.clear();
                go(i, xx);
                ans.push_back(cycle);
            }
        }
        cout<<ans.size()<<"\n";
        for (auto cycle: ans)   {
            cout<<cycle.size();
            for (int x: cycle)  cout<<" "<<x;
            cout<<"\n";
        }
    }
}
