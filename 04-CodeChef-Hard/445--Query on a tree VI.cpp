#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<map>
#include<stack>
#include<queue>
#include<ctime>
#include<vector>
#include<set>
#include<cstdlib>
#include<utility>
using namespace std;
int cnt,head[100000+5],a[100000+5],siz[100000+5],son[100000+5],tot=0,color[100000+5];
int w[100000+5],loc1[100000+5],loc2[100000+5],dep[100000+5],f[17][500000+5];
long long ans;
struct edge{int end,next;}e[200000+5];
struct segment_Tree{int l,r,val[2],flag[2];}T[400000+5];
void add(int pos,int s,int inv)
{
    T[pos].val[inv]+=s;
    T[pos].flag[inv]+=s;
}
void pushdown(int pos)
{
    if (T[pos].flag[0])
    {
        add(pos*2,T[pos].flag[0],0);
        add(pos*2+1,T[pos].flag[0],0);
    }
    if (T[pos].flag[1])
    {
        add(pos*2,T[pos].flag[1],1);
        add(pos*2+1,T[pos].flag[1],1);
    }
    T[pos].flag[0]=T[pos].flag[1]=0;
}
void Build(int Left,int Right,int pos)
{
    T[pos].l=Left;
    T[pos].r=Right;
    if (Left==Right)
    {
        T[pos].val[0]=siz[loc2[Left]];
        T[pos].val[1]=1;
        return;
    }
    int mid=(Left+Right)/2;
    Build(Left,mid,pos*2);
    Build(mid+1,Right,pos*2+1);
}
void modify(int Left,int Right,int pos,int s,int inv)
{
    if (T[pos].l>=Left&&T[pos].r<=Right)
    {
        add(pos,s,inv);
        return;
    }
    pushdown(pos);
    int mid=(T[pos].l+T[pos].r)/2;
    if (Left<=mid) modify(Left,Right,pos*2,s,inv);
    if (Right>mid) modify(Left,Right,pos*2+1,s,inv);
}
int query(int id,int pos,int inv)
{
    if (T[pos].l>=id&&T[pos].r<=id)
        return T[pos].val[inv];
    pushdown(pos);
    int mid=(T[pos].l+T[pos].r)/2;
    if (id<=mid)
        return query(id,pos*2,inv);
    else
        return query(id,pos*2+1,inv);
}
void add_edge(int u,int v)
{
    e[++cnt].end=v;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void dfs1(int u)
{
    int i;
    siz[u]=1;
    for (i=head[u];i;i=e[i].next)
    {
        int v=e[i].end;
        if (f[0][u]==v)
            continue;
        f[0][v]=u;
        dep[v]=dep[u]+1;
        dfs1(v);
        siz[u]+=siz[v];
        if (siz[v]>siz[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int chain)
{
    int i;
    tot++;
    loc1[u]=tot;
    w[u]=chain;
    loc2[tot]=u;
    if (son[u])
        dfs2(son[u],chain);
    for (i=head[u];i;i=e[i].next)
    {
        int v=e[i].end;
        if (f[0][u]==v||v==son[u])
            continue;
        dfs2(v,v);
    }
}
int lca(int u,int v)
{
    int i;
    if (dep[u]>dep[v])
        swap(u,v);
    for (i=16;i>=0;i--)
        if (dep[u]<=dep[f[i][v]])
            v=f[i][v];
    if (u==v)
        return u;
    for (i=16;i>=0;i--)
        if (f[i][u]!=f[i][v])
        {
            u=f[i][u];
            v=f[i][v];
        }
    return f[0][u];
}
void change_chain(int u,int fa,int b,int inv)
{
    while (dep[w[u]]>dep[fa])
    {
        modify(loc1[w[u]],loc1[u],1,b,inv);
        u=f[0][w[u]];
    }
    modify(loc1[fa],loc1[u],1,b,inv);
}
int n,c[100000+5];
int lowbit(int x){return x&(-x);}
void modify_sum(int x,int y)
{
    for (int i=x;i<=n;i+=lowbit(i))
        c[i]+=y;
}
int query_sum(int x)
{
    int sum=0;
    for (int i=x;i>0;i-=lowbit(i))
        sum+=c[i];
    return sum;
}
inline int read()
{
    int res=0;bool bo=false;char c;
    while (((c=getchar())<'0'||c>'9')&&c!='-');
    if (c=='-')
        bo=true;
    else
        res=c-'0';
    while ((c=getchar())>='0'&&c<='9')
        res=(res<<3)+(res<<1)+c-'0';
    return bo?~res+1:res;
}
int main()
{
    int m,i,j;
    n=read();
    for (i=1;i<=n;i++)
        color[i]=0;
    for (i=1;i<n;i++)
    {
        int u,v;
        u=read();v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    f[0][1]=1;
    dep[1]=1;
    dfs1(1);
    for (i=1;i<=16;i++)
        for (j=1;j<=n;j++)
            f[i][j]=f[i-1][f[i-1][j]];
    dfs2(1,1);
    Build(1,n,1);
    m=read();
    while (m--)
    {
        int opt,u,v;
        opt=read();u=read();
        if (opt==0)
        {
            v=u;
            int qq_sum=query_sum(loc1[u]);
            for (i=16;i>=0;i--)
                if (f[i][v]!=0)
                {
                    if (color[u]==0&&qq_sum-query_sum(loc1[f[i][v]])+color[f[i][v]]!=0)
                        continue;
                    if (color[u]==1&&qq_sum-query_sum(loc1[f[i][v]])+color[f[i][v]]!=dep[u]-dep[f[i][v]]+1)
                        continue;
                    v=f[i][v];
                }
            printf("%d\n",query(loc1[v],1,color[v]));
        }
        else
        {
            if (color[u])
            {
                modify_sum(loc1[u],-1);
                modify_sum(loc1[u]+siz[u],1);
            }
            else
            {
                modify_sum(loc1[u],1);
                modify_sum(loc1[u]+siz[u],-1);
            }
            int now_c=color[u];
            color[u]^=1;
            int sum0=query(loc1[u],1,0),sum1=query(loc1[u],1,1);
            if (u==1)
                continue;
            u=f[0][u];
            int qq_sum=query_sum(loc1[u]);
            v=u;
            for (i=16;i>=0;i--)
                if (f[i][v]!=0&&qq_sum-query_sum(loc1[f[i][v]])+color[f[i][v]]==0)
                    v=f[i][v];
            if (v!=1&&color[v]==0)
                v=f[0][v];
      //      printf("%d %d ",u,v);
            if (now_c)
                change_chain(u,v,sum0,0);
            else
                change_chain(u,v,-sum0,0);
            v=u;
            for (i=16;i>=0;i--)
                if (f[i][v]!=0&&qq_sum-query_sum(loc1[f[i][v]])+color[f[i][v]]==dep[u]-dep[f[i][v]]+1)
                    v=f[i][v];
            if (v!=1&&color[v]==1)
                v=f[0][v];
        //    printf(" , %d %d\n",u,v);
            if (!now_c)
                change_chain(u,v,sum1,1);
            else
                change_chain(u,v,-sum1,1);
        }
    }
}
