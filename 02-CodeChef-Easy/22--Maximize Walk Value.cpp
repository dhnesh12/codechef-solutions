#include<bits/stdc++.h>
using namespace std;
bool p[12][1002][1002];
int cost[1002] , pn[12];
vector<int> adj[1002];
void dfs(int x , int src , int par){
    for(int j=0;j<1001;j++){if(p[x][par][j]){p[x][src][j]=true;
        if(j+cost[src]<1001){p[x][src][j+cost[src]]=true;}}}
    for (auto i : adj[src]){if (i != par){dfs(x,i,src);}}}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);int n,s,q;cin >> n >> s >> q;
    for (int j = 1; j < n; j++){int x; cin >> x;adj[x].push_back(j+1);adj[j+1].push_back(x);}
    for (int j = 1; j <= n; j++){cin >> cost[j];} for (int j = 0; j < s; j++){cin >> pn[j];}
    for (int j = 0; j < s; j++){p[j][0][0] = true;dfs(j,pn[j],0);}
    while (q--){int u , v, w;cin >> u >> v >> w;int an = 0;
        for (int j = 0; j < s; j++){
            for (int i = w; i >= 0; i--){if (p[j][u][i] && p[j][v][i]){an = max(an,2*i);break;}}}
        cout << an << endl;}}