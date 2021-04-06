#pragma GCC optimization "Ofast"
#pragma GCC optimization "unroll-loop"
#pragma GCC target ("avx2")

#include <bits/stdc++.h>
#define ll long long
#define ld long double
#define fs first
#define sc second
using namespace std;
const ll N = 1e5 + 9;
const ll inf = 1e9 + 7;
const ll lim = 31;
typedef pair<ll,ll> LL;
vector<LL> g[N];
ll T,n,xo[N],x,y,w;

void Repack(){
    for (ll i = 1;i <= n;i++) g[i].clear();
}

void DFS(ll u,ll p){
    for (auto i : g[u]){
        ll v = i.fs,w = i.sc;
        if (v != p){
            xo[v] = xo[u] ^ w;
            DFS(v,u);
        }
    }
}

bool chkbit(ll x,ll i){
    return (x >> i) & 1;
}

struct Trie{
    Trie *child[2];
    Trie(){
        child[0] = child[1] = NULL;
    }
    void Add(ll bit,ll x){
        if (bit > lim) return;
        ll now = chkbit(x,lim - bit);
        if (!child[now]) child[now] = new Trie;
        child[now] -> Add(bit + 1,x);
    }
    ll MaxXor(ll bit,ll x){
        if (bit > lim) return 0;
        ll cur = lim - bit;
        ll oppo = 1 - chkbit(x,cur);
        if (child[oppo]) return (1ll << cur) + child[oppo] -> MaxXor(bit + 1,x);
        return child[1 - oppo] -> MaxXor(bit + 1,x);
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    #define task "test"
    if (fopen(task".inp","r")){
        freopen(task".inp","r",stdin);
        freopen(task".out","w",stdout);
    }
    cin>>T;
    while(T--){
        Trie Tr;
        cin>>n; Repack();
        for (ll i = 1;i < n;i++){
            cin>>x>>y>>w;
            g[x].push_back({y,w}); g[y].push_back({x,w});
        }
        DFS(1,0); //for (ll i = 1;i <= n;i++) cout<<xo[i]<<" "; return 0;
        ll ans = 0;
        for (ll i = 1;i <= n;i++) Tr.Add(0,xo[i]),ans = max(ans,xo[i]);
        //ll now = Tr.MaxXor(0,6);
        //cout<<now; return 0;
        for (ll i = 1;i <= n;i++) ans = max(ans,Tr.MaxXor(0,xo[i]));
        cout<<ans<<"\n";
    }
}
