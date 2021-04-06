#include<bits/stdc++.h>
using namespace std;

const int maxn=2003;
const int mo=1e9+7;

int c[maxn][maxn],l[maxn][maxn],fa[maxn],sz[maxn],g[maxn],h[maxn],f[maxn],a[maxn],b[maxn],C[maxn][maxn],n,fac[maxn];

int fnd(int x){
	return fa[x]==x?x:fa[x]=fnd(fa[x]);
}

inline void merge(int x,int y){
	int fx=fnd(x),fy=fnd(y);
	if(fx==fy) return ;
	sz[fx]+=sz[fy];
	fa[fy]=fx;
}

inline void add(int &x,int y){
	x+=y;if(x>=mo)x-=mo;
}

void prework(){
	c[0][0]=l[0][0]=1;
	fac[0]=1;
	for(int i=1;i<maxn;++i){
		fac[i]=(1ll*fac[i-1]*i)%mo;
		l[i][0]=c[i][0]=1;
		for(int j=1;j<maxn;++j){
			l[i][j]=l[i-1][j];
			if(i>=2&&j>=1)
				l[i][j]+=l[i-2][j-1];
			if(l[i][j]>=mo)l[i][j]-=mo;
			c[i][j]=l[i][j];
			if(i>=2&&j>=1)
				c[i][j]+=l[i-2][j-1];
			if(c[i][j]>=mo)c[i][j]-=mo;
		}
	}
	for(int i=0;i<maxn;++i){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;++j)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mo;
	}
}
vector<int> cir;
inline void getcir(){
	cir.clear();
	for(int i=1;i<=n;++i)
		fa[i]=i,sz[i]=1;
	for(int i=1;i<=n;++i)
		merge(i,b[i]);
	for(int i=1;i<=n;++i)
		if(fa[i]==i){
			cir.push_back(sz[i]*2);
		}
}

inline void geth(){
	memset(h,0,sizeof(h));
	h[0]=1;
	for(int i=0;i<cir.size();++i)
		for(int j=n;j>=1;--j){
			for(int k=1;k<=min(cir[i]/2,j);++k)
				add(h[j],(1ll*h[j-k]*c[cir[i]][k])%mo);
		}
}

inline void getg(){
	getcir();
	geth();
	for(int i=0;i<=n;++i)
		g[i]=(1ll*fac[n-i]*h[i])%mo;
}

void getf(){
	getg();
	for(int i=n;i>=0;--i){
		f[i]=g[i];
		for(int j=i+1;j<=n;++j)
			add(f[i],mo-(1ll*C[j][i]*f[j])%mo);
	}
}


int main(){
	prework();int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1;i<=n;++i) scanf("%d",&b[a[i]]);
		getf();
//		printf("%d\n",f[0]);
		if(f[0]<0)f[0]+=mo;
		printf("%d\n",f[0]);
	}
	return 0;
}


//