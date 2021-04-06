#include <iostream>
#include <cstdio>
#include <cctype>
//#include <cstring>
#include <algorithm>
#define il inline
#define vd void
#define rg register
#define ll long long
#define mn 50005
#define rep(i,x,y) for(rg int i=x;i<=y;++i)
#define drp(i,x,y) for(rg int i=x;i>=y;--i)
using namespace std;
const int Len=2333333;
char buf[Len],*p1=buf,*p2=buf,duf[Len],*q1=duf;
il char gc(); il int rd(); il vd pc(char c); il vd rt(ll x); il vd flush();
int n,cnt,u,v,w,r,dfc,tot,a[mn],h[mn],dep[mn],fa[mn][17],dfn[mn],id[mn],Log[mn],f[mn],s[mn],b[mn];
ll Ans,S,siz[mn],y[mn],z[mn],ans[mn],c[mn],C[mn];
struct E{int to,nxt,w;}e[mn<<1];
struct Q{
	int l,r,d; ll k,s;
	il int operator <(const Q &p)const{return k<p.k;}
}q[mn*3];
il int cmp(int a,int b){return siz[a]<siz[b];}
il int Cmp(Q a,Q b){return a.d<b.d;}
il vd Add(int u,int v,int w){e[++cnt]=(E){v,h[u],w},h[u]=cnt;}
il vd Add(ll *c,int x,ll k){while(x<=n) c[x]+=k,x+=x&-x;}
il ll Sum(ll *c,int x){ll ans=0ll; while(x) ans+=c[x],x-=x&-x; return ans;}
il ll Sum(ll *c,int x,int y){return x>y?0ll:Sum(c,y)-Sum(c,x-1);}
vd Dfs(int u){//printf("%d\n",u);
	siz[u]=a[u],s[u]=1,dep[u]=dep[fa[u][0]]+1,dfn[u]=++dfc;
	for(rg int i=1;1<<i<dep[u];++i) fa[u][i]=fa[fa[u][i-1]][i-1];
	for(rg int i=h[u];i;i=e[i].nxt){int v=e[i].to;
		if(v!=fa[u][0]) fa[v][0]=u,b[v]=e[i].w,Dfs(v),siz[u]+=siz[v],s[u]+=s[v];
	}
}
vd Efs(int u){//printf("%d\n",u);
	//printf("ss%d\n",u);
	//printf("%lld %lld\n",y[u],z[u]);
	for(rg int i=h[u];i;i=e[i].nxt){int v=e[i].to;
		if(v==fa[u][0]) continue;
		y[v]=y[u]+b[v],z[v]=z[u]+1ll*b[v]*siz[v],Efs(v),id[v]=++tot,
		q[tot]=(Q){dfn[v]+1,dfn[v]+s[v]-1,tot,siz[v],0ll},++tot,
		q[tot]=(Q){1,dfn[v]-1,tot,S-siz[v],0ll},++tot,
		q[tot]=(Q){dfn[v]+s[v],n,tot,S-siz[v],0ll};
		int x=v; ll t=(S-siz[v])>>1;
		//printf("pp%d\n",v);
		drp(j,Log[dep[v]-1],0) if(fa[x][j]&&siz[fa[x][j]]<=t) x=fa[x][j];
		//printf("%d\n",x);
		ans[v]=(z[fa[x][0]]<<1)-z[u]-y[fa[x][0]]*(S-siz[v]),
		//printf("%lld l\n",ans[v]);
		x=v,t=((S-siz[v])>>1)+siz[v];
		//printf("r%d\n",x);
		drp(j,Log[dep[v]-1],0) if(fa[x][j]&&siz[fa[x][j]]<=t) x=fa[x][j];
		int f=fa[x][0];
		ans[v]+=(z[u]-y[u]*siz[v])-((z[f]-y[f]*siz[v])<<1)+y[f]*(S-siz[v]);
		//printf("oo%d %lld %lld %lld %lld\n",x,(z[u]-y[u]*siz[v])-((z[f]-y[f]*siz[v])<<1),y[f],(S-siz[v]),ans[v]);
	}
}
int main(){
	for(rg int T=rd();T;--T){
		n=rd(),r=(n+1)>>1,S=cnt=dfc=tot=0;
		rep(i,1,n) a[i]=rd(),f[i]=i,S+=a[i],h[i]=b[i]=y[i]=z[i]=c[i]=C[i]=0;
		//memset(fa,0,sizeof(fa));
		rep(i,2,n) u=rd(),v=rd(),w=rd(),Add(u,v,w),Add(v,u,w),Log[i]=Log[i>>1]+1;
		Dfs(r),Efs(r),sort(f+1,f+n+1,cmp),sort(q+1,q+tot+1);
		//puts("233");
		int t=1;
		//rep(i,1,n) printf("%d %d %lld\n",i,dfn[i],ans[i]);
		rep(i,1,tot){
			while(t<=n&&siz[f[t]]<=q[i].k>>1){
				Add(c,dfn[f[t]],1ll*b[f[t]]*siz[f[t]]),++t;
			}
			q[i].s=Sum(c,q[i].l,q[i].r);
			//printf("ert%d %d %lld %lld\n",q[i].l,q[i].r,q[i].k,q[i].s);
		}
		t=n;
		rep(i,1,n) c[i]=0;
		drp(i,tot,1){
			while(t&&siz[f[t]]>q[i].k>>1){
				Add(c,dfn[f[t]],1ll*b[f[t]]*siz[f[t]]),
				Add(C,dfn[f[t]],b[f[t]]),--t;
			}
			q[i].s+=Sum(C,q[i].l,q[i].r)*q[i].k-Sum(c,q[i].l,q[i].r);
		}
		sort(q+1,q+tot+1,Cmp),Ans=9e18;
		rep(i,1,n){
			ans[i]+=q[id[i]].s+q[id[i]+1].s+q[id[i]+2].s;
			//printf("%d %lld\n",i,ans[i]);
			if(i!=r&&ans[i]<Ans) Ans=ans[i];
		}
		rt(Ans),pc('\n');
		rep(i,1,n) for(rg int j=0;1<<j<dep[i];++j) fa[i][j]=0;
	}
	return flush(),0;
}

il char gc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,Len,stdin),p1==p2)?-1:*p1++;}
il int rd(){char c;
	while(!isdigit(c=gc())&&c!='-');
	int f=c=='-'?c=gc(),1:0,x=c^48;
	while(isdigit(c=gc())) x=((x+(x<<2))<<1)+(c^48);
	return f?-x:x;
}
il vd pc(char c){q1==duf+Len&&fwrite(q1=duf,1,Len,stdout),*q1++=c;}
il vd rt(ll x){x<0?pc('-'),x=-x:0,pc((x>=10?rt(x/10),x%10:x)+48);}
il vd flush(){fwrite(duf,1,q1-duf,stdout);}