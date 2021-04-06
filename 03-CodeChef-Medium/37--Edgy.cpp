#include<bits/stdc++.h>
#define inline __attribute__((always_inline))
#define R register
#define fp(i,a,b) for(R int i=(a),I=(b)+1;i<I;++i)
#define fd(i,a,b) for(R int i=(a),I=(b)-1;i>I;--i)
#define go(u) for(int i=head[u],v=e[i].v;i;i=e[i].nx,v=e[i].v)
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf;
inline char getc()
{
    return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
    R int res,f=1;
    R char ch;
    while((ch=getc())>'9'||ch<'0')(ch=='-')&&(f=-1);
    for(res=ch-'0';(ch=getc())>='0'&&ch<='9';res=res*10+ch-'0');
    return res*f;
}
char sr[1<<21],z[20];
int C=-1,Z=0;
inline void Ot()
{
    fwrite(sr,1,C+1,stdout),C=-1;
}
void print(R int x)
{
    if(C>1<<20)
    Ot();
    if(x<0)
    sr[++C]='-',x=-x;
    while(z[++Z]=x%10+48,x/=10);
    while(sr[++C]=z[Z],--Z);
    sr[++C]='\n';
}
const int N=1e5+5;
struct eg{int v,nx,w;}e[N<<1];int head[N],tot;
inline void add(R int u,R int v,R int w)
{
    e[++tot]={v,head[u],w},head[u]=tot;
}
inline void swap(R int &x,R int &y)
{
    x^=y^=x^=y;
}
int col[N],bl[N],top[N],dfn[N],rk[N],sz[N],son[N],dep[N],fa[N],cnt,res;
int sum[N][2];
bool ok[N],b[N];
void dfs1(int u,int id)
{
	sz[u]=1,dep[u]=dep[fa[u]]+1,bl[u]=id;
	go(u)
	if(v!=fa[u])
	{
		col[v]=e[i].w,fa[v]=u,dfs1(v,id),sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])
		son[u]=v;
	}
}
void dfs2(int u,int t)
{
	rk[dfn[u]=++cnt]=u,top[u]=t,sum[u][0]=sum[u][1]=0;
	if(!son[u])
	return;
	dfs2(son[u],t);
	go(u)
	if(!top[v])dfs2(v,v),++sum[u][col[v]];
	if((!sum[u][0]||!sum[u][1])&&(sum[u][0]+sum[u][1])&&col[u]==col[son[u]])
	ok[u]=1,b[u]=(sum[u][col[u]^1]!=0);
	if(sum[u][0]&&sum[u][1]||col[u]!=col[son[u]])++res;
}
struct node
{
	node *lc,*rc;int sz[2],c,r;
	inline void ppd()
	{
	    r^=1,c^=1,swap(sz[0],sz[1]);
	}
	inline void pd()
	{
	    if(r)lc->ppd(),rc->ppd(),r=0;
	}
	inline void upd()
	{
	    sz[0]=lc->sz[0]+rc->sz[0],sz[1]=lc->sz[1]+rc->sz[1];
	}
}
pool[N<<2],*rt,*pp=pool;
inline node* newnode()
{
    pp->lc=pp->rc=NULL,pp->sz[0]=pp->sz[1]=pp->c=pp->r=0;
    return pp++;
}
void build(node* &p,int l,int r)
{
	p=newnode();
	if(l==r)
	{
		p->c=col[rk[l]];
		if(ok[rk[l]])
		p->sz[b[rk[l]]]=1;
		res+=p->sz[1];
		return;
	}
	int mid=(l+r)>>1;
	build(p->lc,l,mid),build(p->rc,mid+1,r);
	p->upd();
}
int query(node *p,int l,int r,int x)
{
	if(l==r)
	return p->c;
	int mid=(l+r)>>1;p->pd();
	return x<=mid?query(p->lc,l,mid,x):query(p->rc,mid+1,r,x);
}
void update(node *p,int l,int r,int x,int d)
{
	if(l==r)
	{
		res-=p->sz[1];
		p->sz[0]=p->sz[1]=0;
		if(d>=0)
		p->sz[d]=1;
		res+=p->sz[1];
		return;
	}
	int mid=(l+r)>>1;
	p->pd();
	x<=mid?update(p->lc,l,mid,x,d):update(p->rc,mid+1,r,x,d);
	p->upd();
}
void rev(node *p,int l,int r,int ql,int qr)
{
	if(ql<=l&&qr>=r)
	return res-=p->sz[1],res+=p->sz[0],p->ppd(),void();
	int mid=(l+r)>>1;
	p->pd();
	if(ql<=mid)
	rev(p->lc,l,mid,ql,qr);
	if(qr>mid)
	rev(p->rc,mid+1,r,ql,qr); 
	p->upd();
}
int n,q;
inline void clr()
{
    fp(i,1,n)head[i]=top[i]=son[i]=ok[i]=b[i]=0;
    tot=cnt=0;
    pp=pool;
}
void change(int u)
{
	int las=-1;
	while(u!=1)
	{
		if(son[u])
		{
			int c=query(rt,1,n-1,dfn[u]);
			int cc=query(rt,1,n-1,dfn[son[u]]);
			if(c!=cc||(sum[u][0]&&sum[u][1]))
			--res;
			if(las>=0)
			--sum[u][las],++sum[u][las^1];
			c^=1;
			if(c!=cc||(sum[u][0]&&sum[u][1]))
			++res;
			if((!sum[u][0]||!sum[u][1])&&(sum[u][0]+sum[u][1])&&c==cc)update(rt,1,n-1,dfn[u],sum[u][c^1^1]!=0);
			else
			update(rt,1,n-1,dfn[u],-1);
		}
		rev(rt,1,n-1,dfn[top[u]],dfn[u]);
		u=top[u];
		las=query(rt,1,n-1,dfn[u])^1;
		u=fa[u];
	}
	if(las>=0)
	--sum[u][las],++sum[u][las^1];
}
int main()
{
	for(int T=read();T;--T)
	{
		n=read(),res=0,sum[1][0]=sum[1][1]=0;
		for(R int i=1,u,v,w;i<n;++i)
		u=read(),v=read(),w=read(),add(u,v,w),add(v,u,w);
		go(1)fa[v]=1,col[v]=e[i].w,dfs1(v,v),++sum[1][col[v]];
		top[1]=1;go(1)dfs2(v,v);
		res+=(sum[1][0]!=0)+(sum[1][1]!=0);
		build(rt,1,n-1);
		q=read();
		while(q--)
		{
			int u=read(),v=read();
			res-=(sum[1][0]!=0)+(sum[1][1]!=0);
			change(u),
			change(v);
			res+=(sum[1][0]!=0)+(sum[1][1]!=0);
			print(res);
		}
		clr();
	}
	return Ot(),0;
}