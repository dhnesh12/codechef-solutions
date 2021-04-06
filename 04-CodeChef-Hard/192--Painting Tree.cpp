#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ui unsigned int
#define ull unsigned long long
#define db long double
#define pii pair<ll,int>
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define vi vector<int>
#define vii vector<vi>
#define lb lower_bound
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define per(i,b,a) for(register int i=(b);i>=(a);--i)
#define rep0(i,a,b) for(register int i=(a);i<(b);++i)
#define fore(i,a) for(register int i=0;i<a.size();++i)
#define ls x<<1,l,m
#define rs x<<1|1,m+1,r
#define gc() getchar()
inline ll rd()
{
	ll x=0,w=1;char c=gc();while(!isdigit(c)&&c!='-')c=gc();
	if(c=='-')w=-1,c=gc();while(isdigit(c))x=x*10+c-48,c=gc();return x*w;
}
const int N=100005;
const ll inf=1e18;
int n,tt,H,d[N],rt[N];ll c[N],h[N],f[N],s[N];vi g[N];
struct F
{
	ll a,b,c;
	inline ll gt(ll x){return a*x*x+b*x+c;}
};
struct st{int l,r;ll tg;F f;}T[20*N];
inline int nwnd(F f){T[++tt]=(st){0,0,0,f};return tt;}
inline void cov(int x,ll v){if(!x)return;T[x].tg+=v;T[x].f.c+=v;}
inline void dn(int x){if(!T[x].tg)return;cov(T[x].l,T[x].tg);cov(T[x].r,T[x].tg);T[x].tg=0;}
void ins(int&x,int l,int r,F f)
{
	if(!x){x=nwnd(f);return;}
	int m=l+r>>1;dn(x);
	if(T[x].f.gt(m)>f.gt(m))swap(T[x].f,f);
	if(T[x].f.gt(l)>f.gt(l))ins(T[x].l,l,m,f);
	else if(T[x].f.gt(r)>f.gt(r))ins(T[x].r,m+1,r,f);
}
int merge(int x,int y,int l,int r)
{
	if(!x||!y)return x|y;
	int m=l+r>>1;dn(x);dn(y);
	T[x].l=merge(T[x].l,T[y].l,l,m);
	T[x].r=merge(T[x].r,T[y].r,m+1,r);
	ins(x,l,r,T[y].f);return x;
} 
ll qry(int x,int l,int r,int p)
{
	if(!x)return inf;int m=l+r>>1;dn(x);
	return min(p<=m?qry(T[x].l,l,m,p):qry(T[x].r,m+1,r,p),T[x].f.gt(p));
}
void dfs(int x,int p)
{
	s[x]=0;for(int y:g[x])if(y!=p){dfs(y,x);s[x]+=f[y];}
	rt[x]=nwnd((F){c[x],2*c[x]*c[x]+c[x],c[x]*(c[x]*2+d[x])*(1-d[x])-2*h[x]+s[x]}); 
	for(int y:g[x])if(y!=p){cov(rt[y],s[x]-f[y]);rt[x]=merge(rt[x],rt[y],0,H);}
	f[x]=qry(rt[x],0,H,d[x]);
}
void pre(int x,int p)
{
	d[x]=d[p]+1;H=max(H,d[x]);
	for(int y:g[x])if(y!=p)pre(y,x);
}
void sol()
{
	n=rd();tt=0;H=0;
	rep(i,1,n)h[i]=rd(),c[i]=rd();
	rep(i,1,n-1){int u=rd(),v=rd();g[u].pb(v);g[v].pb(u);}
	pre(1,0);rep(i,1,n)d[i]=H-d[i];
	dfs(1,0);printf("%lld\n",f[1]/2);
	rep(i,1,n)g[i].clear();
}
int main(){int T=rd();while(T--)sol();return 0;}
