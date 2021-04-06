#include<bits/stdc++.h>
#define ll long long
#define re register
#define pb push_back
#define ull unsigned ll
using namespace std;
inline int read(){
	int s=0,t=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')t=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*t;
}
const int N=5e5+5;
int n,m;
vector<int> E0[N];


int Num,Lg[N],d[N],g[N],pos[N],p[N][19],fp[N][19],dfn[N];
void Pre(int x,int f){
	d[x]=d[f]+1,fp[x][0]=f;
	g[pos[x]=++Num]=x,dfn[x]=++dfn[0];
	for(int i=1;i<=18;i++)fp[x][i]=fp[fp[x][i-1]][i-1];
	for(auto y:E0[x])if(y^f)Pre(y,x),g[++Num]=x;
}
int Lca(int x,int y){
	int l=pos[x],r=pos[y],k=0;
	if(l>r)swap(l,r);k=Lg[r-l+1];
	int a=p[l][k],b=p[r-(1<<k)+1][k];
	return (d[a]<d[b])?a:b;
}
int Get(int x,int k){
	for(int i=18;i>=0;i--)if(k>>i&1)x=fp[x][i];
	return x;
}
int Dis(int x,int y){return d[x]+d[y]-2*d[Lca(x,y)];}
void Prepare(){
	Pre(1,0);
	for(int i=2;i<=Num;i++)Lg[i]=Lg[i>>1]+1;
	for(int i=1;i<=Num;i++)p[i][0]=g[i];
	for(int j=1;j<=18;j++)
	for(int i=1;i+(1<<j)-1<=Num;i++){
		int x=p[i][j-1],y=p[i+(1<<j-1)][j-1];
		p[i][j]=(d[x]<d[y])?x:y;
	}
}


int Root,sz[N],vis[N],prt[N];
vector<int> D0[N],D1[N];
void Getrt(int x,int f,int Siz){
	int tmp=0;sz[x]=1;
	for(auto y:E0[x])if((y^f)&&!vis[y])
	Getrt(y,x,Siz),sz[x]+=sz[y],tmp=max(tmp,sz[y]);
	if(max(Siz-sz[x],tmp)*2<=Siz)Root=x;
}
void Getdep(int x,int f,int d,vector<int>&t){
	sz[x]=1;if(x<=n){while(t.size()<=d)t.pb(0);t[d]++;}
	for(auto y:E0[x])if((y^f)&&!vis[y])
	Getdep(y,x,d+1,t),sz[x]+=sz[y];
}
void Calc(int x,int f,int d,vector<int>&t){
	Getdep(x,f,d,t);
	for(int i=1;i<t.size();i++)t[i]+=t[i-1];
}
void Solve(int x,int f){
	vis[x]=1,prt[x]=f,Calc(x,0,0,D0[x]);
	for(auto y:E0[x])if(!vis[y]){
		Getrt(y,0,sz[y]),Calc(y,x,1,D1[Root]);
		Solve(Root,x);
	}
}
int Ask(vector<int>&t,int d){
	if(!t.size()||d<0)return 0;
	return t[min(d,(int)t.size()-1)];
}
int Query(int x,int r){
	int res=0;
	for(int y=x,z=0;y;y=prt[z=y]){
		res+=Ask(D0[y],r-Dis(x,y));
		if(z)res-=Ask(D1[z],r-Dis(x,y));
	}return res;
}


int a[N],s[N],R[N];ll Ans;
vector<int> E1[N],Point;
bool cmp(int x,int y){return dfn[x]<dfn[y];}
void Build(){
	int top=0;
	sort(a+1,a+m+1,cmp),s[top=1]=a[1];
	for(int i=2;i<=m;i++){
		int y=Lca(s[top],a[i]);
		while(top>1&&d[y]<=d[s[top-1]])E1[s[top-1]].pb(s[top]),top--;
		if(s[top]!=y)E1[y].pb(s[top]),s[top]=y,Point.pb(y);
		s[++top]=a[i];
	}
	while(top>1)E1[s[top-1]].pb(s[top]),top--; 
}
void DFS0(int x){for(auto y:E1[x])DFS0(y),R[x]=max(R[x],R[y]-(d[y]-d[x]));}
void DFS1(int x){for(auto y:E1[x])R[y]=max(R[y],R[x]-(d[y]-d[x])),DFS1(y);}
void DFS2(int x){
	if(~R[x])Ans+=Query(x,R[x]);
	for(auto y:E1[x]){
		if(R[x]+R[y]>=d[y]-d[x]){
			int z=Get(y,(d[y]-d[x]+R[y]-R[x])>>1);
			Ans-=Query(z,R[y]-(d[y]-d[z]));
		}DFS2(y);
	}
}
int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		E0[x].pb(n+i),E0[n+i].pb(x);
		E0[n+i].pb(y),E0[y].pb(n+i);
	}
	Prepare(),Getrt(1,0,2*n-1),Solve(Root,0);
	memset(R,-1,sizeof(R));
	for(int T=read();T;T--){
		m=read();
		for(int i=1;i<=m;i++){
			int x=read(),v=read();
			a[i]=x,R[x]=v*2,Point.pb(x);
		}
		Build(),DFS0(s[1]),DFS1(s[1]),DFS2(s[1]);
		cout<<Ans<<'\n';
		for(auto x:Point)E1[x].clear(),R[x]=-1;
		Point.clear(),Ans=0;
	}
	return 0;
}