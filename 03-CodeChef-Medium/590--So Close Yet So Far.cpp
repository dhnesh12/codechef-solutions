#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
using namespace std;
const int N = 35005;
const int SQ = 190;
const int LG = 16;
const int INF = 2e9 + 5;
vector<int> adj[N];
pair<int,int> ar[N];
int dep[N], sp[SQ][N], etl[N], etr[N], etid[3*N], vis[N], res[N], rev[N], idx, cntIdx;

struct Segment{
    int l,r,mn,sz;
}tree[4*N];

struct Query{
    int l,r,lc,tp,id;
    bool operator<(Query o) const{
        if(l / SQ != o.l / SQ){
            return l < o.l;
        }
        return (l / SQ & 1) ? (r < o.r) : (r > o.r);
    }
};

void dfs(int u, int p){
    etl[u] = idx;
    etid[idx++] = u;
    for(int i=1;i<LG;i++){
        sp[i][u] = sp[i-1][sp[i-1][u]];
    }
    for(int v : adj[u]){
        if(v == p){
            continue;
        }
        dep[v] = dep[u] + 1;
        sp[0][v] = u;
        dfs(v,u);
    }
    etr[u] = idx;
    etid[idx++] = u;
}

int lca(int u, int v){
    if(dep[u] > dep[v]){
        swap(u,v);
    }
    for(int i=LG-1;i>=0;i--){
        if(dep[v]-(1 << i) >= dep[u]){
            v = sp[i][v];
        }
    }
    if(u == v){
        return u;
    }
    for(int i=LG-1;i>=0;i--){
        if(sp[i][u] != sp[i][v]){
            u = sp[i][u];
            v = sp[i][v];
        }
    }
    return sp[0][u];
}

void check(int u, int id = 1, int l = 1, int r = N){
    if(l == r){
        tree[id].sz ^= 1;
        tree[id].l = tree[id].r = u;
        tree[id].mn = INF;
    }else{
        int m = (l+r)/2;
        if(u <= m){
            check(u, id << 1, l, m);
        }else{
            check(u, (id << 1) + 1, m+1, r);
        }
        Segment lf = tree[id << 1], rg = tree[(id << 1) + 1];
        if(!lf.sz && !rg.sz){
            tree[id].l = tree[id].r = -1;
            tree[id].mn = INF;
            tree[id].sz = 0;
        }else if(!lf.sz){
            tree[id] = rg;
        }else if(!rg.sz){
            tree[id] = lf;
        }else{
            tree[id].l = lf.l;
            tree[id].r = rg.r;
            tree[id].mn = min(min(lf.mn,rg.mn),ar[rg.l].first-ar[lf.r].first);
            tree[id].sz = 1;
        }
    }
}

int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d",&ar[i].first);
        ar[i].second = i;
    }
    sort(ar+1,ar+n+1);
    for(int i=1;i<=n;i++){
        rev[ar[i].second] = i;
    }
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d %d",&u,&v);
        u = rev[u], v = rev[v];
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    int q;
    scanf("%d",&q);
    int cl = 0, cr = -1;
    Query qry[q];
    for(int i=0;i<q;i++){
        char c[4];
        int u,v;
        scanf("%s %d %d",c,&u,&v);
        u = rev[u], v = rev[v];
        qry[i].tp = c[0] == 'C' ? 0 : 1;
        qry[i].lc = lca(u,v);
        qry[i].id = i;
        if(etl[u] > etl[v]){
            swap(u,v);
        }
        if(qry[i].lc == u){
            qry[i].l = etl[u];
            qry[i].r = etl[v];
        }else{
            qry[i].l = etr[u];
            qry[i].r = etl[v];
        }
    }
    sort(qry,qry+q);
    for(int i=0;i<q;i++){
        while(cl > qry[i].l){
            check(etid[--cl]);
        }
        while(cr < qry[i].r){
            check(etid[++cr]);
        }
        while(cl < qry[i].l){
            check(etid[cl++]);
        }
        while(cr > qry[i].r){
            check(etid[cr--]);
        }
        int u = etid[qry[i].l], v = etid[qry[i].r];
        if(qry[i].lc != u && qry[i].lc != v){
            check(qry[i].lc);
        }
        res[qry[i].id] = qry[i].tp ? ar[tree[1].r].first-ar[tree[1].l].first : tree[1].mn;
        if(qry[i].lc != u && qry[i].lc != v){
            check(qry[i].lc);
        }
    }
    for(int i=0;i<q;i++){
        printf("%d\n",res[i]);;
    }
}