#include<bits/stdc++.h>
#define cs const
#define pb push_back
using namespace std;
typedef long double ld;
typedef long long ll;
cs int N = 15, M = 50;
namespace LP{
	cs ld eps = 1e-10, INF = 1e17;
	int n, m; ld a[N*N][N*M+M*2];
	void pivot(int l, int e){
		ld t=a[l][e]; a[l][e]=1;
		for(int i=0; i<=m; i++) a[l][i]/=t;
		for(int i=0; i<=n; i++) if(i!=l&&fabs(a[i][e])>eps){
			t=a[i][e]; a[i][e]=0;
			for(int j=0; j<=m; j++) a[i][j]-=t*a[l][j];
		}
	}
	void simplex(){
		while(true){
			int l=0, e=0; ld mn=INF;
			for(int j=1; j<=m; j++) if(a[0][j]>eps){ e=j; break; }
			if(!e) break;
			for(int i=1; i<=n; i++) 
			if(a[i][e]>eps&&a[i][0]/a[i][e]<mn) 
			mn=a[i][0]/a[i][e], l=i;
			pivot(l,e); 
		}
	}
	void solve(){
		simplex(); ld vl=-a[0][0];
		for(int i=1;;i++) if(vl*i-(ll)(vl*i+eps)<eps){
			cout<<(ll)(vl*i+eps)<<"/"<<i; return;
		}
	}
} using LP :: a;
int n, m, &nn=LP::n, &mm=LP::m;
int id[3][N][N];
int idx(int t, int u, int v){
	if(u>v) swap(u,v);
	if(id[t][u][v]) return id[t][u][v];
	return id[t][u][v]=++nn;
}
int main(){
	#ifdef FSYolanda
	freopen("1.in","r",stdin);
	#endif
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w; i<=m; i++){
		scanf("%d%d%d",&u,&v,&w); ++u; ++v;
		int i1=idx(0,u,v), i2=idx(1,u,v), i3=idx(2,u,v);
		a[i1][0]=a[i2][0]=1;
		a[0][++mm]=w; a[i3][mm]=a[i2][mm]=1, a[i1][mm]=-1;
		a[0][++mm]=-w; a[i3][mm]=a[i2][mm]=-1; a[i1][mm]=1;
		for(int j=1; j<=n; j++) if(u!=j&&v!=j){
			a[0][++mm]=-w,a[i1][mm]=1,a[i2][mm]=-1,a[idx(2,v,j)][mm]=1,a[idx(2,u,j)][mm]=-1;
			a[0][++mm]=-w,a[i1][mm]=1,a[i2][mm]=-1,a[idx(2,u,j)][mm]=1,a[idx(2,v,j)][mm]=-1;
		}
	} LP::solve(); return 0;
}