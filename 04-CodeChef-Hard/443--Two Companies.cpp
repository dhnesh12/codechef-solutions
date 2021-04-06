#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
#define W 100000
char bf[W],*p1=bf,*p2=bf;
#define nc() (p1==p2&&(p2=(p1=bf)+fread(bf,1,W,stdin),p2==p1)?-1:*p1++)
inline int read(){
	int x=0;char ch=nc();for(;ch<'0'||ch>'9';ch=nc());
	for(;ch<='9'&&ch>='0';x=x*10+ch-48,ch=nc());return x;
}
#define N 500010
#define inf 0x7f7f7f7f
int i,j,k,m,m1,m2,S,T,n,now,x,y,cnt,sm,ans,flow,last[N],ot[N],fa[N],sz[N],son[N],dep[N],top[N],id[N];
struct edge{int to,next;}e[N<<1];
inline void add(int u,int v){
	e[++cnt]=(edge){v,last[u]},last[u]=cnt;
	e[++cnt]=(edge){u,last[v]},last[v]=cnt;
}
void dfs(int x,int d){
	dep[x]=d,sz[x]=1;for(int i=last[x],y;i;i=e[i].next)if((y=e[i].to)!=fa[x])
	if(fa[y]=x,dfs(y,d+1),sz[x]+=sz[y],sz[y]>sz[son[x]])son[x]=y;
}
void dfs1(int x,int d){
	if(top[x]=d,id[x]=++now,son[x])dfs1(son[x],d);
	for(int i=last[x],y;i;i=e[i].next)if((y=e[i].to)!=fa[x]&&y!=son[x])dfs1(y,y);ot[x]=now;
}
inline int lca(int l,int r){
	for(;top[l]!=top[r];)dep[top[l]]<dep[top[r]]?r=fa[top[r]]:l=fa[top[l]];
	return dep[l]<dep[r]?l:r;
}
struct Edge{int l,r,v,w;void in(){l=read(),r=read(),v=read(),w=lca(l,r);}
bool operator<(const Edge&b)const{return dep[w]<dep[b.w];}}B[N],G[N];
struct Mxf{
	struct edge{int to,next,v;}e[N<<1];int cnt,last[N],d[N],q[N];
	inline void add(int u,int v,int w){
		e[++cnt]=(edge){v,last[u],w},last[u]=cnt;
		e[++cnt]=(edge){u,last[v],0},last[v]=cnt;
	}
	inline bool bfs(){
		for(int i=1;i<=T;++i)d[i]=-1;
		int l=1,r=1;q[r]=S,d[S]=0;
		while(l<=r){
			int x=q[l++];
			for(int i=last[x];i;i=e[i].next)if(e[i].v&&d[e[i].to]==-1){
				d[e[i].to]=d[x]+1,q[++r]=e[i].to;
				if(e[i].to==T)return 1;
			}
		}return 0;
	}
	inline int min(int a,int b){return a<b?a:b;}
	int find(int now,int flow){
		if(flow==0)return 0;if(now==T)return flow;int ret,w=0;
		for(int i=last[now];i&&w<flow;i=e[i].next)
		if(e[i].v&&d[e[i].to]==d[now]+1&&(ret=find(e[i].to,min(flow-w,e[i].v))))e[i].v-=ret,e[i^1].v+=ret,w+=ret;
		if(!w)d[now]=-1;return w;
	}
	inline void mxflow(){
		for(ans=0;bfs();)for(;;){flow=find(S,inf);if(!flow)break;ans+=flow;}
		printf("%d\n",sm-ans);
	}
}qwq;
inline bool bw(int x,int l,int r){return x>=l&&x<=r;}
inline bool check(Edge x,Edge y){
	if(x<y)swap(x,y);
	return bw(id[y.l],id[x.w],ot[x.w])||bw(id[y.r],id[x.w],ot[x.w]);
}
int main(){
	for(qwq.cnt=1,n=read(),m1=read(),m2=read(),i=1;i<n;++i)add(read(),read());
	for(dfs(1,0),dfs1(1,1),i=1;i<=m1;++i)B[i].in();for(i=1;i<=m2;++i)G[i].in();
	for(i=1;i<=m1;++i)for(j=1;j<=m2;++j)if(check(B[i],G[j]))qwq.add(i,m1+j,inf);
	S=m1+m2+1,T=S+1;
	for(i=1;i<=m1;++i)qwq.add(S,i,B[i].v),sm+=B[i].v;
	for(i=1;i<=m2;++i)qwq.add(i+m1,T,G[i].v),sm+=G[i].v;
	qwq.mxflow();
}