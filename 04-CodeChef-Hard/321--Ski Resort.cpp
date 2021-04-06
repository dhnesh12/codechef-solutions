#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db double
#define pii pair<ll,int>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,b,a) for(register int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(register int i=(a);i<(b);++i)
#define fore(i,a) for(register int i=0;i<a.size();++i)
#define gc() getchar()
inline int rd()
{
	int x=0,w=1;char c=gc();while(!isdigit(c)&&c!='-')c=gc();
	if(c=='-')w=-1,c=gc();while(isdigit(c))x=x*10+c-48,c=gc();return x*w;
}
const int N=105,V=50005,M=2000005,inf=1000000005;
int S,T,tt,cc=1,hd[V],iter[V],dis[V],q[V];
struct E{int v,nxt,w;}e[M];
inline void add(int u,int v,int w)
{
	e[++cc]=(E){v,hd[u],w};hd[u]=cc;
	e[++cc]=(E){u,hd[v],0};hd[v]=cc;
} 
bool bfs()
{
	rep(i,1,tt)dis[i]=inf,iter[i]=hd[i];
	int ql=0,qr=0;q[++qr]=S;dis[S]=1;
	while(ql<qr)
	{
		int x=q[++ql];
		for(int i=hd[x];i;i=e[i].nxt)
		{
			int y=e[i].v;
			if(dis[y]>dis[x]+1&&e[i].w){dis[y]=dis[x]+1;q[++qr]=y;}
		}
	}
	return dis[T]<inf;
}
int dfs(int x,int f)
{
	if(x==T||!f)return f;
	int sf=0;
	for(int&i=iter[x];i;i=e[i].nxt)if(e[i].w&&dis[e[i].v]==dis[x]+1)
	{
		int w=dfs(e[i].v,min(f,e[i].w));
		if(w){e[i].w-=w;e[i^1].w+=w;f-=w;sf+=w;if(!f)break;}
	}
	return sf;
}
int mxflw()
{
	ll ans=0;
	while(bfs())ans+=dfs(S,inf);
	return ans>=inf?-1:ans;
}
const int dx[5]={0,0,1,0,-1};
const int dy[5]={0,1,0,-1,0};
int n,m,sx,sy,tx,ty,id[N][N],w[N][N];
struct st{int x,y,w;}a[10]; 
inline bool cmp(st a,st b){return a.w<b.w;}
void sol()
{
	n=rd();m=rd();S=n*m*5+1;T=S+1;tt=0;cc=1;
	memset(hd,0,sizeof(hd));
	sx=rd();sy=rd();tx=rd();ty=rd();
	rep(i,1,n)rep(j,1,m)id[i][j]=++tt,w[i][j]=rd();
	add(S,id[sx][sy],inf);add(id[tx][ty],T,inf);
	rep(i,1,n)rep(j,1,m)
	{
		int nn=0;
		rep(k,1,4)
		{
			int x=i+dx[k],y=j+dy[k];
			if(x<1||x>n||y<1||y>m)continue;
			if(w[i][j]<=w[x][y])a[++nn]=(st){x,y,w[x][y]};
			if((i==sx&&j==sy)||(i==tx&&j==ty))add(id[x][y],id[i][j],w[i][j]>w[x][y]?0:inf);
		}
		if((i==sx&&j==sy)||(i==tx&&j==ty)||!nn)continue;
		sort(a+1,a+nn+1,cmp);
		rep(k,1,nn-1)
		{
			int x=a[k].x,y=a[k].y,v=a[k].w;
			tt++;add(tt,tt+1,v-w[i][j]+1);add(id[x][y],tt,inf);
		}
		int x=a[nn].x,y=a[nn].y,v=a[nn].w;
		tt++;add(tt,id[i][j],v-w[i][j]+1);add(id[x][y],tt,inf);
	}
	tt=T;printf("%d\n",mxflw());
}
int main(){int T=rd();while(T--)sol();return 0;}
