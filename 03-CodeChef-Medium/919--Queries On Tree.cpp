#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define  FIO        ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define  Fileio     freopen("output.txt","w",stdout);freopen("input.txt","r",stdin);
#define  all(v)     v.begin(),v.end()
#define  rall(v)    v.rbegin(),v.rend()
#define  MEM(a,x)   memset(a,x,sizeof(a))
#define  SZ(v)      v.size()
#define  nl         "\n"
#define  bug        cout<<"bug"<<nl;
#define  pi         acos(-1.0)
#define  ll     long long
#define  pb     push_back
#define  mp     make_pair
#define  pii    pair< int,int >
#define  pll    pair< ll,ll >
#define  vii    vector< int >
#define  vll    vector< ll >
#define  vpi    vector< pii >
#define  vpl    vector<pll>
#define  MX     100005
#define  EPS    1e-12
#define  ss     second
#define  ff     first
using namespace std;
using namespace __gnu_pbds;

template<typename T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<typename T>
using ordered_multiset=tree<T, null_type, less_equal<T>, rb_tree_tag,tree_order_statistics_node_update>;

inline ll powr(int a,int b){ll res=1;while(b){if(b&1) res*=a;a*=a;b/=2;}return res;}
int cases=1;

#ifdef ppqq
     #define debug(...) __f(#__VA_ARGS__, __VA_ARGS__)
    template < typename Arg1 >
    void __f(const char* name, Arg1&& arg1){
        cerr << name << " is " << arg1 << std::endl;
    }
    template < typename Arg1, typename... Args>
    void __f(const char* names, Arg1&& arg1, Args&&... args){
        const char* comma = strchr(names+1, ',');
        cerr.write(names, comma - names) << " is " << arg1 <<"  ";
        __f(comma+1, args...);
    }
#else
    #define debug(...)
#endif

///******************************************START******************************************
vpi adj[MX],edge;
vii dis;
int gin[MX],tim,start[MX],over[MX];
int parent[MX],seg[2*4*MX];
int depth[MX],n;
int spars_table[MX][20];
void dfs(int u,int p)
{
    for(int i=0;i<adj[u].size();i++)
    {
        int v=adj[u][i].ff;
        if(v!=p)
        {
            parent[v]=u;
            depth[v]=depth[u]+1;
            dfs(v,u);
        }
    }
}

void create_spars_table()
{
    MEM(spars_table,-1);
    for(int i=1;i<=n;i++)
    {
        ///2^0 POSITION IS ACTUALLY PARENT NODE
        spars_table[i][0]=parent[i];
    }
    for(int i=1;(1<<i)<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            int u=spars_table[j][i-1];
            if(u!=-1)
            spars_table[j][i]=spars_table[u][i-1]; ///2^N=(2^N-1 OF 2^N-1 POSITION)
        }
    }
}
int lca(int u,int v)
{
    if(depth[u]!=depth[v])
    {
        ///LEVEL_UP
        if(depth[v]>depth[u]) swap(u,v);
        int dif=depth[u]-depth[v];
        while(dif>0)
        {
        int log=log2(dif);
        u=spars_table[u][log];
        dif-=(1<<log);
        }
    }
    if(u==v) return u;
    int log=0;
    while(1)
    {
        ///SETTING_LOG_VALUE
        int next=log+1;
        if((1<<next)>n) break;
        log++;
    }
    for(int i=log;i>=0;i--)
    {
        ///FINAL_COUNTING
        if(spars_table[u][i]!=-1 && spars_table[u][i]!=spars_table[v][i])
        {
            u=spars_table[u][i];
            v=spars_table[v][i];
        }
    }
    return parent[u];
}
void update(int node,int s,int e,int p,int val)
{
    if(s==e) seg[node]=val;
    else
    {
        int mid=(s+e)/2;
        if(p<=mid) update(2*node,s,mid,p,val);
        else update(2*node+1,mid+1,e,p,val);
        seg[node]=seg[2*node]+seg[2*node+1];
    }
}
void dfs1(int u,int p)
{
    start[u]=++tim;
    dis.pb(u);
    for(auto it: adj[u])
    {
        if(it.ff==p) continue;
        gin[it.ff]=it.ss;
        dfs1(it.ff,u);
    }
    over[u]=++tim;
    dis.pb(u);
}
int query(int node,int s,int e,int lft,int rgt)
{
    if(rgt<s || lft>e) return 0;
    if(s>=lft && e<=rgt) return seg[node];
    int mid=(s+e)/2;
    return query(2*node,s,mid,lft,rgt)+query(2*node+1,mid+1,e,lft,rgt);
}
int main()
{
    FIO;
    cin>>n;
    for(int i=0,x,y,w;i<n-1;i++)
    {
        cin>>x>>y>>w;
        adj[x].pb({y,w});
        adj[y].pb({x,w});
        edge.pb({x,y});
    }
    dis.pb(0);
    dfs1(1,-1);
    parent[1]=1;
    dfs(1,1);
    create_spars_table();
    for(int node=1;node<=n;node++)
    {
        update(1,1,2*n,start[node],gin[node]);
        update(1,1,2*n,over[node],-gin[node]);
    }
    int q;
    cin>>q;
    while(q--)
    {
        int tt;
        cin>>tt;
        if(tt==1)
        {

            int i,c;
            cin>>i>>c;
            if(parent[edge[i-1].ff]==edge[i-1].ss)
            {
                update(1,1,2*n,start[edge[i-1].ff],c);
                update(1,1,2*n,over[edge[i-1].ff],-c);
            }
            else
            {
                update(1,1,2*n,start[edge[i-1].ss],c);
                update(1,1,2*n,over[edge[i-1].ss],-c);
            }
        }
        else
        {
            int u,v;
            cin>>u>>v;
            int LCA=lca(u,v);
            int aa=query(1,1,2*n,1,start[u]),bb=query(1,1,2*n,1,start[v]);
            int cc=2*query(1,1,2*n,1,start[LCA]);
            cout<<aa+bb-cc<<nl;
        }
    }

















}