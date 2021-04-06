#include<cstdio>
#include<algorithm>
#include<cctype>
#include<queue>
using namespace std;
#define G getchar()
inline int read()
{
	int x=0; bool flg=false; char ch=G;
	for (;!isdigit(ch);ch=G) if (ch=='-') flg=true;
	for (;isdigit(ch);ch=G) x=(x<<3)+(x<<1)+(ch^48);
	return flg?-x:x;
}
#undef G
typedef long long ll;
const ll INF=1e11;

int n,m;
struct Rec{
	int u,v;
	ll l,s,t;
}r[10010];
ll U[10010],V[10010];
int O[210],I[210];

namespace F{  //flow

struct Edge{
	int to,nxt;
	ll v,c;
}edge[50010];  //4m+8n+2
int cnt,last[210],S,T,K;  //cnt=1
inline void addedge(int x,int y,ll a,ll b,ll c){
	edge[++cnt]=(Edge){y,last[x],a,c},last[x]=cnt;
	edge[++cnt]=(Edge){x,last[y],b,-c},last[y]=cnt;
}
ll dis[210],h[210]; int pid[210];
void spfa(){
	static bool inq[210];
	static int que[220],hd,tl;
	hd=tl=0;
	for (int i=1;i<=T;i++) inq[i]=0,dis[i]=INF;
	dis[S]=0; que[++tl]=S;
	while (hd^tl){
		int u=que[hd=hd==210?1:hd+1],v;
		inq[u]=0;
		for (int i=last[u];i;i=edge[i].nxt)
			if (v=edge[i].to,edge[i].v&&dis[u]+edge[i].c<dis[v]){
				dis[v]=dis[u]+edge[i].c;
				if (!inq[v]) inq[v]=1,que[tl=tl==210?1:tl+1];
			}
	}
	for (int i=1;i<=T;i++) h[i]=dis[i];
}
typedef pair<ll,int> P;
#define st first
#define nd second
bool dijkstra(){
	priority_queue<P,vector<P>,greater<P> > que;
	for (int i=1;i<=T;i++) dis[i]=INF,pid[i]=0;
	dis[S]=0; que.push((P){dis[S],S});
	while (!que.empty()){
		P x=que.top(); que.pop();
		if (x.st^dis[x.nd]) continue;
		int u=x.nd,v;
		for (int i=last[u];i;i=edge[i].nxt)
			if (v=edge[i].to,edge[i].v&&dis[u]+edge[i].c-h[v]+h[u]<dis[v]){
				dis[v]=dis[u]+edge[i].c-h[v]+h[u];
				pid[v]=i;
				que.push((P){dis[v],v});
			}
	}
	return dis[T]!=INF;
}
#undef st
#undef nd
bool vis[210];
ll dfs(int x,ll flw){
	if (x==T) return flw;
	vis[x]=1;
	ll t,used=0;
	for (int i=last[x],v;i;i=edge[i].nxt)
		if (v=edge[i].to,edge[i].v&&!vis[v]&&dis[x]+edge[i].c+h[x]-h[v]==dis[v]){
			t=dfs(v,min(flw-used,edge[i].v));
			edge[i].v-=t; edge[i^1].v+=t;
			used+=t; if (used==flw) return vis[x]=0,used;
		}
	if (used) vis[x]=0;
	return used;
}


ll w[210];  //I-O
  //i and i+n
  //w
  //reverse edge
ll work(){
	K=n*2+1; S=K+1,T=S+1;
	cnt=1; for (int i=1;i<=T;i++) last[i]=0,O[i]=I[i]=w[i]=0;

	for (int i=1;i<=m;i++){
		int &u=r[i].u,&v=r[i].v;
		O[u]++; I[v]++;
	}
	ll fee=0,flw=0;
	for (int i=1;i<=m;i++){
		int &u=r[i].u,&v=r[i].v;
		ll &l=r[i].l,&s=r[i].s,&t=r[i].t;
		fee+=INF*(-s+l);
		addedge(v+n,u,0,INF,-s+l);
		w[v+n]-=INF; w[u]+=INF;
		addedge(u,v+n,INF,0,t-l);
	}
	for (int i=1;i<=n;i++){
		//fee+=O[i]*0;
		addedge(K,i,INF-O[i],0,0);
		w[K]-=O[i]; w[i]+=O[i];
		//fee
		addedge(i+n,K,0,INF+I[i],0);
		w[i+n]-=I[i]; w[K]+=I[i];
	}
	for (int i=1;i<=K;i++)
		if (w[i]>0) addedge(S,i,w[i],0,0),flw-=w[i];
		else if (w[i]<0) addedge(i,T,-w[i],0,0);
	
	spfa();
	while (dijkstra()){
		for (int i=1;i<=T;i++) vis[i]=0;
		ll t=dfs(S,1e18);
		flw+=t; fee+=t*(dis[T]+h[T]);
		for (int i=1;i<=T;i++) if (dis[i]!=INF) h[i]+=dis[i];
	}
	
	if (flw||fee<-1e8) return 1e18;
	
	for (int i=1;i<=m;i++){
		ll &l=r[i].l,&s=r[i].s,&t=r[i].t;
		int p=i<<2; p-=2;
		V[i]=edge[p^1].v;
		p+=2;
		U[i]=edge[p^1].v;
	}
	
	return fee;
}

}

namespace C{  //construct

struct Edge{
	int to,nxt; ll v;
}edge[50010];  //4n+4m
int cnt,last[210];
inline void addedge(int x,int y,ll v){
	edge[++cnt]=(Edge){y,last[x],v},last[x]=cnt;
}
int K;
ll A[110],B[110];

int que[220],hd,tl;
bool inq[210];
ll dis[210];
void work(){
	K=n<<1|1;
	cnt=0; for (int i=1;i<=K;i++) last[i]=0;
	for (int i=1;i<=n;i++) A[i]=B[i]=0;
	//init
	
	for (int i=1;i<=n;i++) addedge(K,i,0),addedge(K,i+n,0);
	for (int i=1;i<=m;i++){
		int &u=r[i].u,&v=r[i].v;
		ll &l=r[i].l,&s=r[i].s,&t=r[i].t;
		addedge(u,v+n,-t+l);
		addedge(v+n,u,s-l);
		A[u]+=U[i]-V[i];
		B[v]+=-U[i]+V[i];
		if (U[i]) addedge(v+n,u,t-l);
		if (V[i]) addedge(u,v+n,-s+l);
	}
	for (int i=1;i<=n;i++){
		if (A[i]!=O[i]) addedge(i,K,0);
		if (B[i]!=-I[i]) addedge(i+n,K,0);
	}
	
	hd=tl=0;
	for (int i=1;i<=K;i++) inq[i]=0,dis[i]=-1e18;
	que[++tl]=K; dis[K]=0;
	while (hd^tl){
		int u=que[hd=hd==210?1:hd+1],v;
		inq[u]=0;
		for (int i=last[u];i;i=edge[i].nxt)
			if (v=edge[i].to,dis[u]+edge[i].v>dis[v]){
				dis[v]=dis[u]+edge[i].v;
				if (!inq[v]) inq[v]=1,que[tl=tl==210?1:tl+1]=v;
			}
	}
	
	for (int i=1;i<=n;i++) printf("%lld ",dis[i]); puts("");
	for (int i=1;i<=n;i++) printf("%lld ",dis[i+n]); puts("");
}

}

void init(){}  //init finished
void solve(){
	n=read(),m=read();
	for (int i=1;i<=m;i++){
		int &u=r[i].u,&v=r[i].v;
		ll &l=r[i].l,&s=r[i].s,&t=r[i].t;
		u=read(),v=read(),l=read(),s=read(),t=read();
	}
	ll res=F::work();
	if (res==1e18) return puts("Unlike"),void();
	for (int i=1;i<=m;i++) res+=r[i].l;
	printf("%lld\n",res);
	C::work();
	
}
int main()
{
	for (int T=read();T--;) init(),solve();
	return 0;
}