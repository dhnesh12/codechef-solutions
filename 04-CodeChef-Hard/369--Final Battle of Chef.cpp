#include <bits/stdc++.h>
#define lb(x) ((x)&(-x))
using namespace std;
typedef long long ll;

const int N=2e5+5;
const ll INF=0x3f3f3f3f3f3f3f3fLL;
struct Tree{ll mn,tag;}t[N<<2];
int n,Q,dfn[N],ids,bfn[N],ibs,c[N],fa[N];
int L[N][20],R[N][20],bid[N],siz[N],w[N];
vector<int> G[N],zo;

void Add(int x,int k) {for(;x<=n;x+=lb(x)) ++c[x];}
int Ask(int x) {int r=0; for(;x;x-=lb(x)) r+=c[x]; return r;}

void bfs()
{
    queue<int> q; q.push(1);
    while(!q.empty())
    {
        int u=q.front(); q.pop();
        bfn[u]=++ibs,bid[ibs]=u;
        for(int v:G[u]) if(!bfn[v]) q.push(v);
    }
}

void dfs(int u)
{
    memset(L[u],0x3f,sizeof(L[u]));
    dfn[u]=++ids,siz[u]=1;
    L[u][0]=R[u][0]=bfn[u];
    for(int v:G[u]) if(v!=fa[u])
    {
        fa[v]=u,dfs(v),siz[u]+=siz[v];
        for(int i=1;i<20;++i)
            L[u][i]=min(L[v][i-1],L[u][i]),R[u][i]=max(R[v][i-1],R[u][i]);
    }
}

void build(int rt,int l,int r)
{
    if(l==r) {t[rt].mn=w[bid[l]]; return;}
    int mid=l+r>>1;
    build(rt<<1,l,mid),build(rt<<1|1,mid+1,r);
    t[rt].mn=min(t[rt<<1].mn,t[rt<<1|1].mn);
}

inline void pushdown(int rt)
{
    if(!t[rt].tag) return;
    t[rt<<1].tag+=t[rt].tag,t[rt<<1|1].tag+=t[rt].tag;
    t[rt<<1].mn+=t[rt].tag,t[rt<<1|1].mn+=t[rt].tag;
    t[rt].tag=0;
}

void change(int rt,int lc,int rc,int l,int r,int x)
{
    if(l<=lc&&r>=rc) {t[rt].mn-=x,t[rt].tag-=x; return;}
    int mid=lc+rc>>1; pushdown(rt);
    if(l<=mid) change(rt<<1,lc,mid,l,r,x);
    if(r>mid) change(rt<<1|1,mid+1,rc,l,r,x);
    t[rt].mn=min(t[rt<<1].mn,t[rt<<1|1].mn);
}

void five(int x,int l,int r)
{
    for(int i=0;(l||r)&&L[x][i]!=0x3f3f3f3f;++i,l>>=1,r>>=1)
        change(1,1,n,L[x][i],R[x][i],l-r);
}

void flask(int rt,int l,int r)
{
    if(l==r) {zo.push_back(l),t[rt].mn=INF;return;}
    int mid=l+r>>1; pushdown(rt);
    if(t[rt<<1].mn<=0) flask(rt<<1,l,mid);
    if(t[rt<<1|1].mn<=0) flask(rt<<1|1,mid+1,r);
    t[rt].mn=min(t[rt<<1].mn,t[rt<<1|1].mn);
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",w+i);
    for(int i=1,a,b;i<n;++i)
    {
        scanf("%d%d",&a,&b);
        G[a].push_back(b),G[b].push_back(a);
    }
    bfs(),dfs(1),build(1,1,n),scanf("%d",&Q);
    for(int j=1,tp,x,k;j<=Q;++j)
    {
        scanf("%d",&tp);
        if(tp==1)
        {
            scanf("%d%d",&x,&k);
            for(;x&&k;x=fa[x],k>>=1)
                if(x==1) five(x,k,0);
                else five(x,k,k>>2);
            zo.clear(),flask(1,1,n);
            for(int i:zo) Add(dfn[bid[i]],1);
        }
        else
            scanf("%d",&x),printf("%d\n",Ask(dfn[x]+siz[x]-1)-Ask(dfn[x]-1));
    }
    return 0;
}