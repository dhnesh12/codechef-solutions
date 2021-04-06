#pragma GCC optimize("O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

#define fast ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define files(name) name!=""?freopen(name".in","r",stdin),freopen(name".out","w",stdout):0
#define all(a) a.begin(),a.end()
#define len(a) (int)(a.size())
#define elif else if
#define mp make_pair
#define pb push_back
#define fir first
#define sec second

using namespace std;
#define int long long

typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
typedef long double ld;
typedef long long ll;

const int arr=2e5+10;
const int ar=2e3+10;
const ld pi=acos(-1);
const ld eps=1e-10;
const ll md=1e9+7;

///---program start---///

struct line
{
    ld k,b;
    set<line>::iterator it;
    set<line>* where;

    line() {}
    line(ld k,ld b)
    {
        this->k=k;
        this->b=b;
    }

    ld eval(ld x)
    {
        return k*x+b;
    }
};

const bool operator<(const line& lhs,const line& rhs)
{
    if (rhs.k==5e18){
        auto it=lhs.it;
        return next(it)!=lhs.where->end()&&next(it)->k*rhs.b+next(it)->b<=it->k*rhs.b+it->b;
    }
    return lhs.k>rhs.k||(lhs.k==rhs.k&&lhs.b<rhs.b);
}

ld intersect(line l1,line l2)
{
    /// l1.k*x+l1.b==l2.k*x+l2.b
    /// x*(l1.k-l2.k)==l2.b-l1.b
    /// x==(l2.b-l1.b)/(l1.k-l2.k)
    return (l2.b-l1.b)/(l1.k-l2.k);
}

bool to_erase(line l1,line l2,line l3)
{
    ld x=intersect(l1,l2);
    return l2.eval(x)>=l3.eval(x);
}

struct convex_hull_trick
{
    set<line> lines;

    convex_hull_trick()
    {
        lines.clear();
    }

    void clear()
    {
        lines.clear();
    }
    void add_line(line l)
    {
        auto it=lines.insert(l).fir;

        line* what=(line*)&*it;
        what->it=it;
        what->where=(set<line>*)&lines;

        while (it!=lines.begin()&&prev(it)->k==it->k){
            lines.erase(it);
            return;
        }

        while (next(it)!=lines.end()&&next(it)->k==it->k){
            lines.erase(next(it));
        }

        if (it!=lines.begin()&&next(it)!=lines.end()&&to_erase(*prev(it),*it,*next(it))){
            lines.erase(it);
            return;
        }

        while (it!=lines.begin()&&prev(it)!=lines.begin()&&to_erase(*prev(prev(it)),*prev(it),*it)){
            lines.erase(prev(it));
        }

        while (next(it)!=lines.end()&&next(next(it))!=lines.end()&&to_erase(*it,*next(it),*next(next(it)))){
            lines.erase(next(it));
        }
    }

    ld get(ld x)
    {
        if (lines.empty()){
            return 5e18;
        }
        line special(5e18,x);
        auto it=*lines.lower_bound(special);
        return it.eval(x);
    }
};

struct segment_tree
{
    int n;
    vector<convex_hull_trick> t;

    segment_tree() {}
    segment_tree(int n)
    {
        n++;
        this->n=n;
        t.resize(4*n);
    }

    void upd(int v,int l,int r,int tl,int tr,line val)
    {
        if (l>tr||r<tl){
            return;
        }
        if (l>=tl&&r<=tr){
            t[v].add_line(val);
            return;
        }
        int m=(l+r)/2;
        upd(v*2,l,m,tl,tr,val);
        upd(v*2+1,m+1,r,tl,tr,val);
    }
    void upd(int tl,int tr,line val)
    {
        upd(1,1,n,tl,tr,val);
    }
    ld get(int v,int l,int r,int pos,ld x)
    {
        if (l==r){
            return t[v].get(x);
        }
        ld res=t[v].get(x);
        int m=(l+r)/2;
        if (pos<=m){
            res=min(res,get(v*2,l,m,pos,x));
        }
        else{
            res=min(res,get(v*2+1,m+1,r,pos,x));
        }
        return res;
    }
    ld get(int pos,ld x)
    {
        return get(1,1,n,pos,x);
    }
};

#define arr (int)(5e5+10)

vector<pii> reb[arr];
const int M=20;
int p[arr][M];
ld d[arr];
int deep[arr];
int cnt[arr];
int go_hld[arr];

void dfs(int now,int pred=-1)
{
    p[now][0]=pred;
    for (int i=1;i<M;i++){
        p[now][i]=p[p[now][i-1]][i-1];
    }
    cnt[now]=1;
    go_hld[now]=-1;
    for (auto wh:reb[now]){
        if (wh.fir!=pred){
            deep[wh.fir]=deep[now]+1;
            d[wh.fir]=d[now]+wh.sec;
            dfs(wh.fir,now);
            cnt[now]+=cnt[wh.fir];
            if (go_hld[now]==-1||cnt[wh.fir]>cnt[go_hld[now]]){
                go_hld[now]=wh.fir;
            }
        }
    }
}

int lca(int u,int v)
{
    if (deep[u]>deep[v]){
        swap(u,v);
    }
    for (int i=M-1;i>=0;i--){
        if (deep[p[v][i]]>=deep[u]){
            v=p[v][i];
        }
    }
    if (u==v){
        return u;
    }
    for (int i=M-1;i>=0;i--){
        if (p[u][i]!=p[v][i]){
            u=p[u][i];
            v=p[v][i];
        }
    }
    return p[u][0];
}

int len_of_way[arr];
int top_of_way[arr];
int back_of_way[arr];
int number_of_way[arr];
segment_tree S;
vector<line> to_push_on_prefix[arr];

int pos_in_segment_tree[arr];
int who_with_pos[arr];

int current_number_of_way;
int current_pos_in_segment_tree;

void hld(int now,int pred)
{
    pos_in_segment_tree[now]=++current_pos_in_segment_tree;
    who_with_pos[pos_in_segment_tree[now]]=now;
    number_of_way[now]=current_number_of_way;
    if (!top_of_way[current_number_of_way]){
        top_of_way[current_number_of_way]=now;
    }
    len_of_way[number_of_way[now]]++;
    back_of_way[current_number_of_way]=now;

    if (go_hld[now]!=-1){
        hld(go_hld[now],now);
    }
    for (auto wh:reb[now]){
        if (wh.fir!=pred&&wh.fir!=go_hld[now]){
            current_number_of_way++;
            hld(wh.fir,now);
        }
    }
}

void add_line_to_mini_way(int u,int v,line l) /// v is pred u
{
    if (top_of_way[number_of_way[u]]==v){
        to_push_on_prefix[pos_in_segment_tree[u]].pb(l);
    }
    else{
        int tl=pos_in_segment_tree[v];
        int tr=pos_in_segment_tree[u];
        S.upd(tl,tr,l);
    }
}

void add_line_to_way(int u,int v,line l) /// v is pred u
{
    while (number_of_way[u]!=number_of_way[v]){
        int to=top_of_way[number_of_way[u]];
        add_line_to_mini_way(u,to,l);
        u=p[to][0];
    }
    add_line_to_mini_way(u,v,l);
}

void add_way(int u,int v,ld t,ld s)
{
    int LCA=lca(u,v);
    line line1=*new line(-ld(1)/ld(s),ld(d[u])/s+t);
    add_line_to_way(u,LCA,line1);
    line line2=*new line(+ld(1)/ld(s),ld(d[u]-2*d[LCA])/s+t);
    add_line_to_way(v,LCA,line2);
}

int n;
ld ans[arr];

void build_all_ans()
{
    for (int i=1;i<=n;i++){
        ans[i]=S.get(pos_in_segment_tree[i],d[i]);
    }
    convex_hull_trick CHT;
    for (int i=0;i<=current_number_of_way;i++){
        CHT.clear();
        int cur=back_of_way[i];
        for (int j=0;j<len_of_way[i];j++){
            for (auto k:to_push_on_prefix[pos_in_segment_tree[cur]]){
                CHT.add_line(k);
            }
            ans[cur]=min(ans[cur],CHT.get(d[cur]));
            cur=p[cur][0];
        }
    }
}

void solve()
{
    cin>>n;

    for (int i=0;i<=n;i++){
        reb[i].clear();
        ans[i]=0;
        len_of_way[i]=0;
        top_of_way[i]=0;
        back_of_way[i]=0;
        number_of_way[i]=0;
        to_push_on_prefix[i].clear();
        pos_in_segment_tree[i]=0;
        who_with_pos[i]=0;
        d[i]=0;
        deep[i]=0;
        cnt[i]=0;
        go_hld[i]=-1;
    }
    current_number_of_way=0;
    current_pos_in_segment_tree=0;

    for (int i=1;i<n;i++){
        int u,v,w;
        cin>>u>>v>>w;
        reb[u].pb({v,w});
        reb[v].pb({u,w});
    }
    dfs(1,1);
    hld(1,1);
    S=*new segment_tree(n);
    int m;
    cin>>m;
    while (m--){
        int u,v,t,s;
        cin>>u>>v>>t>>s;
        add_way(u,v,t,s);
    }
    build_all_ans();
    for (int i=1;i<=n;i++){
        if (ans[i]==5e18){
            cout<<-1<<"\n";
        }
        else{
            cout<<fixed<<setprecision(7)<<ans[i]<<"\n";
        }
    }
}

main()
{
    #ifdef I_love_Maria_Ivanova
        files("barik");
        freopen("debug.txt","w",stderr);
    #endif

    fast;

    int test;
    cin>>test;
    while (test--){
        solve();
    }
}