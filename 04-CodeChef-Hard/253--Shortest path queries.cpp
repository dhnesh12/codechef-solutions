#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int mx = 1e5+5;
const int inf = 1e9+7;
int par[mx][20],depth[mx],dis[mx],cycle_cost[mx],component[mx];
priority_queue< pair<int,int>, vector< pair<int,int> >, greater< pair<int,int> > >pq;
vector< pair<int,int> >edge[mx];
vector< pair< pair<int,int>, int > >total_edge;
///(1)Transposing Graph into a tree using digstra's algo
void digstra(int n){
    for(int i=0;i<n;i++){
        dis[i]=inf;
    }
    dis[0]=0;
    pq.push({0,0});
    while(!pq.empty()){
        pair<int,int>a = pq.top();
        pq.pop();
        if(a.first>dis[a.second]) continue;
        for(int i=0; i<edge[a.second].size(); i++){
            int to = edge[a.second][i].first;
            if(dis[to] > a.first+edge[a.second][i].second){
                dis[to] = a.first+edge[a.second][i].second;
                par[to][0]=a.second;
                depth[to] = depth[a.second]+1;
                pq.push({dis[to],to});
            }
        }
    }
}
///(3)Finding LCA
int LCA(int u, int v){
    if(depth[u]<depth[v]) swap(u,v);
    int dif = depth[u]-depth[v], c=0;
    while(dif>0){
        if(dif&1){
            u=par[u][c];
        }
        dif/=2,c++;
    }
    if(u==v) return u;
    for(int i=19;i>=0;i--){
        if(par[u][i] != par[v][i]){
            u=par[u][i], v=par[v][i];
        }
    }
    return par[u][0];
}
///(4)Finding LCA of Components
int f(int u, int v){
    if(component[u] == component[v]) return u;
    for(int i=19;i>=0;i--){
        if(depth[par[u][i]]>depth[v] && component[par[u][i]]!=component[v]){
            u=par[u][i];
        }
    }
    return par[u][0];
}
int main()
{
#ifdef kk
    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);
#endif // kk
    int n,m,q,u,v,w,cycle = 1;
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&u,&v,&w); u--,v--;
        total_edge.push_back({{u,v},w});
        edge[u].push_back({v,w});
        edge[v].push_back({u,w});
    }
    ///(1)Transposing Graph into a tree using digstra's algo
    digstra(n);
    ///(2)Transposing Cycle into one Component
    for(int i=0;i<m;i++){
        u=total_edge[i].first.first;
        v=total_edge[i].first.second;
        w=total_edge[i].second;
        if(par[u][0]==v || par[v][0]==u) continue;
        if(depth[u]<depth[v]) swap(u,v);
        ll d=(1ll)*dis[u]+dis[v]+w;
        component[u]=component[v]=cycle;
        while(depth[u] != depth[v]){
            u=par[u][0];component[u]=cycle;
        }
        while(u!=v){
            u=par[u][0],v=par[v][0];
            component[u] = component[v] = cycle;
        }
        d-=2*dis[u];
        cycle_cost[cycle++] = d;
    }
    ///LCA part
    for(int j=1;j<20;j++){
        for(int i=0;i<n;i++){
            par[i][j] = par[par[i][j-1]][j-1];
        }
    }
    ///Query part
    scanf("%d",&q);
    while(q--){
        scanf("%d%d",&u,&v);u--,v--;
        ///(3)Finding LCA
        int l = LCA(u,v);
        if(component[l]==0){
            printf("%d\n",dis[u]+dis[v]-2*dis[l]); continue;
        }
        ///(4)Finding LCA of Components
        int r1 = f(u,l), r2 = f(v,l);
        int pans = dis[r1]+dis[r2]-2*dis[l];
        pans = min(pans, cycle_cost[component[l]]-pans);
        int ans = (dis[u]-dis[r1])+(dis[v]-dis[r2])+pans;
        printf("%d\n",ans);
    }
    return 0;
}
