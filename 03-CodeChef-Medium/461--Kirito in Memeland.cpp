#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
#define lc (v<<1)    
#define rc (lc|1)
#define pll pair<int, int>
#define ppll pair<int,pll>
#define fr first
#define sc second
#define mp make_pair
#define low lower_bound
#define upp upper_bound
#define pb push_back
#define endl '\n'
const int mxn = 5e4+10;
const ll inf = 2e9+1000;
const int mod = 1e9+7;

int l, r, a[mxn], sz[mxn], fen[2][mxn], ans, n, t, x, y;
vector<int> g[mxn], v2;
vector<pll> er;
bool vis[mxn];

void upd(int l, int val, bool f){
    l++;
    while (l <= mxn && l > 0){
        fen[f][l] += val;
        l += (l & -l);
    }
}

int ask(int l, bool f){
    if(l < 0) return 0;
    l++;
    int res = 0;
    while(l > 0 && l <= mxn){
        res += fen[f][l];
        l -= (l & -l);
    }
    return res;
}

int dfs(int v, int pr = -1){
    sz[v] = 1;
    for(int u : g[v]){
        if(u == pr || vis[u]) continue;
        sz[v] += dfs(u, v);
    }
    return sz[v]; 
}

int cent(int v, int pr, int val){
    int ans = -1;
    if(sz[v] > val) ans = v;
    for(int u : g[v]){
        if(u == pr || vis[u]) continue;
        int cen = cent(u, v, val);
        if(cen != -1 && (ans == -1 || sz[ans] > sz[cen]))
        ans = cen; 
    }
    return ans; 
}

void calc(int v, int pr, bool last, int curr, bool tl){
    
    if(curr > r) return;
    
    ans += ask(r - curr, 0) - ask(l - curr - 1, 0);
    
    if(tl) ans += ask(r - curr - 1, 1) - ask(l - curr - 2, 1);
    else ans += ask(r - curr, 1) - ask(l - curr - 1, 1);
    
    ans += (curr >= l && curr <= r);
    
    v2.pb(curr);
    
    for(int u : g[v]){
        if(u == pr || vis[u]) continue;
        calc(u, v, a[v] < a[u], ((last && a[v] > a[u])?1:0) + curr, tl);
    } 
}

void solve(int v){
    dfs(v);
    if(sz[v] == 1) return;
    int cen = cent(v, -1, sz[v] / 2);
    vis[cen] = true;
    for(int u : g[cen]){
        if(vis[u]) continue;
        solve(u);
    }
    vis[cen] = false;
    for(int u : g[cen]){
        if(vis[u]) continue;
        if(a[cen] > a[u])
            calc(u, cen, 0, 0, 1);
        else calc(u, cen, a[cen] != a[u], 0, 0);
        for(int y : v2){
            er.pb(mp(y, a[cen] > a[u]));
            upd(y, 1, a[cen] > a[u]);
        }   
        v2.clear();
    }
    for(auto p : er)
        upd(p.fr, -1, p.sc);
    er.clear();
}

int main(){
    ios_base :: sync_with_stdio(false),cin.tie(0),cout.tie(0);
    
    cin >> t;
    while(t--){
    
        cin >> n  >> l >> r;
        r = min(r, n);
        for(int i=1; i<=n;i++){
            cin >> a[i];
            g[i].clear();
        }   
        for(int i=0; i<n-1;i++){
            cin >> x >> y;
            g[x].pb(y);g[y].pb(x);
        }
        if(l > r){
            cout << 0 << endl;
            continue;
        }
        ans = 0;
        solve(1);
        cout << ans << endl;
    }

    return 0;
}



