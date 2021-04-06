#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<int, pii> pipii;
typedef pair<pii, pii> piipii;

#define mp make_pair
#define fi first
#define se second
#define all(a) (a).begin(), (a).end()
#define sz(a) (int)(a).size()
#define eb emplace_back
const int mod = 1e9+7;

vector<int> g[300005];
int cnt[300005];
ll p2[300005];
ll dp[300005][2], ans[300005];
void dfs(int u, int p){
    cnt[u] = 0;
    int co = 0;
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i];
        if(v == p) continue;
        dfs(v, u);
        co++;
        cnt[u] += cnt[v];
    }
    if(sz(g[u]) == 1 && p != 0){
        cnt[u]++;
        return;
    }
    dp[u][0] = (p2[co] - 2 + mod)%mod;
    dp[u][1] = (p2[co] - 2 + mod)%mod;
    ll res1 = 0, res2 = 0;
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i];
        if(v == p) continue;

        dp[u][0] = (dp[u][0] + dp[v][0]*1ll*p2[co-1])%mod;
        dp[u][1] = (dp[u][1] + dp[v][0]*1ll*(p2[co-1]-1+mod))%mod;
        dp[u][1] = (dp[u][1] + dp[v][1])%mod;

        res2 = (res2 + res1*1ll*dp[v][0])%mod;
        res1 = (res1 + dp[v][0])%mod;
    }
    if(co >= 2) dp[u][1] = (dp[u][1] + res2*1ll*p2[co-2])%mod;
}
void dfs2(int u, int p, ll val0, ll val1){
    vector<ll> dp2[2];
    dp2[0].clear(), dp2[1].clear();
    if(p != 0){
        dp2[0].eb(val0);
        dp2[1].eb(val1);
    }
    for(int i=0;i<sz(g[u]);i++){
        int v = g[u][i];
        if(v == p) continue;
        dp2[0].eb(dp[v][0]);
        dp2[1].eb(dp[v][1]);
    }
    int co = sz(g[u]);

    dp[u][0] = (p2[co] - 2 + mod)%mod;
    dp[u][1] = (p2[co] - 2 + mod)%mod;
    ll res1 = 0, res2 = 0, res3 = 0;
    for(int i=0;i<sz(dp2[0]);i++){

        dp[u][0] = (dp[u][0] + dp2[0][i]*1ll*p2[co-1])%mod;
        dp[u][1] = (dp[u][1] + dp2[0][i]*1ll*(p2[co-1]-1+mod))%mod;
        dp[u][1] = (dp[u][1] + dp2[1][i])%mod;

        res2 = (res2 + res1*1ll*dp2[0][i])%mod;
        res1 = (res1 + dp2[0][i])%mod;
        res3 = (res3 + dp2[1][i])%mod;
    }
    if(co >= 2) dp[u][1] = (dp[u][1] + res2*1ll*p2[co-2])%mod;
    ans[u] = dp[u][1];

    for(int i=0;i<g[u].size();i++){
        int v = g[u][i];
        if(v == p) continue;

        ll val0 = 0, val1 = 0;
        if(co >= 1) val0 = (val0 + (p2[co-1] - 2 + mod))%mod;
        if(co >= 2) val0 = (val0 + (res1-dp[v][0]+mod)*1ll*p2[co-2])%mod;

        if(co >= 1) val1 = (val1 + (p2[co-1] - 2 + mod))%mod;
        if(co >= 2) val1 = (val1 + (res1-dp[v][0]+mod)*1ll*(p2[co-2]-1+mod))%mod;
        val1 = (val1 + (res3 - dp[v][1] + mod))%mod;

        ll tmp = (res2 - dp[v][0]*1ll*(res1-dp[v][0])%mod + mod)%mod;
        if(co >= 3) val1 = (val1 + tmp*1ll*p2[co-3])%mod;

        dfs2(v, u, val0, val1);
    }
}
int main(){
    p2[0] = 1;
    for(int i=1;i<=300000;i++) p2[i] = p2[i-1]*2%mod;
    int t;
    scanf("%d", &t);
    while(t--){
        int n;
        scanf("%d", &n);
        for(int i=1;i<=n;i++){
            g[i].clear();
            ans[i] = 0;
            cnt[i] = 0;
            dp[i][0] = dp[i][1] = 0;
        }
        for(int i=1;i<=n-1;i++){
            int a, b;
            scanf("%d%d", &a, &b);
            g[a].eb(b);
            g[b].eb(a);
        }
        if(n == 2){
            printf("1\n1\n");
            continue;
        }
        int r = 1;
        for(int i=1;i<=n;i++){
            if(sz(g[i]) > 1) r = i;
        }
        dfs(r, 0);
        dfs2(r, 0, 0, 0);
        for(int i=1;i<=n;i++) printf("%lld\n", (ans[i]+1)%mod);
    }
}