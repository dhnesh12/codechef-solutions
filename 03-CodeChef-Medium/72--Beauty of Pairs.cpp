#include<bits/stdc++.h>
#define ll long long
#define uint unsigned
#define ull unsigned ll
#define pii pair<int,int>
#define pll pair<ll,ll>
#define PB push_back
#define fi first
#define se second
#define For(i,j,k) for (int i=(int)(j);i<=(int)(k);i++)
#define Rep(i,j,k) for (int i=(int)(j);i>=(int)(k);i--)
#define CLR(a,v) memset(a,v,sizeof(a))
#define CPY(a,b) memcpy(a,b,sizeof(a))
using namespace std;
const int N=200005;
struct Tarr{
	ll t[N];
	int n;
	void init(int _n){
		n=_n;
		For(i,0,n) t[i]=0;
	}
	void change(int k,ll v){
		for (;k<=n;k+=k&(-k)) t[k]+=v;
	}
	ll query(int k){
		ll ans=0;
		for (;k;k-=k&(-k)) ans+=t[k];
		return ans;
	}
}T1,T2;
struct edge{
	int to,next;
}e[N*2];
int head[N],tot;
int w[N],n;
ll sum[N];
void add(int x,int y){
	e[++tot]=(edge){y,head[x]};
	head[x]=tot;
}
void change(int x,int v){
	//printf("change %d %d\n",x,v);
	T1.change(x,1ll*v*w[x]);
	T2.change(x,1ll*v*w[x-1]);
}
ll query(int x){
	return T1.query(x-1)+T2.query(n)-T2.query(x);
}
void getans1(int x,int fa){
	for (int i=head[x];i;i=e[i].next)
		if (e[i].to!=fa){
			change(e[i].to,x);
			getans1(e[i].to,x);
		}
}
void getans2(int x,int fa){
	sum[x]=query(x);
	for (int i=head[x];i;i=e[i].next)
		if (e[i].to!=fa){
			change(e[i].to,-x);
			change(x,e[i].to);
			getans2(e[i].to,x);
			change(x,-e[i].to);
			change(e[i].to,x);
		}
}
void solve(){
	scanf("%d",&n);
	T1.init(n); T2.init(n);
	For(i,1,n) head[i]=0;
	tot=0;
	For(i,1,n-1) scanf("%d",&w[i]);
	For(i,1,n-1){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y); add(y,x);
	}
	getans1(1,0);
	getans2(1,0);
	ll S=-(1ll<<60),ans=0;
	For(i,1,n){
		if (sum[i]>S)
			S=sum[i],ans=0;
		if (sum[i]==S) ++ans;
	}
	printf("%lld %lld\n",S,ans);
}
int main(){
	int T;
	scanf("%d",&T);
	while (T--) solve();
}