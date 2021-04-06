#include<bits/stdc++.h>
using namespace std;
const int N=5+1e5;
struct Graph{
	struct Edge{ int to,nxt,c; }edge[N*2];
	int head[N],top;
	Graph(){memset(head,-1,sizeof(head)),top=-1;}
	inline void add(int x,int y,int c){
		edge[++top]=(Edge){y,head[x],c};
		head[x]=top;
	}
}G;
inline void add2(Graph& G,int x,int y,int c){
//	printf("(%d %d %d)",x,y,c);
	G.add(x,y,c),G.add(y,x,0); 
}
namespace FLOW{
	int iter[N],lev[N];
	bool bfs(Graph& G,int s,int t,int n){
		memcpy(iter,G.head,sizeof(int)*(n+1));
		memset(lev,0,sizeof(int)*(n+1));
		static int q[N],left,right;
		left=right=1; q[right++]=t; lev[t]=1;
		while(left!=right){
			int x=q[left++];
			for(int j=G.head[x];~j;j=G.edge[j].nxt){
				int y=G.edge[j].to;
				if(G.edge[j^1].c>0&&lev[y]==0)
					lev[y]=lev[x]+1,q[right++]=y;
			}
		}
		return lev[s]>0;
	}
	int dfs(Graph& G,int x,int t,int mx){
		if(x==t) return mx;
		int ret=0;
		for(int& j=iter[x];~j;j=G.edge[j].nxt){
			int y=G.edge[j].to;
			if(G.edge[j].c>0&&lev[y]==lev[x]-1){
				int d=dfs(G,y,t,min(mx-ret,G.edge[j].c));
				G.edge[j].c-=d; G.edge[j^1].c+=d;
				ret+=d; if(mx==ret) break;
			}
		}
		return ret;
	}
	int dinic(Graph& G,int s,int t,int n,int mx){
		int ret=0;
		while(ret<mx&&bfs(G,s,t,n)) ret+=dfs(G,s,t,mx-ret);
		return ret;
	}
}
int id[105][105],x[105][105],top=0;
int main(){
	int n,m,k,ans=0; scanf("%d%d%d",&n,&m,&k);
	int s=++top,t=++top;
	for(int i=1;i<=n;++i){
		for(int j=1;j<m;++j)
			id[i][j]=++top;
		for(int j=1;j<=m;++j){
			scanf("%d",&x[i][j]);
			int u=j==1?s:id[i][j-1],v=j==m?t:id[i][j];
			add2(G,u,v,x[i][j]==-1?1e9:100-x[i][j]);
		}
		ans+=100;
	}
	for(int i=1;i<=k;++i){
		int a,b; scanf("%d%d",&a,&b);
		for(int j=1;j<=m;++j){
			int u=j==1?s:id[a][j-1];
			int v=j==m?t:id[b][j];
			add2(G,u,v,1e9);
		}
	}
	ans-=FLOW::dinic(G,s,t,top,1e9);
//	printf("<%d>",ans);
	printf("%.2lf\n",(double)ans/n);
	return 0;
}