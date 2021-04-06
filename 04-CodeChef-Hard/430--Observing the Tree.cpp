#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N=1e5+10,M=N*500;

int read()
{
	int ret=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) ret=ret*10+(c^48),c=getchar();
	return ret;
}

namespace Data_Structure
{
	int tim,cur,rt[N];
	struct Segment
	{
		int sz,ls[M],rs[M];
		ll sum[M],tk[M],tb[M];
		ll f(ll k,ll b,ll n){return (b+(b+k*(n-1)))*n/2;}
		void copy(int x,int y){ls[x]=ls[y];rs[x]=rs[y];sum[x]=sum[y];tk[x]=tk[y];tb[x]=tb[y];}
		void update(int &x,int y,int l,int r,int L,int R,ll k,ll b)
		{
			x=++sz;copy(x,y);
			if(L<=l && r<=R)
			{
				sum[x]+=f(k,(l-L)*k+b,r-l+1);tk[x]+=k;tb[x]+=(l-L)*k+b;
				return;
			}
			int mid=(l+r)>>1,tl=max(l,L),tr=min(r,R);
			sum[x]+=f(k,(tl-L)*k+b,tr-tl+1);
			if(L<=mid) update(ls[x],ls[y],l,mid,L,R,k,b);
			if(R>mid) update(rs[x],rs[y],mid+1,r,L,R,k,b);
		}
		ll query(int x,int l,int r,int L,int R)
		{
			if(!x || L>R) return 0;
			if(L<=l && r<=R) return sum[x];
			int mid=(l+r)>>1,tl=max(l,L),tr=min(r,R);
			ll res=f(tk[x],tk[x]*(tl-l)+tb[x],tr-tl+1);
			if(L<=mid) res+=query(ls[x],l,mid,L,R);
			if(R>mid) res+=query(rs[x],mid+1,r,L,R);
			return res;
		}
	}T;	
}
using namespace Data_Structure;

namespace Tree
{
	int ind,tot;
	int head[N],siz[N],son[N],fa[N],dfn[N],pos[N],top[N],dep[N];
	struct Tway{int v,nex;}e[N<<1];
	void add(int u,int v)
	{
		e[++tot]=(Tway){v,head[u]};head[u]=tot;
		e[++tot]=(Tway){u,head[v]};head[v]=tot;
	}
	void dfs1(int x,int ff)
	{
		siz[x]=1;fa[x]=ff;dep[x]=dep[ff]+1;
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v==ff) continue;
			dfs1(v,x);siz[x]+=siz[v];
			if(siz[v]>siz[son[x]]) son[x]=v;
		}
	}
	void dfs2(int x,int tp)
	{
		dfn[x]=++ind;pos[ind]=x;top[x]=tp;
		if(son[x]) dfs2(son[x],tp);
		for(int i=head[x];i;i=e[i].nex)
		{
			int v=e[i].v;
			if(v==fa[x] || v==son[x]) continue;
			dfs2(v,v);
		}
	}
	int lca(int x,int y)
	{
		while(top[x]^top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			x=fa[top[x]];
		}
		return dep[x]>dep[y]?y:x;
	}
}
using namespace Tree;

namespace DreamLolita
{
	int n,Q;
	ll ans;
	void update(int x,int y,ll k,ll b,int len)
	{
		ll l=0,r=len;
		while(top[x]^top[y])
		{
			if(dep[top[x]]>dep[top[y]])
			{
				T.update(rt[tim],rt[tim],1,n,dfn[top[x]],dfn[x],-k,b+k*(l+dfn[x]-dfn[top[x]]));
				l+=dfn[x]-dfn[top[x]]+1;x=fa[top[x]];
			}
			else
			{
				T.update(rt[tim],rt[tim],1,n,dfn[top[y]],dfn[y],k,b+k*(r-dfn[y]+dfn[top[y]]));
				r-=dfn[y]-dfn[top[y]]+1;y=fa[top[y]];
			}
		}
		if(dep[x]<dep[y]) T.update(rt[tim],rt[tim],1,n,dfn[x],dfn[y],k,b+k*l);
		else T.update(rt[tim],rt[tim],1,n,dfn[y],dfn[x],-k,b+k*r);
	}
	ll query(int x,int y)
	{
		ll res=0;
		while(top[x]^top[y])
		{
			if(dep[top[x]]<dep[top[y]]) swap(x,y);
			res+=T.query(rt[cur],1,n,dfn[top[x]],dfn[x]);x=fa[top[x]];
		}
		if(dep[x]>dep[y]) swap(x,y);
		res+=T.query(rt[cur],1,n,dfn[x],dfn[y]);
		return res;
	}
	void solution()
	{
		n=read();Q=read();
		for(int i=1;i<n;++i) add(read(),read());
		dfs1(1,0);dfs2(1,1);
		while(Q--)
		{
			char op[3];scanf("%s",op);
			if(op[0]=='c')
			{
				int u=(read()+ans)%n+1,v=(read()+ans)%n+1,b=read(),k=read();
				rt[++tim]=rt[cur];
				update(u,v,k,b,dep[u]+dep[v]-2*dep[lca(u,v)]);
				cur=tim;
			}
			else if(op[0]=='q')
			{
				int u=(read()+ans)%n+1,v=(read()+ans)%n+1;
				printf("%lld\n",(ans=query(u,v)));
			}
			else cur=(read()+ans)%(tim+1);
		}
	}
}

int main()
{
#ifdef Durant_Lee
	freopen("CC_QUERY.in","r",stdin);
	freopen("CC_QUERY.out","w",stdout);
#endif
	DreamLolita::solution();
	return 0;
}