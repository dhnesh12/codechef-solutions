#include<stdio.h>
#include<algorithm>
#include<vector>
#include<string.h>
using namespace std;
typedef long long ll;
const int inf=2147483647;
int n;
struct pr{
	int y,v;
	pr(int y=0,int v=0):y(y),v(v){}
};
int f1[100010],g1[100010],f2[100010],g2[100010],bl[100010],w1,w2,*d2;
//f1:A1,g1:B1,bl:A1 or B1
ll ans;
#define ok to[i]!=fa&&!vis[i]
namespace vt{
	vector<int>g[50010];
	int h[100010],nex[200010],to[200010],v[200010],M,N;
	void ins(int a,int b,int c){
		M++;
		to[M]=b;
		v[M]=c;
		nex[M]=h[a];
		h[a]=M;
	}
	void add(int a,int b,int c){
		ins(a,b,c);
		ins(b,a,c);
	}
	void dfs(int x){
		int las=0;
		for(int&y:g[x]){
			h[y]=0;
			if(las){
				h[++N]=0;
				add(las,N,0);
				add(N,y,d2[y]-d2[x]);
				las=N;
			}else{
				add(x,y,d2[y]-d2[x]);
				las=x;
			}
			dfs(y);
		}
	}
	bool vis[200010];
	int siz[100010];
	void dfs1(int fa,int x){
		siz[x]=1;
		for(int i=h[x];i;i=nex[i]){
			if(ok){
				dfs1(x,to[i]);
				siz[x]+=siz[to[i]];
			}
		}
	}
	int n,mn,cn;
	void dfs2(int fa,int x){
		for(int i=h[x];i;i=nex[i]){
			if(ok){
				if(abs(n-siz[to[i]]*2)<mn){
					mn=abs(n-siz[to[i]]*2);
					cn=i;
				}
				dfs2(x,to[i]);
			}
		}
	}
	int p1[50010],p2[50010],n1,n2;
	//p1:A2A1,p2:A2B1
	void dfs3(int fa,int x,int d){
		f2[x]=d;
		if(bl[x]==1)p1[++n1]=x;
		if(bl[x]==2)p2[++n2]=x;
		for(int i=h[x];i;i=nex[i]){
			if(ok)dfs3(x,to[i],d+v[i]);
		}
	}
	int p3[50010],p4[50010],n3,n4;
	//p3:B2B1,p4:B2A1
	void dfs4(int fa,int x,int d){
		g2[x]=d;
		if(bl[x]==2)p3[++n3]=x;
		if(bl[x]==1)p4[++n4]=x;
		for(int i=h[x];i;i=nex[i]){
			if(ok)dfs4(x,to[i],d+v[i]);
		}
	}
	int id[50010];
	ll s1[50010],s2[50010],c[50010];
	void solve(int x){
		int y,i,t,M;
		dfs1(0,x);
		n=siz[x];
		mn=inf;
		cn=0;
		dfs2(0,x);
		if(!cn)return;
		vis[cn]=vis[cn^1]=1;
		x=to[cn];
		y=to[cn^1];
		w2=v[cn];
		n1=n2=0;
		dfs3(y,x,0);
		n3=n4=0;
		dfs4(x,y,0);
		for(i=1;i<=n3;i++)id[i]=g1[p3[i]]-g2[p3[i]];
		sort(id+1,id+n3+1);
		M=unique(id+1,id+n3+1)-id-1;
		memset(s1,0,(M+1)<<3);
		memset(s2,0,(M+1)<<3);
		memset(c,0,(M+1)<<3);
		for(i=1;i<=n3;i++){
			t=lower_bound(id+1,id+M+1,g1[p3[i]]-g2[p3[i]])-id;
			s1[t]+=g1[p3[i]];
			s2[t]+=g2[p3[i]];
			c[t]++;
		}
		for(i=1;i<=M;i++){
			s1[i]+=s1[i-1];
			s2[i]+=s2[i-1];
			c[i]+=c[i-1];
		}
		for(i=1;i<=n1;i++){
			t=upper_bound(id+1,id+M+1,f2[p1[i]]+w2-f1[p1[i]]-w1)-id-1;
			ans+=(f1[p1[i]]+w1)*c[t]+s1[t];
			ans+=(f2[p1[i]]+w2)*(c[M]-c[t])+s2[M]-s2[t];
		}
		for(i=1;i<=n4;i++)id[i]=f1[p4[i]]-g2[p4[i]];
		sort(id+1,id+n4+1);
		M=unique(id+1,id+n4+1)-id-1;
		memset(s1,0,(M+1)<<3);
		memset(s2,0,(M+1)<<3);
		memset(c,0,(M+1)<<3);
		for(i=1;i<=n4;i++){
			t=lower_bound(id+1,id+M+1,f1[p4[i]]-g2[p4[i]])-id;
			s1[t]+=f1[p4[i]];
			s2[t]+=g2[p4[i]];
			c[t]++;
		}
		for(i=1;i<=M;i++){
			s1[i]+=s1[i-1];
			s2[i]+=s2[i-1];
			c[i]+=c[i-1];
		}
		for(i=1;i<=n2;i++){
			t=upper_bound(id+1,id+M+1,f2[p2[i]]+w2-g1[p2[i]]-w1)-id-1;
			ans+=(g1[p2[i]]+w1)*c[t]+s1[t];
			ans+=(f2[p2[i]]+w2)*(c[M]-c[t])+s2[M]-s2[t];
		}
		solve(x);
		solve(y);
	}
	void clear(int fa,int x){
		for(int&y:g[x]){
			if(y!=fa)clear(x,y);
		}
		g[x].clear();
	}
	void gao(int rt){
		h[rt]=0;
		M=1;
		N=::n;
		dfs(rt);
		for(int i=1;i<=M;i++)vis[i]=0;
		solve(rt);
		clear(0,rt);
	}
}
namespace t2{
	int h[50010],nex[100010],to[100010],v[100010],M;
	void add(int a,int b,int c){
		M++;
		to[M]=b;
		v[M]=c;
		nex[M]=h[a];
		h[a]=M;
	}
	int dis[50010],in[50010],dep[50010],mn[100010][17],lg[100010];
	void dfs(int fa,int x){
		in[x]=++M;
		mn[M][0]=x;
		dep[x]=dep[fa]+1;
		for(int i=h[x];i;i=nex[i]){
			if(to[i]!=fa){
				dis[to[i]]=dis[x]+v[i];
				dfs(x,to[i]);
				mn[++M][0]=x;
			}
		}
	}
	int qmin(int x,int y){return dep[x]<dep[y]?x:y;}
	int query(int l,int r){
		int k=lg[r-l+1];
		return qmin(mn[l][k],mn[r-(1<<k)+1][k]);
	}
	int lca(int x,int y){
		if(in[x]>in[y])swap(x,y);
		return query(in[x],in[y]);
	}
	void pre(){
		int i,j,x,y,z;
		for(i=1;i<=n;i++)h[i]=0;
		M=0;
		for(i=1;i<n;i++){
			scanf("%d%d%d",&x,&y,&z);
			add(x,y,z);
			add(y,x,z);
		}
		M=0;
		dfs(0,1);
		for(i=2;i<=M;i++)lg[i]=lg[i>>1]+1;
		for(j=1;j<=lg[M];j++){
			for(i=1;i+(1<<j)-1<=M;i++)mn[i][j]=qmin(mn[i][j-1],mn[i+(1<<(j-1))][j-1]);
		}
	}
	int p[50010],st[50010],tp;
	int cmp(int x,int y){return in[x]<in[y];}
	void insert(int x){
		if(!tp){
			st[++tp]=x;
			return;
		}
		int l=lca(st[tp],x);
		while(tp>1&&dep[l]<dep[st[tp-1]]){
			vt::g[st[tp-1]].push_back(st[tp]);
			tp--;
		}
		if(dep[st[tp]]>dep[l])vt::g[l].push_back(st[tp--]);
		if(dep[st[tp]]<dep[l])st[++tp]=l;
		st[++tp]=x;
	}
	void build(){
		int i;
		sort(p+1,p+M+1,cmp);
		tp=0;
		for(i=1;i<=M;i++)insert(p[i]);
		for(i=1;i<tp;i++)vt::g[st[i]].push_back(st[i+1]);
		vt::gao(st[1]);
	}
}
namespace t1{
	vector<pr>g[50010];
	int h[100010],nex[200010],to[200010],v[200010],M,N;
	void ins(int a,int b,int c){
		M++;
		to[M]=b;
		v[M]=c;
		nex[M]=h[a];
		h[a]=M;
	}
	void add(int a,int b,int c){
		ins(a,b,c);
		ins(b,a,c);
	}
	void dfs(int fa,int x){
		int las=0;
		for(pr&t:g[x]){
			if(t.y!=fa){
				if(las){
					add(las,++N,0);
					add(N,t.y,t.v);
					las=N;
				}else{
					add(x,t.y,t.v);
					las=x;
				}
				dfs(x,t.y);
			}
		}
	}
	bool vis[200010];
	void pre(){
		int i,x,y,z;
		for(i=1;i<=n;i++)g[i].clear();
		for(i=1;i<=n*2;i++)h[i]=0;
		M=1;
		for(i=1;i<n;i++){
			scanf("%d%d%d",&x,&y,&z);
			g[x].push_back(pr(y,z));
			g[y].push_back(pr(x,z));
		}
		N=n;
		dfs(0,1);
		for(i=1;i<=M;i++)vis[i]=0;
	}
	int siz[100010];
	void dfs1(int fa,int x){
		siz[x]=1;
		for(int i=h[x];i;i=nex[i]){
			if(ok){
				dfs1(x,to[i]);
				siz[x]+=siz[to[i]];
			}
		}
	}
	int n,mn,cn;
	void dfs2(int fa,int x){
		if(x<=::n)t2::p[++t2::M]=x;
		for(int i=h[x];i;i=nex[i]){
			if(ok){
				if(abs(n-siz[to[i]]*2)<mn){
					mn=abs(n-siz[to[i]]*2);
					cn=i;
				}
				dfs2(x,to[i]);
			}
		}
	}
	int*p,f;
	void dfs3(int fa,int x,int d){
		p[x]=d;
		if(x<=::n)bl[x]=f;
		for(int i=h[x];i;i=nex[i]){
			if(ok)dfs3(x,to[i],d+v[i]);
		}
	}
	void dfs4(int fa,int x){
		bl[x]=0;
		for(int i=h[x];i;i=nex[i]){
			if(ok)dfs4(x,to[i]);
		}
	}
	void solve(int x){
		int y;
		dfs1(0,x);
		n=siz[x];
		mn=inf;
		cn=0;
		t2::M=0;
		dfs2(0,x);
		if(!cn)return;
		vis[cn]=vis[cn^1]=1;
		x=to[cn];
		y=to[cn^1];
		w1=v[cn];
		p=f1;
		f=1;
		dfs3(y,x,0);
		p=g1;
		f=2;
		dfs3(x,y,0);
		t2::build();
		dfs4(0,x);
		dfs4(0,y);
		solve(x);
		solve(y);
	}
}
void work(){
	scanf("%d",&n);
	t1::pre();
	t2::pre();
	ans=0;
	t1::solve(1);
	printf("%lld\n",ans);
}
int main(){
	d2=t2::dis;
	int T;
	scanf("%d",&T);
	while(T--)work();
}