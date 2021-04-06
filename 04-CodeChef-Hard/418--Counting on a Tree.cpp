#include<bits/stdc++.h>
using namespace std;
#define N 2000010
#define M 2000010
#define int long long
int n,a[N],b[N],c[N],q,pr[M],f[N],sz[N],fc[N],vv[N],va[N],vg,vt[N],tp,k[N],x[N],cv[N],vp[N];
int p[M],vi[M],ct,vu[M];
int fd(int x){
	while(f[x])
		x=f[x];
	return x; 
}
struct no{
	int s,f,x,y;
}ss[M];
int mg(int x,int y){
	x=fd(x);
	y=fd(y);
	if(x==y)
		return 0;
	if(sz[x]>sz[y])
		swap(x,y);
	int ans=sz[x]*sz[y];
	ss[++tp]=((no){sz[y],f[x],x,y});
	sz[y]+=sz[x];
	f[x]=y;
	return ans;
}
void rb(int x){
	while(tp>x){
		no z=ss[tp];
		f[z.x]=z.f;
		sz[z.y]=z.s;
		tp--;
	}
}
vector<int>vc[M];
void si(){
	vu[1]=1;
	for(int i=2;i<M;i++){
		if(!vi[i]){
			p[++ct]=i;
			vu[i]=-1;
			pr[i]=i;
		}
		for(int j=1;i*p[j]<M;j++){
			vi[i*p[j]]=1;
			pr[i*p[j]]=p[j];
			if(i%p[j]==0)
				break;
			vu[i*p[j]]=-vu[i];
		}
	}
}
void dfs(int v,int x,int y,int t){
	if(y==ct+1){
		if(!t)
			vp[v]++;
		cv[v]++;
		if(t)
			vc[v].push_back(x);
		return;
	}
	dfs(v*fc[y],x,y+1,t);
	dfs(v,x,y+1,t);
}
signed main(){
	si();
	memset(vi,0,sizeof(vi));
	scanf("%lld",&n);
	for(int i=1;i<n;i++)
		scanf("%lld%lld%lld",&a[i],&b[i],&c[i]);
	for(int i=1;i<=n;i++)
		sz[i]=1;
	for(int i=1;i<n;i++){
		ct=0;
		int x=c[i];
		while(x!=1){
			if(!vv[pr[x]])
				fc[++ct]=pr[x];
			vv[pr[x]]=1;
			x/=pr[x];
		}
		dfs(1,i,1,1);
		for(int j=1;j<=ct;j++)
			vv[fc[j]]=0;
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		sz[i]=1;
	for(int i=1;i<M;i++)
		if(vc[i].size()&&vu[i]){
			for(int j=0;j<vc[i].size();j++)
				ans+=vu[i]*mg(a[vc[i][j]],b[vc[i][j]]);
			rb(0);
		}
	printf("%lld\n",ans);
	scanf("%lld",&q);
	for(int i=1;i<=q;i++){
		scanf("%lld%lld",&k[i],&x[i]);
		ct=0;
		int y=x[i];
		while(y!=1){
			if(!vv[pr[y]])
				fc[++ct]=pr[y];
			vv[pr[y]]=1;
			y/=pr[y];
		}
		for(int j=1;j<=ct;j++)
			vv[fc[j]]=0;
		dfs(1,i,1,0);
		vi[k[i]]=1;
	}
	for(int i=1;i<=n;i++)
		if(vi[i]){
			ct=0;
			int y=c[i];
			while(y!=1){
				if(!vv[pr[y]])
					fc[++ct]=pr[y];
				vv[pr[y]]=1;
				y/=pr[y];
			}
			for(int j=1;j<=ct;j++)
				vv[fc[j]]=0;
			dfs(1,i,1,0);
		}
	ans=0;
	int ct=0,ok=0;
	for(int i=1;i<M;i++){
		if(cv[i]&&vu[i]){
			ct+=q*q;
			ans=0;
			for(int j=0;j<vc[i].size();j++)
				if(!vi[vc[i][j]])
					ans+=vu[i]*mg(a[vc[i][j]],b[vc[i][j]]);
			for(int j=1;j<=q;j++)
				va[j]+=ans;
			int tt=tp;
			for(int j=1;j<=q;j++)
				vt[k[j]]=c[k[j]];
			if(vp[i]){
				for(int j=1;j<=q;j++){
					vt[k[j]]=x[j];
					ans=0;
					for(int l=1;l<=q;l++)
						if(vt[k[l]]%i==0){
							ok=1;
							ans+=vu[i]*mg(a[k[l]],b[k[l]]);
						}
					rb(tt);
					va[j]+=ans;
				}
			}
			rb(0);
		}
	}
	//printf("%d\n",ok);
	for(int i=1;i<=q;i++)
		printf("%lld\n",va[i]);
}