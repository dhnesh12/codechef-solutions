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
const int N=35;
int a[N],q[N],vis[N],n,m;
ll f[N][N],ans;
void solve(){
	scanf("%d%d",&n,&m);
	CLR(vis,0); CLR(q,0); ans=0;
	For(i,1,m) scanf("%d",&a[i]),vis[a[i]]=1;
	For(i,1,n) if (!vis[i]) q[++*q]=i;
	For(i,0,n-m){
		int fi=(*q==0?2333:q[1]),se=(!q[i]||!i?2333:q[i]),fl=1;
		Rep(j,m,1)
			if (a[j]>se) fl=0;
			else if (a[j]>fi) se=a[j];
			else fi=a[j];
		if (fl) ans+=f[n-m][i];
	}
	printf("%lld\n",ans);
}
int main(){
	f[0][0]=f[1][0]=1;
	For(i,2,30) For(j,0,i-1){
		int mn=1,mx=j;
		For(k,1,(!j?i:j)){
			int to=(k==1?j+(j!=0):k);
			f[i][to]+=f[i-1][j];
		}
	}
	int T; scanf("%d",&T);
	while (T--) solve();
}