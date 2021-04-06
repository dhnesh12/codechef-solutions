#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
#define sd(x) scanf("%d", &(x))
#define pii pair<int, int>
#define F first
#define S second
#define all(c) ((c).begin()), ((c).end())
#define sz(x) ((int)(x).size())
 
const int INF = 1 << 30;
 
void merge(vector<int> & a, vector<int> & b, int offset = 1){
    if(b.empty()){
        return;
    }
    if(a.empty()){
        a = b;
        return;
    }
    if(offset==1)assert(a.back() == b[0]);
    copy(b.begin() + offset, b.end(), back_inserter(a));
}
 
struct graph {
  int n;
  vector<vector<int>> adj, rdj, dist, prv;
  graph(int n) : n(n), adj(n), rdj(n), dist(n), prv(n){ }
  void add_edge(int src, int dst) {
    adj[src].push_back(dst);
    rdj[dst].push_back(src);
  }
 
  vector<vector<int>> strongly_connected_components() { // kosaraju
    vector<int> ord, visited(n);
    vector<vector<int>> scc;
    function<void(int,vector<vector<int>>&, vector<int>&)> dfs 
      = [&](int u, vector<vector<int>> &adj, vector<int> &out) {
      visited[u] = true;
      for (int v: adj[u]) 
        if (!visited[v]) dfs(v, adj, out);
      out.push_back(u);
    };
    for (int u = 0; u < n; ++u)
      if (!visited[u]) dfs(u, adj, ord);
    fill(all(visited), false);
    for (int i = n-1; i >= 0; --i) 
      if (!visited[ord[i]]) 
        scc.push_back({}), dfs(ord[i], rdj, scc.back()); 
    return scc;
  }
 
    void bfs(int s){
        dist[s].assign(n, INF);
        prv[s].assign(n, -1);
        dist[s][s] = 0;
        queue<int> q; q.push(s);
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v : adj[u]) if(dist[s][v] == INF){
                dist[s][v] = dist[s][u] + 1;
                prv[s][v] = u;
                q.push(v);
            }
        }
    }
 
    vector<int> getPath(int a, int b){
        int curr = b;
        vector<int> ret;
        while(curr != a){
            ret.push_back(curr);
            curr = prv[a][curr];
        }
        ret.push_back(a);
        reverse(all(ret));
        return ret;
    }
 
    void precompute(){
        for(int i= 0; i < n; i++)bfs(i);
    }
 
    vector<int> go_scc(vector<int> nodes, int st, int en){
        if(sz(nodes) == 1){
            return nodes;
        }
        int a = -1, b = -1, mx = -1;
        for(int i : nodes) for(int j : nodes) if(dist[i][j] > mx || (dist[i][j] == mx && i == st)){
            mx = dist[i][j];
            a = i, b = j;
        }
        vector<int> walk = getPath(a, b);
        set<int> vis;
        for(int it : walk) vis.insert(it);
        for(int i : nodes) if(!vis.count(i)){
            vector<int> now = getPath(walk.back(), i);
            merge(walk, now);
        }
        b = walk.back();
        if( (st == -1 || st == a) && (en == -1 || en == b)) return walk;
        vector<int> lft, rgt;
        if(en != -1 && dist[b][en] == mx){
            vector<int> rev_walk = getPath(b, en);
            reverse(all(rev_walk));
            vis.clear();
            for(auto it : rev_walk) vis.insert(it);
            for(int i : nodes) if(!vis.count(i)){
                vector<int> now = getPath(i, rev_walk.back());
                reverse(all(now));
                merge(rev_walk, now);
            }
            if(st != -1){
                vector<int> now = getPath(st, rev_walk.back());
                reverse(all(now));
                merge(rev_walk, now);
            }
            reverse(all(rev_walk));
            return rev_walk;
        } else{
            if(st != -1) lft = getPath(st, walk[0]);
            if(en != -1) rgt = getPath(walk.back(), en);
            merge(lft, walk);
            merge(lft, rgt);
            return lft; 
        }
    }
    vector<int> getWalk(){
        precompute();
        vector<vector<int>> scc = strongly_connected_components();
        vector<int> where(n, -1);
        for(int i = 0; i < sz(scc); i++) for(int j : scc[i]) where[j] = i;
        vector<pii> edge(n, {-1, -1});
        for(int i = 0; i < n; i++) for(int j : adj[i]){
            if(where[j] == where[i] + 1) edge[where[i]] = {i, j};
        }
        for(int i = 0; i + 1 < sz(scc); i++) if(edge[i].F == -1) return {};
        vector<int> walk;
        for(int i = 0; i < sz(scc); i++){
            int st = i == 0 ? -1 : edge[i - 1].S;
            int en = i == sz(scc) - 1 ? -1 : edge[i].F;
            vector<int> now = go_scc(scc[i], st, en);
            merge(walk, now, 0);
        }
        return walk;
    }
};
 
int main(){
    int t; sd(t);
    while(t--){
        int n, m;
        sd(n); sd(m);
        graph g(n);
        for(int i = 0; i < m; i++){
            int u, v; sd(u); sd(v); u--; v--;
            g.add_edge(u, v);
        }
 
        vector<int> walk = g.getWalk();
        if(walk.empty()){
            printf("-1\n");
            continue;
        }
        printf("%d ", sz(walk) - 1);
        for(auto it : walk) printf("%d ", it + 1);
        printf("\n");
    }
}