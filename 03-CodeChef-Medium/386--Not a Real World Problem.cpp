#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int arr[1001][1001];// h(i,j)
int p[1001][1001];
map <pair<int,int>,int> mp;
struct FlowEdge {
    int v, u;
    long long cap, flow = 0;
    FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
    const long long flow_inf = 1e18;
    vector<FlowEdge> edges;
    vector<vector<int>> adj;
    //vector <bool> visited;
    int n, m = 0;
    int s, t;
    vector<int> level, ptr;
    queue<int> q;

    Dinic(int n, int s, int t) : n(n), s(s), t(t) {
        adj.resize(n+1);
        level.resize(n+1);
        ptr.resize(n+1);
        //visited.resize(n+1);
    }

    void add_edge(int v, int u, long long cap) {
        edges.emplace_back(v, u, cap);
        edges.emplace_back(u, v, 0);
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }

    bool bfs() {
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int id : adj[v]) {
                if (edges[id].cap - edges[id].flow < 1)
                    continue;
                if (level[edges[id].u] != -1)
                    continue;
                level[edges[id].u] = level[v] + 1;
                q.push(edges[id].u);
            }
        }
        return level[t] != -1;
    }

    long long dfs(int v, long long pushed) {
        if (pushed == 0)
            return 0;
        if (v == t)
            return pushed;
        for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
            int id = adj[v][cid];
            int u = edges[id].u;
            if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
                continue;
            long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
            if (tr == 0)
                continue;
            edges[id].flow += tr;
            edges[id ^ 1].flow -= tr;
            return tr;
        }
        return 0;
    }

    long long flow() {
        long long f = 0;
        while (true) {
            fill(level.begin(), level.end(), -1);
            level[s] = 0;
            q.push(s);
            if (!bfs())
                break;
            fill(ptr.begin(), ptr.end(), 0);
            while (long long pushed = dfs(s, flow_inf)) {
                f += pushed;
            }
        }
        return f;
    }
};  
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--){
        int H,W,N;
        cin>>H>>W>>N;
        mp.clear();
        for(int i=1;i<=H;i++){
            for(int j=1;j<=W;j++){
                cin>>arr[i][j];
                p[i][j]=0;
            }
        }
        for(int i=1;i<=N;i++){
            int a,b,x;
            cin>>a>>b>>x;
            mp[{a,b}]=i;
            p[a][b]=x;
        }
        ll ans=0;
        struct Dinic* D=new Dinic(N+1,0,N+1);
        for(int i=1;i<=H;i++){
            for(int j=1;j<=W;j++){
                if(p[i][j]){
                    if(arr[i][j]>=0){
                        D->add_edge(0,mp[{i,j}],arr[i][j]*p[i][j]);
                        D->add_edge(mp[{i,j}],0,arr[i][j]*p[i][j]);
                        ans+=arr[i][j]*p[i][j];
                    }
                    else if(arr[i][j]<=0){
                        D->add_edge(N+1,mp[{i,j}],-1*arr[i][j]*p[i][j]);
                        D->add_edge(mp[{i,j}],N+1,-1*arr[i][j]*p[i][j]);
                        ans+=-1*arr[i][j]*p[i][j];
                    }
                    if(i-1>0&&p[i-1][j]){
                        D->add_edge(mp[{i,j}],mp[{i-1,j}],p[i-1][j]*p[i][j]);
                        D->add_edge(mp[{i-1,j}],mp[{i,j}],p[i-1][j]*p[i][j]);
                        ans+=(p[i][j]*p[i-1][j]);
                    }
                    if(j-1>0&&p[i][j-1]){
                        D->add_edge(mp[{i,j}],mp[{i,j-1}],p[i][j-1]*p[i][j]);
                        D->add_edge(mp[{i,j-1}],mp[{i,j}],p[i][j-1]*p[i][j]);
                        ans+=(p[i][j]*p[i][j-1]);
                    }
                }
            }
        }
        ans-=(2*D->flow());
        cout<<ans<<endl;
        fill(D->level.begin(),D->level.end(),-1);
        D->level[0]=0;
        D->q.push(0);
        D->bfs();
        for(int i=1;i<=N;i++){
            if(D->level[i]!=-1)cout<<1<<" ";
            else cout<<-1<<" ";
        }
        cout<<endl;
    }
    return 0;
}