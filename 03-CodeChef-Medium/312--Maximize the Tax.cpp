#include<bits/stdc++.h>
#define ll long long
#define re register
#define ull unsigned ll
using namespace std;
namespace Fread{
	const int SIZE=(1<<21)+1;
	char ibuf[SIZE],*iS,*iT,obuf[SIZE],*oS=obuf,*oT=oS+SIZE-1,c,qu[55];int f, qr;
	#define gc() (iS==iT?(iT=(iS=ibuf)+fread(ibuf,1,SIZE,stdin),(iS==iT?EOF:*iS++)):*iS++)
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout),oS=obuf;}
	inline void putc(char x){*oS++=x;if(oS==oT)flush();}
	template <class I>
	inline void read(I &x){
		for(f=1,c=gc();c<'0'||c>'9';c=gc())if(c== '-')f=-1;
		for(x=0;c<='9'&&c>='0';c=gc())x=(x<<3)+(x<<1)+(c & 15);x*=f;
	}
	template <class I>
	inline void print (I x){
		if(!x)putc('0');
		if(x<0)putc('-'),x=-x;
		while(x)qu[++qr]=x%10+'0',x/=10;
		while(qr)putc(qu[qr--]);
	}
	struct Flusher_{~Flusher_(){flush();}}io_flusher_;
}
using Fread::read;
using Fread::putc;
using Fread::print;

const int N=1e5+5;
const int M=205;
int n,m,K,cnt,top,tot,Num;
int b[N],h[N],dfn[N],low[N],s[N],vis[N],be[N],d[N];
ll Ans,f[N][M],g[M];
struct Node{int x,y;}p[N*2];
vector<int> S[N],G[N];
struct edge{int to,next;}e[N*2];
void Add(int x,int y){e[++cnt]=(edge){y,h[x]};h[x]=cnt;}
void Tarjan(int x){
	low[x]=dfn[x]=++tot;
	s[++top]=x,vis[x]=1;
	for(int i=h[x];i;i=e[i].next){
		int y=e[i].to;
		if(!dfn[y])Tarjan(y),low[x]=min(low[x],low[y]);
		else if(vis[y])low[x]=min(low[x],dfn[y]);
	}
	if(low[x]==dfn[x]){
		int y=0;Num++;
		while(y^x){
			y=s[top--],vis[y]=0;
			S[Num].push_back(b[y]),be[y]=Num;
		}
	}
}
void Pre(){
	cnt=1,Num=0,tot=0,Ans=0;
	for(int i=1;i<=n;i++){
		h[i]=low[i]=dfn[i]=d[i]=be[i]=0;
		S[i].clear(),G[i].clear();
	}
}
void Solve(vector<int> S,ll *f){
	int n=S.size(),m=min(K,n-1);
	sort(S.begin(),S.end());
	for(int i=0;i<=K;i++)g[i]=f[i];
	for(int i=0;i<=m;i++){
		ll v=1ll*(n-i)*S[i];
		for(int j=K;j>=i;j--)f[j]=max(f[j],g[j-i]+v);
	}
	for(int i=0;i<=K;i++)Ans=max(Ans,f[i]);
}
int main(){
//	freopen("tax.in","r",stdin);
//	freopen("tax.out","w",stdout);
	int T;read(T);
	while(T--){
		read(n),read(m),read(K),Pre();
		for(int i=1;i<=n;i++)read(b[i]);
		for(int i=1;i<=m;i++){
			read(p[i].x),read(p[i].y);
			Add(p[i].x,p[i].y);	
		}
		for(int i=1;i<=n;i++)if(!dfn[i])Tarjan(i);
		for(int i=1;i<=m;i++){
			int x=be[p[i].x],y=be[p[i].y];
			if(x^y)G[x].push_back(y),d[y]++;
		}
		queue<int> q;
		for(int i=1;i<=Num;i++){
			if(!d[i])q.push(i);
			for(int j=0;j<=K;j++)f[i][j]=0;
		}
		while(q.size()){
			int x=q.front();q.pop();
			Solve(S[x],f[x]);
			for(auto y:G[x]){
				for(int i=0;i<=K;i++)f[y][i]=max(f[y][i],f[x][i]);
				d[y]--;if(!d[y])q.push(y);
			}
		}
		printf("%lld\n",Ans%1000000021);
	}
	return 0;
}