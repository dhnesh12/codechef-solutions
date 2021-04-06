#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=25;
const int maxs=505;
const int maxp=1005;
const int maxe=50005;
const int INF=5e7+5;
int n,m,K,ans=INF;
int ID[25][25];
int A[maxp],B[maxp],C[maxp];
int q[maxp],P[maxn];
int tot;
int dx[4]={-1,0,1,0},dy[4]={0,1,0,-1};
int h[maxp],last[maxe],to[maxe];
int F[maxp][maxs],tempans[maxs];
int vis[maxp];
void add(int x,int y)
{
	to[++tot]=y,last[tot]=h[x],h[x]=tot;
}
void spfa(int S)
{
	int head=1,tail=1;
	for(int i=1;i<=n*m;++i) 
	  q[++tail]=i,vis[i]=1;
	while(head<=tail){
		int u=q[head];
		++head,vis[u]=0;
		for(int i=h[u];i;i=last[i]){
			int v=to[i];
			if(!~A[v]) continue;
			if(F[v][S]>F[u][S]+B[v]){
				F[v][S]=F[u][S]+B[v];
				if(!vis[v]) vis[v]=1,q[++tail]=v;
			}
		}
	}
}
int main()
{
	srand(19260817);
	scanf("%d%d%d",&n,&m,&K);
	int cnt=0;
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=m;++j){
	  	ID[i][j]=++cnt;
	  	scanf("%d",&A[cnt]);
	  }
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=m;++j)
	    scanf("%d",&B[ID[i][j]]);
	for(int i=1;i<=n;++i)
	  for(int j=1;j<=m;++j)
	  	for(int k=0;k<4;++k){
	  		int vx=i+dx[k],vy=j+dy[k];
	  		int u=ID[i][j],v=ID[vx][vy];
	  		if(vx<1||vx>n||vy<1||vy>m||!~A[u]||!~A[v]) continue;
	  		add(u,v);
		  }
	P[1]=1;
	for(int i=2;i<=K+1;++i) P[i]=P[i-1]<<1;
	int T=350;
	while(T--){
		for(int i=1;i<=cnt;++i) vis[i]=0;
		int now=0;
		for(int S=0;S<P[K+1];++S)
		  for(int i=1;i<=cnt;++i) F[i][S]=INF;
		for(int i=1;i<=cnt;++i) 
		  if(~A[i]) F[i][0]=B[i];
		for(int i=1;i<=cnt;++i){
			if(!(~A[i])||!A[i]) continue;
			if(!vis[A[i]]){
				if(now==K) vis[A[i]]=(rand()%K)+1;
				else vis[A[i]]=++now;
			}
			C[i]=vis[A[i]];
			F[i][P[C[i]]]=B[i];
		}
		for(int S=0;S<P[K+1];++S){
			for(int i=1;i<=cnt;++i){
				for(int s=S&(S-1);s;s=S&(s-1)){
					F[i][S]=min(F[i][S],F[i][s]+F[i][S^s]-B[i]);
				}
			}
			spfa(S);
		}
		for(int i=1;i<=cnt;++i){
			ans=min(ans,F[i][P[K+1]-1]);
		}
	}
	if(ans<INF) printf("%d",ans);
	else printf("-1");
	return 0;
}