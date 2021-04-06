#include<bits/stdc++.h>
#define ll long long
#define ull unsigned ll
#define uint ungigned
#define db double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define pli pair<ll,int>
#define vi vector<int>
#define vpi vector<pii >
#define IT iterator
 
#define PB push_back
#define MK make_pair
#define LB lower_bound
#define UB upper_bound
#define y1 wzpakking 
#define fi first
#define se second
#define BG begin
#define ED end
 
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define UPD(x,y) (((x)+=(y))>=mo?(x)-=mo:233)
#define CLR(a,v) memset(a,v,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
#define sqr(x) (1ll*x*x)
 
#define LS3 k*2,l,mid
#define RS3 k*2+1,mid+1,r
#define LS5 k*2,l,mid,x,y
#define RS5 k*2+1,mid+1,r,x,y
#define GET pushdown(k);int mid=(l+r)/2
#define INF (1<<29)
using namespace std;
struct P{
	int x,y;
}p[1000005];
int n;
int XJ(P p1,P p2,P p3){
	return (p2.x-p1.x)*(p3.y-p1.y)-
		   (p2.y-p1.y)*(p3.x-p1.x);
}
int dis(P p1,P p2){
	return (p1.x-p2.x)*(p1.x-p2.x)+
		   (p1.y-p2.y)*(p1.y-p2.y);
}
bool cmp(P p1,P p2){
	int v=XJ(p[1],p1,p2);
	return v>0||(v==0&&dis(p[1],p1)<dis(p[1],p2));
}
int convex(int n){
	if (!n) return 0;
	int id=1;
	For(i,2,n)
		if (p[i].y<p[id].y||
			(p[i].y==p[id].y&&p[i].x<p[id].x))
				id=i;
	if (id!=1) swap(p[1],p[id]);
	sort(p+2,p+n+1,cmp);
	int tp=2;
	For(i,3,n){
		for (;tp>=2&&XJ(p[tp-1],p[tp],p[i])<=0;tp--);
		p[++tp]=p[i];
	}
	return tp;
}
int calc(int i,int j,int n){
	int l=j,r=n;
	while (r-l>2){
		int lm=(l*2+r)/3,rm=(l+2*r)/3;
		if (abs(XJ(p[i],p[j],p[lm]))<abs(XJ(p[i],p[j],p[rm])))
			l=lm;
		else r=rm;
	}
	int ans=0;
	For(k,l,r)
		ans=max(ans,abs(XJ(p[i],p[j],p[k])));
	return ans;
}
int cutP(int n){
	P xx=p[1],nx=p[1],xy=p[1],ny=p[1],
	  xxpy=p[1],nxpy=p[1],xxmy=p[1],nxmy=p[1];
	For(i,2,n){
		if (p[i].x>xx.x||(p[i].x==xx.x&&abs(p[i].y)<abs(xx.y))) xx=p[i];
		if (p[i].x<nx.x||(p[i].x==nx.x&&abs(p[i].y)<abs(nx.y))) nx=p[i];
		if (p[i].y>xy.y||(p[i].y==xy.y&&abs(p[i].x)<abs(xy.x))) xy=p[i];
		if (p[i].y<ny.y||(p[i].y==ny.y&&abs(p[i].x)<abs(ny.x))) ny=p[i];
		if (p[i].x+p[i].y>xxpy.x+xxpy.y) xxpy=p[i];
		if (p[i].x+p[i].y<nxpy.x+nxpy.y) nxpy=p[i];
		if (p[i].x-p[i].y>xxmy.x-xxmy.y) xxmy=p[i];
		if (p[i].x-p[i].y<nxmy.x-nxmy.y) nxmy=p[i];
	}
	int m=0;
	For(i,1,n)
		if (!(XJ(ny,xxmy,p[i])>0&&XJ(xxmy,xx,p[i])>0&&
			  XJ(xx,xxpy,p[i])>0&&XJ(xxpy,xy,p[i])>0&&
			  XJ(xy,nxmy,p[i])>0&&XJ(nxmy,nx,p[i])>0&&
			  XJ(nx,nxpy,p[i])>0&&XJ(nxpy,ny,p[i])>0))
				  p[++m]=p[i];
	return m;
}
void solve(){
	scanf("%d",&n);
	For(i,1,n) scanf("%d%d",&p[i].x,&p[i].y);
	//if (n>1500) n=cutP(n);
	int cnt=convex(n),ans=0;
	For(j,1,cnt) For(k,j+1,cnt)
		ans=max(ans,calc(j,k,cnt));
	printf("%d\n",ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
} 