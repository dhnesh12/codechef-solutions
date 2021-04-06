#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, int> piipi;
typedef pair<pii, pii> piipii;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back

vector<int> g[200005];
int D[200005], vis[200005], par[200005];
int n, m, k;
bool dfs(int u, int p, int d){
    D[u] = d;
    vis[u] = 1;
    par[u] = p;
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i];
        if(v == p) continue;
        if(vis[v]){
            if(D[v] < D[u]){
                if(D[u]-D[v]+1 >= k){
                    printf("CYCLE\n");
                    printf("%d\n", D[u]-D[v]+1);
                    while(u != par[v]){
                        printf("%d ", u);
                        u = par[u];
                    }
                    printf("\n");
                    return 1;
                }
            }
            continue;
        }
        else{
            if(dfs(v, u, d+1)) return 1;
        }
    }
    return 0;
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d%d%d", &n, &m, &k);
        for(int i=1;i<=n;i++){
            g[i].clear();
            D[i] = 0;
            vis[i] = 0;
        }
        for(int i=1;i<=m;i++){
            int a, b;
            scanf("%d%d", &a, &b);
            g[a].eb(b);
            g[b].eb(a);
        }
        if(!dfs(1, 0, 0)){
            int mx = 0, ans = 1;
            for(int i=1;i<=n;i++){
                if(D[i] > mx){
                    mx = D[i]; 
                    ans = i;
                }
            }
            printf("CUT\n");
            printf("1\n");
            printf("%d\n", ans);
        }   
    }
}