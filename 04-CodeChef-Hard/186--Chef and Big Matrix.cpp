#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=210;
int w,b,n,D,mod,T;
struct pt{
	int x,y;
}p[N];
inline int dec(int x,int y){return (x-y<0)?x-y+mod:x-y;}
inline int add(int x,int y){return (x+y>=mod)?x+y-mod:x+y;}
inline int ksm(int x,int y){
	int ret=1;
	for(;y;y>>=1,x=1ll*x*x%mod) if(y&1) ret=1ll*ret*x%mod;
	return ret;
} 
namespace Lucas{
	typedef pair<int,int> pii;
	#define mp make_pair
	vector<pii> fac;
	int tp;
	int rep[10][N],k[10];
	unordered_map<int,int> mpf[10],mpg[10];
	inline void exgcd(int a,int b,int &x,int &y){
		if(!b){x=1;y=0;return ;}
		exgcd(b,a%b,x,y);
		int t=x;x=y;y=t-a/b*y;
	}
	inline int inv(int a,int mod){
		int x=0,y=0;
		exgcd(a,mod,x,y);
		return (x%mod+mod)%mod;
	}
	inline int F(int n,int p,int pk){
		if(!n) return 1;
		if(mpf[tp].count(n)) return mpf[tp][n];
		if(n<pk) return mpf[tp][n]=1ll*F(n/p,p,pk)*rep[tp][n%pk]%pk;
		else return mpf[tp][n]=1ll*F(n/p,p,pk)*ksm(rep[tp][pk],n/pk)%pk*rep[tp][n%pk]%pk; 
	}
	inline int G(int n,int p,int pk){
		if(n<p) return 0;
		if(mpg[tp].count(n)) return mpg[tp][n];
		return mpg[tp][n]=n/p+G(n/p,p,pk);
	}
	inline int binom_pk(int n,int m,int p,int pk){
		int c=G(n,p,pk)-G(m,p,pk)-G(n-m,p,pk);
		if(c>=k[tp]) return 0;
		int ret=1ll*F(n,p,pk)*inv(F(m,p,pk),pk)%pk*inv(F(n-m,p,pk),pk)%pk;
		return 1ll*ret*ksm(p,c)%pk;
	}
	inline int exLucas(int n,int m){
		if(n<0||n<m||m<0) return 0;
		int ans=0;
		for(int i=0;i<fac.size();++i){
			int p=fac[i].first,pk=fac[i].second;tp=i;
			int ret=binom_pk(n,m,p,pk);
			ans=add(ans,1ll*ret%mod*(mod/pk)%mod*inv(mod/pk,pk)%mod); 
		}
		return ans;
	}
	inline void init(int n){
		fac.clear();
		int tp=mod;
		for(int i=2;i*i<=tp;++i){
			if(tp%i==0){
				int now=1,cnt=0;
				while(tp%i==0) tp/=i,now*=i,++cnt;
				fac.push_back(mp(i,now));k[fac.size()-1]=cnt;
			}
		}
		if(tp>1) fac.push_back(mp(tp,tp)),k[fac.size()-1]=1;
		for(int i=0;i<fac.size();++i){
			int p=fac[i].first,pk=fac[i].second;
			mpf[i].clear();mpg[i].clear();
			rep[i][0]=1;
			pk=min(pk,n);
			for(int j=1;j<=pk;++j){
				if(j%p!=0) rep[i][j]=1ll*rep[i][j-1]*j%mod;
				else rep[i][j]=rep[i][j-1];
			}
		}
	}
}
using namespace Lucas;

int c[4][N],ans[N],f[M][M],g[M][M],vis[M][M],d[M][M];
//f[x][y]从第x个点走到第y个点中间不经过任何特殊点的方案
//g[x][y]到达第x个点时已经走过y个点方案 
inline int finddis(int i,int j){
	return exLucas(p[j].y-p[i].y+p[j].x-p[i].x,p[j].x-p[i].x);
}
inline void work(int qx,int qy,int tx,int ty,int tp){
	p[0].x=qx;p[0].y=qy;
	p[n+1].x=tx;p[n+1].y=ty;
	for(int i=1;i<=n+1;++i) d[0][i]=finddis(0,i);
	for(int i=0;i<=n;++i) d[i][n+1]=finddis(i,n+1);
	for(int i=0;i<=n+1;++i){
		f[i][i]=1;
		for(int j=i+1;j<=n+1;++j){
			f[i][j]=d[i][j];
			for(int k=i+1;k<j;++k) f[i][j]=dec(f[i][j],1ll*f[i][k]*d[k][j]%mod);
		}
	} 
	g[0][0]=1;
	for(int i=1;i<=n+1;++i){
		for(int j=0;j<=i;++j){
			g[i][j]=0;
			for(int k=0;k<=i-1;++k) g[i][j]=add(g[i][j],1ll*g[k][j-1]*f[k][i]%mod);
		}
	}
	for(int i=0;i<=n;++i) c[tp][i]=g[n+1][i+1]; 
}
inline void solve(int D){
	for(int i=1;i<=n;++i) for(int j=i+1;j<=n;++j) d[i][j]=finddis(i,j);
	work(1,2,w-1,b,0);
	work(1,2,w,b-1,1);
	work(2,1,w-1,b,2);
	work(2,1,w,b-1,3);
	for(int i=0;i<=n;++i) ans[i]=0;
	for(int i=0;i<=n;++i)
		for(int j=0;j<=n;++j)
			ans[i+j]=add(ans[i+j],dec(1ll*c[0][i]*c[3][j]%mod,1ll*c[1][i]*c[2][j]%mod));
	int ret=0;for(int i=0;i<=D;++i) ret=add(ret,ans[i]);
	printf("%d\n",ret);
}
inline bool cmp(pt a,pt b){
	return a.x!=b.x?a.x<b.x:a.y<b.y; 
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d%d%d",&w,&b,&n,&D,&mod);
		for(int i=1;i<=n;++i) scanf("%d%d",&p[i].x,&p[i].y);
		sort(p+1,p+n+1,cmp);
		init(w+b);
		solve(D);
	}
	return 0;
} 