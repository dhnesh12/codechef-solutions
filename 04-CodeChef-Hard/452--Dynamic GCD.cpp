// Smit Vavliya

#include <bits/stdc++.h>
using namespace std;
const int inf = (1LL<<60) - 1;
const int mod = 998244353;

const int N = 50005;
struct edge {
    int u, v, next; 
};
int cnt, timer;
int head[N], in[N], FT[N], value[N], par[N], top[N], chain[N], sz[N], depth[N];
edge e[N << 1];

void addEdge(int u, int v) {
    cnt++;
    e[cnt].u = u;
    e[cnt].v = v;
    e[cnt].next = head[u];
    head[u] = cnt;
}

void dfs1(int cur, int p, int d) {
    depth[cur] = d;
    par[cur] = p;
    sz[cur] = 1;
    chain[cur] = 0;
    for(int i=head[cur];i;i=e[i].next) {
        int v=e[i].v;
        if(v == par[cur]) continue;
        dfs1(v,cur,d+1);
        sz[cur]+=sz[v];
        if(sz[v]>sz[chain[cur]]) chain[cur] = v;
    }
}

void dfs2(int cur, int tp) {
    in[cur] = ++timer;
    FT[timer]=cur;
    top[cur]=tp; 
    if(chain[cur]) dfs2(chain[cur], tp);
    for(int i=head[cur];i;i=e[i].next) {
        int v=e[i].v;
        if(v==par[cur]||v==chain[cur]) continue;
        dfs2(v,v);
    }
}

struct tr {
    int first, last, gcd;
};
tr t[4 * N];
int arr[N];
int lazy[4 * N];
int n;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

struct SegmentTree {
    tr combine(tr x, tr y) {
        tr ans;
        if(x.first == 0) return y;
        if(y.first == 0) return x;
        ans.first = x.first;
        ans.last = y.last;
        ans.gcd = gcd(gcd(x.gcd, y.gcd), abs(y.first - x.last));
        return ans;
    }

    void build(int node, int start, int end) {
        if(start == end) {
            t[node].first = t[node].last = value[FT[start]];
            t[node].gcd = 0;
        } else {
            int mid = (start + end) / 2;
            build(node * 2, start, mid);
            build(node * 2 + 1, mid + 1, end);
            t[node] = combine(t[node * 2], t[node * 2 + 1]);
        }
    }

    void propagate(int node, int start, int end, int val, bool flag) {
        t[node].first += val;
        t[node].last += val;
        if(start != end) {
            lazy[node * 2] += val;
            lazy[node * 2 + 1] += val;
        }
        if(flag) lazy[node] = 0;
    }

    tr queryLazy(int node, int start, int end, int l, int r) {
        tr ans;
        ans.first = ans.last = ans.gcd = 0;
        if(start > end || start > r || end < l) return ans;
        if(lazy[node]) propagate(node, start, end, lazy[node], true);
        if(start >= l && end <= r) return t[node];
        int mid = (start + end) / 2;
        tr left, right;
        left = queryLazy(node * 2, start, mid, l, r);
        right = queryLazy(node * 2 + 1, mid + 1, end, l, r);
        return combine(left, right);
    }

    void updateLazyRange(int node, int start, int end, int l, int r, int val) {
        if(lazy[node]) propagate(node, start, end, lazy[node], true);
        if(start > end || start > r || end < l)  return;
        if(start >= l && end <= r) {
            propagate(node, start, end, val, false);
            return;
        }
        int mid = (start + end) / 2;
        updateLazyRange(node * 2, start, mid, l, r, val);
        updateLazyRange(node * 2 + 1, mid + 1, end, l, r, val);
        t[node] = combine(t[node * 2], t[node * 2 + 1]);
    }
} SegmentTree;

void update(int x, int y, int z) {
    while(top[x] != top[y]) {
        if(depth[top[x]] < depth[top[y]]) swap(x, y);
        SegmentTree.updateLazyRange(1, 1, n, in[top[x]], in[x], z);
        x = par[top[x]];
    }
    if(depth[x] < depth[y]) swap(x, y);
    SegmentTree.updateLazyRange(1, 1, n, in[y], in[x], z);
}

int queGcd(int x, int y) {
    tr ans;
    ans.first = ans.last = ans.gcd = 0;
    while(top[x] != top[y]) {
        if(depth[top[x]] < depth[top[y]]) swap(x, y);
        ans = SegmentTree.combine(ans, SegmentTree.queryLazy(1, 1, n, in[top[x]], in[x]));
        x = par[top[x]];
    }
    if(depth[x] < depth[y]) swap(x, y);
    ans = SegmentTree.combine(ans, SegmentTree.queryLazy(1, 1, n, in[y], in[x]));
    return gcd(ans.first, ans.gcd);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n;
    for(int i=1;i<n;i++) {
        int x,y;
        cin>>x>>y;
        x++,y++;
        addEdge(x,y);
        addEdge(y,x);
    }
    for(int i=1;i<=n;i++) cin>>value[i];
    dfs1(1,1,0);
    timer=0;
    dfs2(1,1);
    SegmentTree.build(1,1,n);
    int q;
    cin>>q;
    while(q--) {
        char c;
        int l,r,x;
        cin>>c;
        if(c == 'F') {
            cin>>l>> r;
            l++,r++;
            cout<<queGcd(l, r)<<"\n";
        } else {
            cin>>l>>r>>x;
            l++,r++;
            update(l,r,x);
        }
    }
}