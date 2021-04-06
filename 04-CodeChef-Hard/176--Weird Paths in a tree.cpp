#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline char getch(){
	static char buf[10000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,10000,stdin),p1==p2)?EOF:*p1++;
}
#define Getc getch
inline ll read(){
	ll s=0,f=1;char ch=Getc();
	while(ch<'0'||ch>'9')f=(ch=='-'?-1:1),ch=Getc();
	while(ch>='0'&&ch<='9')s=s*10+ch-'0',ch=Getc();
	return s*f;
}
#define filename "path"
void File(){
	freopen(filename"22.in","r",stdin);
	freopen(filename".out","w",stdout);
}
const int MaxN=1e5+5;
struct Edge{int to,nxt;};
Edge e[MaxN<<1];
int Head[MaxN],cnt;
void Add_Edge(int x,int y){
	e[++cnt]=(Edge){y,Head[x]};
	Head[x]=cnt;
}
int n,Mod,a[MaxN],Q;
namespace BF{
	ll f[1001][1001][2],g[1001][1001];
	ll h[1001][1001][2];
	void Dfs(int x,int r,int fa){
		g[r][x]=f[r][x][0]=f[r][x][1]=h[r][x][0]=h[r][x][1]=0;
		for(int i=Head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(y==fa)continue;
			Dfs(y,r,x);
			g[r][x]=(g[r][x]+g[r][y])%Mod;
			if(a[y]>a[x]){
				g[r][x]=(g[r][x]+(h[r][x][0]+a[x])*(f[r][y][1]+1)%Mod+(f[r][x][0]+1)*(h[r][y][1]+a[y])%Mod)%Mod;
				f[r][x][0]=(f[r][x][0]+f[r][y][1]+1)%Mod;
				h[r][x][0]=(h[r][x][0]+h[r][y][1]+a[x]*f[r][y][1]%Mod+a[x]+a[y])%Mod;
			}else{
				g[r][x]=(g[r][x]+(h[r][x][1]+a[x])*(f[r][y][0]+1)%Mod+(f[r][x][1]+1)*(h[r][y][0]+a[y])%Mod)%Mod;
				f[r][x][1]=(f[r][x][1]+f[r][y][0]+1)%Mod;
				h[r][x][1]=(h[r][x][1]+h[r][y][0]+a[x]*f[r][y][0]%Mod+a[x]+a[y])%Mod;
			}
		}
	}
	void Main(){
		for(int i=1;i<=n;i++)Dfs(i,i,0);
		Q=read();
		while(Q--){
			int R,S;
			R=read(),S=read();
			printf("%lld\n",g[R][S]);
		}
	}
}
namespace TR{
	int top[MaxN],prt[MaxN],dep[MaxN];
	int son[MaxN],siz[MaxN];
	ll f[MaxN][2],g[MaxN],h[MaxN][2],b[MaxN];
	ll gf[MaxN],ff[MaxN][2],hf[MaxN][2];
	int F[MaxN][20];
	void Dfs1(int x,int fa){
		siz[x]=1;
		dep[x]=dep[fa]+1;
		prt[x]=fa;
		g[x]=f[x][0]=f[x][1]=h[x][0]=h[x][1]=0;
		for(int i=Head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(y==fa)continue;
			Dfs1(y,x);
			siz[x]+=siz[y];
			if(siz[y]>siz[son[x]])son[x]=y;
			g[x]=(g[x]+g[y])%Mod;
			if(b[y]>b[x]){
				g[x]=(g[x]+(h[x][0]+a[x])*(f[y][1]+1)%Mod+(f[x][0]+1)*(h[y][1]+a[y])%Mod)%Mod;
				f[x][0]=(f[x][0]+f[y][1]+1)%Mod;
				h[x][0]=(h[x][0]+h[y][1]+a[x]*f[y][1]%Mod+a[x]+a[y])%Mod;
			}else{
				g[x]=(g[x]+(h[x][1]+a[x])*(f[y][0]+1)%Mod+(f[x][1]+1)*(h[y][0]+a[y])%Mod)%Mod;
				f[x][1]=(f[x][1]+f[y][0]+1)%Mod;
				h[x][1]=(h[x][1]+h[y][0]+a[x]*f[y][0]%Mod+a[x]+a[y])%Mod;
			}
		}
	}
	void pushup(int x,int y){
		gf[x]=(gf[x]+gf[y]);
		int xx=prt[x],yy=prt[y];
		if(b[yy]>b[xx]){
			gf[x]=(gf[x]+(hf[x][0]+a[xx])*(ff[y][1]+1)%Mod+(ff[x][0]+1)*(hf[y][1]+a[yy])%Mod)%Mod;
			ff[x][0]=(ff[x][0]+ff[y][1]+1)%Mod;
			hf[x][0]=(hf[x][0]+hf[y][1]+a[xx]*ff[y][1]%Mod+a[xx]+a[yy])%Mod;
		}else{
			gf[x]=(gf[x]+(hf[x][1]+a[xx])*(ff[y][0]+1)%Mod+(ff[x][1]+1)*(hf[y][0]+a[yy])%Mod)%Mod;
			ff[x][1]=(ff[x][1]+ff[y][0]+1)%Mod;
			hf[x][1]=(hf[x][1]+hf[y][0]+a[xx]*ff[y][0]%Mod+a[xx]+a[yy])%Mod;
		}
	}
	void Dfs2(int x,int fa,int tp){
		top[x]=tp;
		for(int i=Head[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(y==fa)continue;
			ff[y][0]=f[x][0];ff[y][1]=f[x][1];
			hf[y][0]=h[x][0];hf[y][1]=h[x][1];
			gf[y]=(g[x]-g[y]+Mod)%Mod;
			if(b[y]>b[x]){
				ff[y][0]=(ff[y][0]-(f[y][1]+1)+Mod)%Mod;
				hf[y][0]=(hf[y][0]-(h[y][1]+a[x]*f[y][1]%Mod+a[x]+a[y])%Mod+Mod)%Mod;
				gf[y]=(gf[y]-((hf[y][0]+a[x])*(f[y][1]+1)%Mod+(ff[y][0]+1)*(h[y][1]+a[y])%Mod)%Mod+Mod)%Mod;
			}else{
				ff[y][1]=(ff[y][1]-(f[y][0]+1)+Mod)%Mod;
				hf[y][1]=(hf[y][1]-(h[y][0]+a[x]*f[y][0]%Mod+a[x]+a[y])%Mod+Mod)%Mod;
				gf[y]=(gf[y]-((hf[y][1]+a[x])*(f[y][0]+1)%Mod+(ff[y][1]+1)*(h[y][0]+a[y])%Mod)%Mod+Mod)%Mod;
			}
			if(prt[x])pushup(y,x);
			if(y==son[x])Dfs2(y,x,tp);
			else Dfs2(y,x,y);
		}
	}
	int Lca(int x,int y){
		for(;top[x]!=top[y];x=prt[top[x]])
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		return dep[x]<dep[y]?x:y;
	}
	int getSon(int x,int y){
		for(int j=19;j>=0;j--){
			if(F[y][j]&&dep[F[y][j]]>dep[x])y=F[y][j];
		}
		return y;
	}
	ll Ask(int R,int S){
		int lca;
		if(R==S)return g[1];
		lca=Lca(R,S);
		if(lca!=S)return g[S];
		R=getSon(S,R);
		return gf[R];
	}
	void Main(){
		for(int i=1;i<=n;i++)b[i]=a[i],a[i]%=Mod;
		Dfs1(1,0);
		Dfs2(1,0,1);
		for(int i=1;i<=n;i++)F[i][0]=prt[i];
		for(int j=1;j<20;j++)
		for(int i=1;i<=n;i++)F[i][j]=F[F[i][j-1]][j-1];
		Q=read();//Q=1;
		while(Q--){
			int R,S;
			R=read(),S=read();
			printf("%lld\n",Ask(R,S));
		}
	}
}
int main(){
//	File();
	n=read(),Mod=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	TR::Main();
//	if(n<=1000)BF::Main();
//	else TR::Main();
	return 0;
}
/*
6 100000
1 2 3 4 5 6
1 2
2 5
1 4
3 4
1 6
5
5 2
3 1
1 6
2 4
5 1
*/