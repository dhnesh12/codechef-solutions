

/*

#include <iostream>
#include <vector>
#include <queue>
#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
#include <stdio.h>
#include <string.h>
#include <climits>
#include <queue>
#include<bitset>
#include<fstream>


using namespace std;

#define ll long long

map<string, int>ind;
int n, m;
vector<vector<int>>adj;

int dist[257]={0};
bool vis[257]={0};

struct family
{
    vector<int>child, parent, sibling;
};

void bfs(int node)
{
    queue<int>q;
    q.push(node);
    dist[node]=0;
    vis[node]=true;
    while(!q.empty())
    {
        int v=q.front();
        q.pop();
        for(int i=0;i<adj[v].size();i++)
        {
            if(!vis[adj[v][i]])
            {
                vis[adj[v][i]]=true;
                dist[adj[v][i]]=dist[v]+1;
                q.push(adj[v][i]);
            }
        }
    }
}

int main()
{
    
    ifstream fin("balance.in");
    ofstream fout("balance.out");

    cin>>n>>m;
    int count=1;
    
    vector<family>v;
    for(int i=0;i<=n;i++)
    {
        vector<int>a, b, c;
        v.push_back({a, b, c});
    }
    
    adj.resize(n+1);
    for(int i=0;i<m;i++)
    {
        string a, b, c, d, e;
        cin>>a>>b>>c>>d>>e;
        if(ind[a]==0)
        {
            ind[a]=count;
            count++;
        }
        if(ind[e]==0)
        {
            ind[e]=count;
            count++;
        }
        
        if(c=="brother"||c=="sister")
        {
            v[ind[a]].sibling.push_back(ind[e]);
            v[ind[e]].sibling.push_back(ind[a]);
        }
        if(c=="son"||c=="daughter")
        {
            v[ind[a]].parent.push_back(ind[e]);
            v[ind[e]].child.push_back(ind[a]);
        }
        if(c=="father"||c=="mother")
        {
            v[ind[a]].child.push_back(ind[e]);
            v[ind[e]].sibling.push_back(ind[a]);
        }
        
        adj[ind[a]].push_back(ind[e]);
        adj[ind[e]].push_back(ind[a]);
        
        
    }
    
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<adj[i].size();j++)
        {
            
        }
    }
    
    
    int Q;
    cin>>Q;
    
    while(Q--)
    {
        string a, b;
        cin>>a>>b;
        memset(vis, 0, sizeof(vis));
        vis[0]=true;
        memset(dist, -1, sizeof(dist));
        bfs(ind[a]);
        cout<<dist[ind[b]]<<endl;
    }
    
    
}



*/

#include <iostream>
#include <vector>
#include <queue>
#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <set>
#include <stdio.h>
#include <string.h>
#include <climits>
#include <queue>
#include<bitset>
#include<fstream>


using namespace std;



map<string, int> IDCache;
vector<int> ds[301];
bool vis[301][301];
int dist[301][301];

int main() {
    int N, Q, M;
    cin >> N >> Q;
    memset(dist, 0, sizeof(dist));
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < N; ++ i) ds[i].clear();
    IDCache.clear(); M = 0;
    while (Q --) {
        string A, is, F, of , B;
        cin >> A >> is >> F >> of >> B;
        if (!IDCache.count(A)) IDCache[A] = M ++;
        if (!IDCache.count(B)) IDCache[B] = M ++;
        int u = IDCache[A], v = IDCache[B];
        if (F == "father" || F == "mother") ds[u].push_back(v), dist[u][v] = dist[v][u] = 1;
        if (F == "brother" || F == "sister") dist[u][v] = dist[v][u] = vis[u][v] = vis[v][u] = 1;
        if (F == "son" || F == "daughter") ds[v].push_back(u), dist[u][v] = dist[v][u] = 1;
    }
    while (true) {
        bool flag = false;
        for (int i = 0; i < M; ++ i) {
            for (int j = 0; j < (int)ds[i].size(); ++ j) {
                for (int k = 0, v = ds[i][j]; k < M; ++ k) {
                    if (vis[v][k] && !dist[i][k]) {
                        dist[i][k] = dist[k][i] = 1;
                        ds[i].push_back(k);
                        flag = true;
                    }
                }
            }
            for (int j = 0; j < (int)ds[i].size(); ++ j) {
                for (int k = j + 1; k < (int)ds[i].size(); ++ k) {
                    int u = ds[i][j], v = ds[i][k];
                    if (!dist[u][v]) {
                        dist[u][v] = dist[v][u] = 1;
                        vis[u][v] = vis[v][u] = 1;
                        flag = true;
                    }
                }
            }
            for (int j = 0; j < M; ++ j) {
                if (!vis[i][j]) continue;
                for (int k = 0; k < M; ++ k) {
                    if (vis[j][k] && !vis[i][k] && i != k) {
                        vis[i][k] = vis[k][i] = 1;
                        dist[i][k] = dist[k][i] = 1;
                        flag = true;
                    }
                }
            }
        }
        if (!flag) break;
    }
    for (int i = 0; i < M; ++ i) {
        for (int j = 0; j < M; ++ j) {
            if (!dist[i][j]) dist[i][j] = 1e9;
        }
    }
    for (int k = 0; k < M; ++ k) {
        for (int i = 0; i < M; ++ i) {
            for (int j = 0; j < M; ++ j) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    cin >> Q;
    while (Q --) {
        string x, y; cin >> x >> y;
        int u = IDCache[x], v = IDCache[y];
        int ret = dist[u][v];
        if (ret > M) ret = -1;
        cout << ret << endl;
    }
    return 0;
}









