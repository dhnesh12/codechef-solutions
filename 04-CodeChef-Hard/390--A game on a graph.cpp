#include<bits/stdc++.h>
using namespace std;
int n,m;
#define Maxn 2005
#define E 4000010
int head[Maxn],v[E],nxt[E],tot=0;
inline void add_edge(int s,int e){
	tot++;v[tot]=e;nxt[tot]=head[s];head[s]=tot;
	tot++;v[tot]=s;nxt[tot]=head[e];head[e]=tot;
}

int mate[Maxn],link[Maxn],fa[Maxn],vis[Maxn];
int Q[Maxn<<1],hd,tl;
int ss[Maxn],T;
int getroot(int x){
	if(fa[x]!=x)fa[x]=getroot(fa[x]);
	return fa[x];
}
int LCA(int a,int b){
	T++;
	while(ss[a]^T){
		if(a){ss[a]=T;a=getroot(link[mate[a]]);}
		swap(a,b);
	}
}
void Flower(int x,int y,int p){
	while(getroot(x)^p){
		link[x]=y;
		fa[y=mate[x]]=fa[x]=p;
		if(vis[y]==1)vis[Q[tl++]=y]=2;
		x=link[y];
	}
}
bool ans[Maxn];
void Match(int x,int ty){
	hd=tl=0;
	for(int i=1;i<=n;++i)vis[fa[i]=i]=0;
	Q[tl++]=x;
	vis[x]=2;
	while(hd<tl){
		int u=Q[hd];hd++;
		if(ty)ans[u]=true;
		for(int i=head[u];i;i=nxt[i])
			if(!vis[v[i]]){
				link[v[i]]=u;
				vis[v[i]]=1;
				if(!mate[v[i]]){
					int node=v[i];
					while(node){
						int pre=mate[link[node]];
						mate[node]=link[node];
						mate[link[node]]=node;
						node=pre;
					}
					return;
				}else vis[Q[tl++]=mate[v[i]]]=2;
			}else if(vis[v[i]]==2&&getroot(u)!=getroot(v[i])){
				int p=LCA(u,v[i]);
				Flower(u,v[i],p);
				Flower(v[i],u,p);
			}
	}
}

inline void rd(int &x){
	x=0;char ch=getchar();
	while(ch<'0'||ch>'9')ch=getchar();
	while(ch>='0'&&ch<='9'){
		x=x*10+ch-'0';
		ch=getchar();
	}
}

int main(){
	int cas;rd(cas);
	while(cas--){
		rd(n);rd(m);
		memset(head,0,sizeof(int)*(n+1));tot=0;
		memset(mate,0,sizeof(int)*(n+1));
		memset(ans,false,sizeof(bool)*(n+1));
		int s,e;
		for(int i=1;i<=m;++i){
			rd(s);rd(e);
			add_edge(s,e);
			if(!mate[s]&&!mate[e]){
				mate[s]=e;
				mate[e]=s;
			}
		}
		for(int i=1;i<=n;++i)
			if(!mate[i]){
				Match(i,0);
			}
		for(int i=1;i<=n;++i)
			if(!mate[i])Match(i,1);
		int res=0;
		for(int i=1;i<=n;++i)
			if(ans[i])res++;
		printf("%d\n",res);
	}
	return 0;
}