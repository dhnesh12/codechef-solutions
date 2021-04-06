#include<bits/stdc++.h>
#define inl inline
#define reg register
#define mk(x,y) make_pair(x,y)
#define pb push_back
#define pll pair<long long,long long>
#define fir first
#define sec second

using namespace std;

namespace zzc
{
    typedef long long ll;
    inl ll read()
    {
        ll x=0,f=1;char ch=getchar();
        while(!isdigit(ch)) {if(ch=='-')f=-1;ch=getchar();}
        while(isdigit(ch)) {x=x*10+ch-48;ch=getchar();}
        return x*f;
    }

    const ll maxn = 4e5+5;
    const ll inf = 0x3f3f3f3f3f3f3f3f;
    ll n,m,qt,tot,len;
    ll id[maxn][4];
    vector<pll> e[maxn];
    
    struct spt
    {
		ll dis[maxn],c[maxn];
		int fa[maxn],dfn[maxn],low[maxn];
		int tim;
		bool vis[maxn];
		vector<int> son[maxn];
		priority_queue<pll> q;
		ll lowbit(ll x) {return x&(-x);}
		
		void dfs(int u)
		{
			dfn[u]=++tim;
			for(int v:son[u])dfs(v);
			low[u]=tim;
		}
		
        void modify(int x,ll w) {for(reg int i=dfn[x];i<=tim;i+=lowbit(i)) c[i]+=w;}

		ll query(int x)
	    {
	        ll res=0;
	        for(reg int i=low[x];i;i-=lowbit(i)) res+=c[i];
	        for(reg int i=dfn[x]-1;i;i-=lowbit(i)) res-=c[i];
	        return res;
	    }
		
		void dijkstra(int l,int r,int S)
		{
			for(int i=l;i<=r;++i)dis[i]=inf,vis[i]=false;
			dis[S]=0;q.push(mk(-dis[S],S));
			while(!q.empty())
			{
				int u=q.top().sec;q.pop();
				if(vis[u])continue;vis[u]=true;
				for(pll x:e[u])
				{
					int v=x.fir;ll w=x.sec;
					if(v<l||v>r||dis[v]<=dis[u]+w)continue;
					dis[v]=dis[u]+w;fa[v]=u;q.push(mk(-dis[v],v));
				}
			}
			for(int i=l;i<=r;++i)if(i!=S)son[fa[i]].pb(i);
			dfs(S);
		}
    }t[20][4];

    void build(int l,int r,int dep)
    {
        int mid=(l+r)>>1;
        for(reg int i=1;i<=n;i++) t[dep][i].dijkstra(id[l][1],id[r][n],id[mid][i]);
        if(l<mid) build(l,mid-1,dep+1);
        if(r>mid) build(mid+1,r,dep+1);
    }

    void calc(int l,int r,int dep,int x,int y)
    {
        int mid=(l+r)>>1;
        for(reg int i=1;i<=n;i++) len=min(len,t[dep][i].dis[x]+t[dep][i].dis[y]);
        if(x<=id[mid][n]&&y>=id[mid][1]) return ;
        if(y<id[mid][1]) calc(l,mid-1,dep+1,x,y);
        else calc(mid+1,r,dep+1,x,y);
    }

    void modify(int l,int r,int dep,int x,int y,ll w)
    {
        int mid=(l+r)>>1;
        for(reg int i=1;i<=n;i++) if(t[dep][i].dis[x]+t[dep][i].dis[y]==len)
        {
            t[dep][i].modify(x,w);
            t[dep][i].modify(y,w);
            return ;
        }
        if(y<id[mid][1]) modify(l,mid-1,dep+1,x,y,w);
        else modify(mid+1,r,dep+1,x,y,w);
    }

    ll query(int l,int r,int dep,int x)
    {
        ll mid=(l+r)>>1,res=0;
        for(reg int i=1;i<=n;i++)
        {
            ll tmp=t[dep][i].query(x);
            if(id[mid][i]==x) tmp>>=1;
            res+=tmp;
        }
        if(x<id[mid][1]) res+=query(l,mid-1,dep+1,x);
        if(x>id[mid][n]) res+=query(mid+1,r,dep+1,x);
        return res;
    }

    void work()
    {
        ll u,v,w,opt,x1,x2,y1,y2;
        n=read();m=read();qt=read();
        for(reg int i=1;i<=m;i++) for(reg int j=1;j<=n;j++) id[i][j]=++tot;
        for(reg int i=1;i<=n-1;i++) for(reg int j=1;j<=m;j++)
        {
            u=id[j][i];v=id[j][i+1];w=read();
            e[u].pb(mk(v,w));e[v].pb(mk(u,w));
        }
        for(reg int i=1;i<=n;i++) for(reg int j=1;j<m;j++)
        {
            u=id[j][i];v=id[j+1][i];w=read();
            e[u].pb(mk(v,w));e[v].pb(mk(u,w));
        }
        build(1,m,0);
        while(qt--)
        {
            opt=read();
            if(opt==1)
            {
                x1=read();y1=read();x2=read();y2=read();w=read();
                u=id[y1][x1];v=id[y2][x2];
                if(u>v) swap(u,v);
                len=inf;calc(1,m,0,u,v);
                modify(1,m,0,u,v,w);
            }
            else
            {
                x1=read();y1=read();u=id[y1][x1];
                printf("%lld\n",query(1,m,0,u));
            }
        }
    }

}

int main()
{
    zzc::work();
    return 0;
}