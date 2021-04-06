#include <bits/stdc++.h>
using namespace std;
const int Q=2005;
namespace Rand{
vector<int>g[Q];
int pr[Q],vis[Q],Time=0;
int Try(int x)
{
	random_shuffle(g[x].begin(),g[x].end());
	vis[x]=Time;
	for(int y:g[x])
		if(!pr[y]){
			pr[x]=y,pr[y]=x;
			return 1;
		}
	for(int y:g[x]){
		int z=pr[y];
		if(vis[z]==Time)continue;
		pr[x]=y,pr[y]=x,pr[z]=0;
		if(Try(z))return 1;
		pr[x]=0,pr[y]=z,pr[z]=y;
	}
	return 0;
}
}
int fa[Q];
int gf(int x)
{return fa[x]==x?x:(fa[x]=gf(fa[x]));}
int X[Q],Y[Q];
int n,m,kk;
int x[Q*Q],y[Q*Q];
__int128 sd[Q],sd2[Q],d[Q];
__int128 r1[Q],r2[Q];
vector<int>p;
int ox[Q],oy[Q];
int Cal(int st)
{
	p.clear();
	for(int i=1;i<=n;i++)
		if(gf(i)==st)p.push_back(i),sd[i]=sd2[i]=d[i]=r1[i]=r2[i]=0;
	int tp=0;
	for(int i=1;i<=m;i++)
		if(gf(X[i])==st)
			x[++tp]=X[i],y[tp]=Y[i],++d[X[i]],++d[Y[i]];
	if(kk==1)return tp>>1;
	__int128 tmp=0;
	if(kk==2){
		for(int i=1;i<=n;i++)
			if(gf(i)==st)tmp+=d[i]*(d[i]-1)/2;
		return tmp>>1;
	}
	if(kk==3){
		for(int i=1;i<=tp;i++){
			int D=d[x[i]]+d[y[i]]-2;
			tmp+=D*(D-1)/2;
		}
		return tmp>>1;
	}
	if(kk==4){
		for(int i=1;i<=tp;i++){
			int a=x[i],b=y[i];
			sd[a]+=d[b],sd[b]+=d[a];
			sd2[a]+=1ll*d[b]*d[b];
			sd2[b]+=1ll*d[a]*d[a];
		}
		for(int i:p){
			tmp+=4ll*d[i]*d[i]*d[i]*(d[i]-1)/2ll;
			tmp+=42ll*d[i]*(d[i]-1)/2ll;
			tmp-=13ll*d[i]*d[i]*(d[i]-1);
			tmp-=13ll*sd[i]*(d[i]-1);
			tmp+=4ll*d[i]*sd[i]*(d[i]-1);
			tmp+=sd2[i]*(d[i]-1);
			tmp+=sd[i]*sd[i]-sd2[i];
		}
		tmp>>=1;
		return (tmp>>1)%998244353;
	}
	if(kk==6){
		int rem=tp;tp=0;
		for(int i=1;i<=rem;i++)
			ox[i]=x[i],oy[i]=y[i],d[i]=r1[i]=r2[i]=sd[i]=sd2[i]=0;
		for(int i=1;i<=rem;i++)
			for(int j=i+1;j<=rem;j++)
				if(ox[i]==ox[j]||ox[i]==oy[j]||oy[i]==ox[j]||oy[i]==oy[j])
					++d[i],++d[j],x[++tp]=i,y[tp]=j;
	}
	for(int i=1;i<=tp;i++){
		int a=x[i],b=y[i],D=d[a]+d[b]-2;
		r1[a]+=D,r1[b]+=D;
		r2[a]+=1ll*D*D,r2[b]+=1ll*D*D;
	}
	for(int i=1;i<=tp;i++){
		int a=x[i],b=y[i];
		__int128 dd=d[a]+d[b]-2,sd=r1[a]+r1[b]-2*dd,sd2=r2[a]+r2[b]-2*dd*dd;
		tmp+=4ll*dd*dd*dd*(dd-1)/2ll;
		tmp+=42ll*dd*(dd-1)/2ll;
		tmp-=13ll*dd*dd*(dd-1);
		tmp-=13ll*sd*(dd-1);
		tmp+=4ll*dd*sd*(dd-1);
		tmp+=sd2*(dd-1);
		tmp+=sd*sd-sd2;
	}
	tmp>>=1;
	return (tmp>>1)%998244353;
}
int main()
{
	scanf("%d%d%d",&n,&m,&kk);
	if(kk==1){
		srand(time(NULL));
		for(int i=1,x,y;i<=m;i++)
			scanf("%d%d",&x,&y),Rand::g[x].push_back(y),Rand::g[y].push_back(x);
		int tmp=0;
		for(int o=1;o<=8;o++)
			for(int i=1;i<=n;i++)
				if(!Rand::pr[i])
					++Rand::Time,tmp+=Rand::Try(i);
		return 0&printf("%d\n",tmp);
	}
	for(int i=1;i<=n;i++)
		fa[i]=i;
	--kk;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&X[i],&Y[i]),fa[gf(X[i])]=gf(Y[i]);
	long long als=0;
	for(int i=1;i<=n;i++)
		if(gf(i)==i)
			als+=Cal(i);
	printf("%lld\n",als%998244353);
	return 0;
}