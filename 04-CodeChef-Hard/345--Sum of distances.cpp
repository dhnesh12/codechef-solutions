#include <bits/stdc++.h>
const int inf=1000000000;
#define Rint register int
#define C(n,m) (n<m?0:1ll*fac[n]*invfac[n-m]%mod*invfac[m]%mod)
using namespace std;
int T,n,m,p,k,a[3][100010],f[40][40],dis[3][100010],tree[600010],cnt,b[600010];
long long ans;
struct node{
	int x,y,id;
	bool operator <(const node &b)const{
		return x==b.x?y<b.y:x<b.x;
	}
}addn[100010],qyn[100010];
void add(int x,int c){
	for(int i=x;i<=600000;i+=(i&-i)) tree[i]+=c;
}
int query(int x){
	int res=0;
	for(int i=x;i;i-=(i&-i)) res+=tree[i];
	return res; 
}
void doit(int l,int r,int mid,int k1,int k2,int k3){
	#define cst(p1,p2,i) (int)(cnt-(lower_bound(b+1,b+cnt+1,dis[p1][i]-dis[p2][i])-b)+1)
	int tmp=0,tmp2=0,j;
	for(int i=mid+2;i<=r;i++) addn[++tmp]=(node){cst(k1,k3,i),cst(k2,k3,i),i};
	for(int i=l;i<=mid-2;i++) qyn[++tmp2]=(node){cst(k3,k1,i),cst(k3,k2,i),i};
	sort(addn+1,addn+tmp+1);
	sort(qyn+1,qyn+tmp2+1);
	j=1;
	for(int i=1;i<=tmp;i++){
		while(j<=tmp2&&qyn[j].x<addn[i].x+(k3>=1)) ans+=1ll*dis[k3][qyn[j].id]*query(qyn[j].y-(k3==2)),j++;
		add(addn[i].y,1);
	} 
	while(j<=tmp2) ans+=1ll*dis[k3][qyn[j].id]*query(qyn[j].y-(k3==2)),j++;
	for(int i=1;i<=tmp;i++) add(addn[i].y,-1);
	tmp=tmp2=0;
	for(int i=l;i<=mid-2;i++) addn[++tmp]=(node){cst(k1,k3,i),cst(k2,k3,i),i};
	for(int i=mid+2;i<=r;i++) qyn[++tmp2]=(node){cst(k3,k1,i),cst(k3,k2,i),i};
	sort(addn+1,addn+tmp+1);
	sort(qyn+1,qyn+tmp2+1);
	j=1;
	for(int i=1;i<=tmp;i++){
		while(j<=tmp2&&qyn[j].x<addn[i].x+(k3>=1)) ans+=1ll*dis[k3][qyn[j].id]*query(qyn[j].y-(k3==2)),j++;
		add(addn[i].y,1);
	} 
	while(j<=tmp2) ans+=1ll*dis[k3][qyn[j].id]*query(qyn[j].y-(k3==2)),j++;
	for(int i=1;i<=tmp;i++) add(addn[i].y,-1);
}
void work(int l,int r){
	if(r-l+1<=4){
		for(int i=l;i<=r;i++) for(int j=l;j<=r;j++) f[i-l][j-l]=inf;
		for(int i=l;i<=r;i++) for(int j=0;j<3;j++) if(i+j+1<=r) f[i-l][i+j+1-l]=a[j][i];
		for(int k=l;k<=r;k++) for(int i=l;i<=r;i++) for(int j=l;j<=r;j++) f[i-l][j-l]=min(f[i-l][j-l],f[i-l][k-l]+f[k-l][j-l]);
		for(int i=l;i<=r;i++) for(int j=i+1;j<=r;j++) ans+=f[i-l][j-l];
		int mid=(l+r)>>1;
		return;
	}
	int mid=(l+r)>>1;
	work(l,mid-2),work(mid-1,mid+1),work(mid+2,r);
	for(int i=l;i<=mid+1;i++) dis[0][i]=dis[1][i]=dis[2][i]=inf;
	dis[0][mid-1]=dis[1][mid]=dis[2][mid+1]=0;
	for(int i=mid+1;i>=l;i--) for(int k1=0;k1<3;k1++) if(i+k1+1<=mid+1) for(int k2=0;k2<3;k2++) dis[k2][i]=min(dis[k2][i],dis[k2][i+k1+1]+a[k1][i]);
	for(int i=mid-1;i<=r;i++) dis[0][i]=dis[1][i]=dis[2][i]=inf;
	dis[0][mid-1]=dis[1][mid]=dis[2][mid+1]=0;
	for(int i=mid-1;i<=r;i++) for(int k1=0;k1<3;k1++) if(i-k1-1>=mid-1) for(int k2=0;k2<3;k2++) dis[k2][i]=min(dis[k2][i],dis[k2][i-k1-1]+a[k1][i-k1-1]);
	cnt=0;
	for(int i=l;i<=r;i++){
		if(i>=mid-1&&i<=mid+1) continue;
		for(int k1=0;k1<3;ans+=dis[k1][i],k1++) for(int k2=0;k2<3;k2++) if(k1!=k2) b[++cnt]=dis[k1][i]-dis[k2][i];
	}
	sort(b+1,b+cnt+1);
	cnt=unique(b+1,b+cnt+1)-b-1;
	doit(l,r,mid,1,2,0);
	doit(l,r,mid,0,2,1);
	doit(l,r,mid,0,1,2);
}
void solve(){
	ans=0; 
	scanf("%d",&n);
	for(int i=1;i<n;i++) scanf("%d",&a[0][i]);
	for(int i=1;i<n-1;i++) scanf("%d",&a[1][i]);
	for(int i=1;i<n-2;i++) scanf("%d",&a[2][i]);
	work(1,n);
	printf("%lld\n",ans);
}
int main(){
	scanf("%d",&T);
	while(T--) solve();
}