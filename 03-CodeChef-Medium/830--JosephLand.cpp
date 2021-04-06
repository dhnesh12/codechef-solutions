#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> ipair;
typedef vector<int> vi;
typedef long long ll ;
#define fo(i, n) for(int i=0;i<n;i++)
#define rep(i, a, b) for(int i=a; i<(b); i++)
#define pb emplace_back
#define mp make_pair
#define sz(x) (int)(x).size()
#define ff first
#define ss second
#define debug(x) cout << #x << "  " << x << endl;   
#define mem(x,y) memset(x,y,sizeof(x))
#define endl '\n'
#define all(x) x.begin(), x.end()
// #define int long long int

const ll MAXN = 1e14 + 7;
const int N = 1e5+2;
int len;
vector<vector <int>> adj(N);
vector <vector<pair<int ,ll>>> ticket(N); 
ll segtree[4*N];
ll dp[N];
int visited[N];

ll query(int v, int l, int r, int tl, int tr) {
    if(l>r || tl>r || tr<l)
        return MAXN;
    if(tl<=l && tr>=r)
        return segtree[v];
    int mid = (r+l)>>1;
    return min(query(2*v+1, l, mid, tl, tr), query(2*v+2, mid+1, r, tl, tr));
}

void update(int v, int l, int r, int ind, ll val) {
    if(ind < l || ind > r)
        return;
    if(l==r) {
        if(l==ind)
            segtree[v] = val;
        return;
    }
    else {
        int mid = (r + l)>>1;
        update(2*v+1, l, mid, ind, val);
        update(2*v+2, mid+1, r, ind, val);
        segtree[v] = min(segtree[2*v+1], segtree[2*v+2]);
    }
}

void dfs(int v, int lvl) {
    visited[v] = 1;
    for(auto t: ticket[v]) {
        ll tmp = t.ss + query(0, 0, len, max(0, lvl-t.ff), lvl-1);
        dp[v] = min(dp[v], tmp);
    }
    update(0, 0, len, lvl, dp[v]);
    for(int i: adj[v]) {
        if(!visited[i]) {
            dfs(i, lvl+1);
        }
    }
    // update(0, 0, len, lvl, MAXN);
}

signed main() {
    ios_base::sync_with_stdio(false);cin.tie(NULL);
    int n, m;   cin >> n >> m;
    len = n;
    fo(i, n-1) {
        int a, b;   cin >> a >> b;
        adj[a-1].pb(b-1);
        adj[b-1].pb(a-1);

    }
    fo(i, m) {
        int a, b;
        ll c;
        cin >> a >> b >> c;
        ticket[a-1].pb(b, c);
    }
    fill(dp, dp+N, MAXN);
    // fill(segtree, segtree+4*N, MAXN);
    dp[0] = 0;
    dfs(0, 0);
    int q;  cin >> q;
    while(q--) {
        int x; cin >> x;
        cout << dp[x-1] << endl;
    }
}