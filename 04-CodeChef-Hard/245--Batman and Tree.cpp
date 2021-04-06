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

vector<int> g[400005];
ll st[1600005], tmp[1600005];
void push(int n, int s, int e){
    st[n] = max(st[n], tmp[n]);
    if(s != e){
        tmp[n+n] = max(tmp[n+n], tmp[n]);
        tmp[n+n+1] = max(tmp[n+n+1], tmp[n]);
    }
    tmp[n] = -1e18;
}
void update(int n, int s, int e, int l, int r, ll v){
    push(n, s, e);
    if(s > r || l > e || l > r) return;
    if(l <= s && e <= r){
        tmp[n] = max(tmp[n], v);
        push(n, s, e);
        return;
    }
    int mid = (s+e)/2;
    update(n+n, s, mid, l, r, v);
    update(n+n+1, mid+1, e, l, r, v);
    st[n] = max(st[n+n], st[n+n+1]);
}
ll query(int n, int s, int e, int l, int r){
    push(n, s, e);
    if(s > r || l > e || l > r) return -1e18;
    if(l <= s && e <= r) return st[n];
    int mid = (s+e)/2;
    return max(query(n+n, s, mid, l, r), query(n+n+1, mid+1, e, l, r));
}
int ti = 0, S[400005], E[400005], par[19][400005], D[400005];
void dfs(int u, int p, int d){
    S[u] = ++ti;
    D[u] = d;
    par[0][u] = p;
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i];
        if(v == p) continue;
        dfs(v, u, d+1);
    }
    E[u] = ti;
}
int jump(int u, int v){
    int d = D[v] - D[u] - 1;
    for(int i=18;i>=0;i--){
        if((d>>i)&1) v = par[i][v];
    }
    return v;
}
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, s, p;
        scanf("%d%d%d", &n, &s, &p);
        ti = 0;
        for(int i=1;i<=n;i++){
            g[i].clear();
            for(int j=0;j<19;j++) par[j][i] = 0;
        }
        for(int i=1;i<=4*n;i++) st[i] = -1e18, tmp[i] = -1e18;
        for(int i=1;i<=n-1;i++){
            int a, b;
            scanf("%d%d", &a, &b);
            g[a].eb(b);
            g[b].eb(a);
        }
        dfs(1, 0, 1);
        for(int j=1;j<19;j++){
            for(int i=1;i<=n;i++){
                if(par[j-1][i] != 0) par[j][i] = par[j-1][par[j-1][i]];
            }
        }
        int m;
        scanf("%d", &m);
        update(1, 1, n, S[s], S[s], p);
        for(int i=1;i<=m;i++){
            int x, y, r, t;
            scanf("%d%d%d%d", &x, &y, &r, &t);
            if(D[x] > D[y]) swap(x, y);

            if(S[x] <= S[y] && E[y] <= E[x]){
                int z = jump(x, y);
                ll q1 = query(1, 1, n, S[y], E[y]);
                ll q2 = max(query(1, 1, n, 1, S[z]-1), query(1, 1, n, E[z]+1, n));
                if(q1 > r){
                    update(1, 1, n, 1, S[z]-1, q1+t);
                    update(1, 1, n, E[z]+1, n, q1+t);
                }
                if(q2 > r){
                    update(1, 1, n, S[y], E[y], q2+t);
                }
            }
            else{
                ll q1 = query(1, 1, n, S[x], E[x]);
                ll q2 = query(1, 1, n, S[y], E[y]);
                if(q1 > r){
                    update(1, 1, n, S[y], E[y], q1+t);
                }
                if(q2 > r){
                    update(1, 1, n, S[x], E[x], q2+t);
                }
            }
        }
        printf("%lld\n", query(1, 1, n, 1, n));
    }
}