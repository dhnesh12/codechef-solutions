#include<bits/stdc++.h>
#define ll long long
#define ld long double
#define ull unsigned ll
#define uint unsigned int
#define db double
#define pint pair<int,int>
#define mk make_pair
#define pb push_back
#define eb emplace_back
#define ins insert
#define fi first
#define se second
#define Rep(x,y,z) for(int x=y;x<=z;x++)
#define Red(x,y,z) for(int x=y;x>=z;x--)
using namespace std;
const int MAXN=6e5+5,Mod=1e9+7;const db pie=acos(-1);
char buf[1<<12],*pp1=buf,*pp2=buf,nc;int ny;
inline char gc() {return pp1==pp2&&(pp2=(pp1=buf)+fread(buf,1,1<<12,stdin),pp1==pp2)?EOF:*pp1++;}
//inline char gc(){return getchar();}
inline int read(){
	int x=0;for(ny=1;nc=gc(),(nc<48||nc>57)&&nc!=EOF;)if(nc==45)ny=-1;if(nc<0)return nc;
	for(x=nc-48;nc=gc(),47<nc&&nc<58&&nc!=EOF;x=(x<<3)+(x<<1)+(nc^48));return x*ny;
}
inline int Fp(int x,int k){int ans=1;for(;k;k>>=1,x=1ll*x*x%Mod)if(k&1)ans=1ll*ans*x%Mod;return ans;}
int n,Fac[MAXN],iFac[MAXN];ll cnt[MAXN];vector<int>G[MAXN];
void dfs(int x,int fa,int d){cnt[d]++;for(auto y:G[x])if(y!=fa)dfs(y,x,d+1);}
inline void Init(int n=6e5){
	Fac[0]=1;Rep(i,1,n)Fac[i]=1ll*Fac[i-1]*i%Mod;
	iFac[n]=Fp(Fac[n],Mod-2);Red(i,n,1)iFac[i-1]=1ll*iFac[i]*i%Mod;
}
struct cp{db x,y;cp(){}cp(db x,db y):x(x),y(y){}inline cp conj(){return cp(x,-y);}}w[2][MAXN],aa[MAXN],bb[MAXN],cc[MAXN],dd[MAXN];
inline cp operator+(cp a,cp b){return cp(a.x+b.x,a.y+b.y);}inline cp operator-(cp a,cp b){return cp(a.x-b.x,a.y-b.y);}
inline cp operator*(cp a,cp b){return cp(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
int r[MAXN];
inline int Trans(int n){
	int N,c;for(N=1,c=0;N<=n;N<<=1,c++);
	for(int i=0;i<N;i++)r[i]=(r[i>>1]>>1)|((i&1)<<(c-1)),w[0][i]=cp(cos(2*pie*i/N),sin(2*pie*i/N)),w[1][i]=cp(cos(2*pie*i/N),-sin(2*pie*i/N));
	return N;
}
inline void FFT(cp*F,int len,int opt){
	for(int i=0;i<len;i++)if(i<r[i])swap(F[i],F[r[i]]);
	for(int i=1,x=len>>1;i<len;i<<=1,x>>=1)
		for(int j=0;j<len;j+=i<<1)for(int k=0;k<i;k++){
			cp tt=w[opt][k*x]*F[i+j+k];F[i+j+k]=F[j+k]-tt,F[j+k]=F[j+k]+tt;
		}
	if(opt)for(int i=0;i<len;i++)F[i].x/=len,F[i].y/=len;
}
inline void MTT(int n,int*A,int*B,int*C){
	int N=Trans(n);
	for(int i=0;i<N>>1;i++)aa[i]=cp(A[i]>>15,A[i]&0x7fff),bb[i]=cp(B[i]>>15,B[i]&0x7fff),aa[i+(N>>1)]=bb[i+(N>>1)]=cp(0,0);
	FFT(aa,N,0),FFT(bb,N,0);
	for(int i=0,j;i<N;i++){j=(N-i)&(N-1);
		cp a=(aa[i]+aa[j].conj())*cp(0.5,0),b=(aa[i]-aa[j].conj())*cp(0,-0.5),c=(bb[i]+bb[j].conj())*cp(0.5,0),d=(bb[i]-bb[j].conj())*cp(0,-0.5);
		cc[i]=a*c+a*d*cp(0,1),dd[i]=b*c+b*d*cp(0,1);
	}
	FFT(cc,N,1),FFT(dd,N,1);
	for(int i=0;i<N;i++){
		int a=(ll)(cc[i].x+0.5)%Mod,b=(ll)(cc[i].y+0.5)%Mod,c=(ll)(dd[i].x+0.5)%Mod,d=(ll)(dd[i].y+0.5)%Mod;
		C[i]=(((ll)a<<30)+((ll)(b+c)<<15)+d)%Mod;
	}
}
int vis[MAXN],sz[MAXN],N,Min,rt;
inline void dfs(int x,int fa){int Max=0;sz[x]=1;for(auto y:G[x])if(y!=fa&&!vis[y])dfs(y,x),sz[x]+=sz[y],Max=max(Max,sz[y]);Max=max(Max,N-sz[x]),Max<Min?Min=Max,rt=x:0;}
inline int GetRt(int x,int Sz){return N=Sz,Min=1e9,dfs(x,0),rt;}
int a[MAXN],b[MAXN],c[MAXN];
void dfs1(int x,int fa,int d){a[d]++;for(auto y:G[x])if(y!=fa&&!vis[y])dfs1(y,x,d+1);}
inline void calc(int x,int fa,int d,int opt){
	dfs1(x,fa,d);
	Rep(i,0,sz[x])b[i]=a[i];MTT(2*sz[x],a,b,c);
	Rep(i,0,2*sz[x])cnt[i]+=opt*c[i];
	Rep(i,0,2*sz[x])a[i]=b[i]=0;
}
inline void Solve(int x,int N){
	x=GetRt(x,N),vis[x]=1,dfs(x,0);
	calc(x,0,0,1);for(auto y:G[x])if(!vis[y])calc(y,x,1,-1);
	for(auto y:G[x])if(!vis[y])Solve(y,sz[y]);
}
int main(){
//	freopen("std.in","r",stdin);
//	freopen("std.out","w",stdout);
	n=read(),Init();
	Rep(i,1,n-1){int x=read(),y=read();G[x].pb(y),G[y].pb(x);}
	Solve(1,n);Rep(i,0,n)cnt[i]%=Mod;memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
	Rep(i,0,n-1)a[i]=1ll*cnt[i]*Fac[n-i-1]%Mod,b[i]=iFac[i];MTT(2*n,a,b,c);
	Rep(i,0,n-1)cout<<1ll*c[n-i-1]*Fac[n-i-1]%Mod*iFac[n-1]%Mod<<' ';
	return 0;
}



