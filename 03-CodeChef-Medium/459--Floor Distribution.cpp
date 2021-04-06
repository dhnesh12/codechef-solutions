#include <bits/stdc++.h>

using namespace std;

const int N = 1111;
const int Rmax = 555;
const int INF = 1e9;

int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};

int n, m, w, k, r;
bool dir[N][N][4], B[N][N];
int Mon[Rmax][2], Con[N][N];
int mf, f, D[Rmax][Rmax], Tr[Rmax];
vector<int> Adj[N];
bool boo[Rmax];

struct data{
    int x, y, u, v;
    data(){}
    data(int a, int b, int c, int d){
        x = a; y = b; u = c; v = d;
    }
} T[N*N];

void Wall(int x, int y, int u, int v){
    if(x==u){
        if(y<v){
            dir[x][y][1] = 0;
            dir[u][v][3] = 0;
        }
        else{
            dir[x][y][3] = 0;
            dir[u][v][1] = 0;
        }
    }
    else{
        if(x<u){
            dir[x][y][2] = 0;
            dir[u][v][0] = 0;
        }
        else{
            dir[x][y][0] = 0;
            dir[u][v][2] = 0;
        }
    }
}

void DFS(int x, int y, int c){
    Con[x][y] = c;
    B[x][y] = 1;
    for(int i = 0; i < 4; i++){
        if(dir[x][y][i]){
            int u = x + dx[i];
            int v = y + dy[i];
            if(B[u][v]) continue;
            DFS(u,v,c);
        }
    }
}

void BackTrack(int u, int minEdge){
    if(u==0){
        f = minEdge;
        return;
    }
    if(Tr[u]!=-1){
        BackTrack(Tr[u],min(minEdge,D[Tr[u]][u]));
        D[Tr[u]][u] -= f;
        D[u][Tr[u]] += f;
    }
}

void MaxFlow(){///min cut
    while(1){
        f = 0;
        queue<int> Qu;
        memset(boo,0,sizeof(boo));
        memset(Tr,255,sizeof(Tr));
        Qu.push(0);
        boo[0] = 1;
        while(!Qu.empty()){
            int u = Qu.front(); Qu.pop();
            if(u==r+1){
                BackTrack(r+1,INF);
                break;
            }
            for(int i = 0; i < (int)Adj[u].size(); i++){
                int v = Adj[u][i];
                if(boo[v]||D[u][v]==0) continue;
                Tr[v] = u;
                boo[v] = 1;
                Qu.push(v);
            }
        }
        if(f==0) break;
        mf += f;
    }
}

int main()
{
    ios_base::sync_with_stdio(0); cin.tie(0);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif // ONLINE_JUDGE
    cin>>n>>m>>w>>k>>r;
    memset(dir,1,sizeof(dir));
    for(int i = 1; i <= w; i++){
        int x, y, u, v;
        cin>>x>>y>>u>>v;
        T[i] = data(x,y,u,v);
        Wall(x,y,u,v);
    }
    memset(B,1,sizeof(B));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++) B[i][j] = 0;
    }
    for(int i = 1; i <= r; i++){
        int x, y, t0, t1;
        cin>>x>>y>>t0>>t1;
        Mon[i][0] = t0;
        Mon[i][1] = t1;
        DFS(x,y,i);
    }
    for(int i = 1; i <= w; i++){
        int s = Con[T[i].x][T[i].y];
        int t = Con[T[i].u][T[i].v];
        if(s==t) continue;
        if(D[s][t]==0){
            Adj[s].push_back(t);
            Adj[t].push_back(s);
        }
        D[s][t]+=k;
        D[t][s]+=k;
    }
    for(int i = 1; i <= r; i++){
        D[0][i] = D[i][0] = Mon[i][1];
        D[r+1][i] = D[i][r+1] = Mon[i][0];
        Adj[0].push_back(i);
        Adj[i].push_back(0);
        Adj[r+1].push_back(i);
        Adj[i].push_back(r+1);
    }
    MaxFlow();
    cout<<mf;
    return 0;
}
