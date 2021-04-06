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

int a[100005];
ll dp[100005];
vector<int> v[10005];
vector<pii> g[100005];
int in[100005], out[100005], arr[200005], D[100005], rmq[18][200005], ti = 0;
void dfs(int u, int p, int d){
    in[u] = ++ti;
    arr[ti] = u;
    D[u] = d;
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i].fi, w = g[u][i].se;
        if(v == p) continue;
        dp[v] = dp[u] + w;
        dfs(v, u, d+1);
        ++ti;
        arr[ti] = u;
    }
    out[u] = ti;
}
int p[100005], x[100005], y[100005], dia[100005], add[100005];
int LCA(int a, int b){
    if(a == b) return a;
    if(in[a] > in[b]) swap(a, b);
    int l = in[b]-in[a]+1;
    int k = __lg(l);
    return D[rmq[k][in[a]]]<D[rmq[k][in[b]-(1<<k)+1]]?rmq[k][in[a]]:rmq[k][in[b]-(1<<k)+1];
}
ll dist(int a, int b){
    return dp[a] + dp[b] - 2*dp[LCA(a, b)];
}
int get_root(int a){
    if(p[a] == a) return a;
    return p[a] = get_root(p[a]);
}
void merge(int a, int b, int w){
    int ra = get_root(a), rb = get_root(b);
    int u = dist(a, x[ra])>dist(a, y[ra])?x[ra]:y[ra];
    int v = dist(b, x[rb])>dist(b, y[rb])?x[rb]:y[rb];
    if(ra != rb){
        p[ra] = rb;
        if(dia[ra] > dia[rb]){
            dia[rb] = dia[ra];
            x[rb] = x[ra];
            y[rb] = y[ra];
        }
        if(dist(u, a) + dist(v, b) + w > dia[rb]){
            dia[rb] = dist(u, a) + dist(v, b) + w;
            x[rb] = u;
            y[rb] = v;
        }
    }
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        ti = 0;
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++) g[i].clear();
        for(int i=1;i<=n;i++){
            scanf("%d", &a[i]);
            v[a[i]].eb(i);
        }
        for(int i=1;i<=n-1;i++){
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            g[a].eb(mp(b, c));
            g[b].eb(mp(a, c));
        }
        dfs(1, 0, 0);
        for(int i=1;i<=ti;i++) rmq[0][i] = arr[i];
        for(int j=1;j<18;j++){
            for(int i=1;i<=ti;i++){
                if(i+(1<<(j-1)) <= ti) rmq[j][i] = D[rmq[j-1][i]]<D[rmq[j-1][i+(1<<(j-1))]]?rmq[j-1][i]:rmq[j-1][i+(1<<(j-1))];
            }
        }
        for(int i=1;i<=n;i++){
            p[i] = i;
            x[i] = i;
            y[i] = i;
            dia[i] = 0;
            add[i] = 0;
        }
        ll ans = 0;
        for(int i=1;i<=10000;i++){
            int mx = 0;
            for(int j=10000/i*i;j>=i;j-=i){
                for(int k=0;k<sz(v[j]);k++){
                    int u = v[j][k];
                    for(int l=0;l<sz(g[u]);l++){
                        int v = g[u][l].fi, w = g[u][l].se;
                        if(add[v]){
                            merge(u, v, w);
                            mx = max(mx, dia[get_root(u)]);
                        }
                    }
                    ans = max(ans, i*1ll*j*mx);
                    add[u] = 1;
                }
            }
            for(int j=10000/i*i;j>=i;j-=i){
                for(int k=0;k<sz(v[j]);k++){
                    int u = v[j][k];
                    p[u] = u;
                    x[u] = u;
                    y[u] = u;
                    dia[u] = 0;
                    add[u] = 0;
                }
            }
        }
        printf("%lld\n", ans);
        for(int i=1;i<=n;i++) v[a[i]].clear();
    }   
}