#include<bits/stdc++.h>
using namespace std;
#define X first
#define Y second
#define mp make_pair
#define pb push_back
#define il inline
#define rg register
#define lch(x) ((x)<<1)
#define rch(x) ((x)<<1^1)
#define rep(i,st,ed) for(rg int i=(st);i<=(ed);++i)
#define per(i,ed,st) for(rg int i=(ed);i>=(st);--i)
#define rep0(i,n) for(rg int i=0;i<(n);++i)
#define per0(i,n) for(rg int i=(n)-1;i>=0;--i)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double dbl;
typedef long double ldb;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
template<typename T> il T qmin(const T &x,const T &y){return x<y?x:y;}
template<typename T> il T qmax(const T &x,const T &y){return x>y?x:y;}
template<typename T> il void getmin(T &x,const T &y){if(y<x) x=y;}
template<typename T> il void getmax(T &x,const T &y){if(y>x) x=y;}
il void fileio(const string &s){
	freopen((s+".in").c_str(),"r",stdin);
	freopen((s+".out").c_str(),"w",stdout);
}

const int inf=(int)1e9+7;
const ll linf=(ll)1e18+7;
const int N=405,M=805;

int a[M],b[M],x[M],y[M],val[M];
int r,n,m;
ll ans;

il int qid(int x,int y){
	return (x-1)*r+y;
}

int par[N];

il int find(const int &x){
	return !par[x]?x:par[x]=find(par[x]);
}

int p[M];

il bool cmp(const int &x,const int &y){
	return val[x]>val[y];
}

vector<int> ed,cur;

il void solve(){
	memset(par+1,0,sizeof(int)*n);
	rep(i,1,m) p[i]=i;
	sort(p+1,p+m+1,cmp);
	int curx=0,cury=0;
	int rest=n-1;
	cur.clear();
	rep(i,1,m){
		int id=p[i];
		if(find(a[id])==find(b[id])) continue;
		par[find(a[id])]=find(b[id]);
		--rest;
		cur.pb(id);
		curx+=x[id],cury+=y[id];
		if(!rest) break;
	}
	if((ll)curx*curx+(ll)cury*cury>ans){
		ans=(ll)curx*curx+(ll)cury*cury;
		ed=cur;
	}
}

int main(){
	srand(time(0));
//	fileio("test");
	scanf("%d",&r);
	n=r*r,m=0;
	rep(i,1,r){
		rep(j,1,r-1){
			int id=qid(i,j);
			++m;
			scanf("%d%d",x+m,y+m);
			a[m]=id;
			b[m]=id+1;
		}
	}
	rep(j,1,r){
		rep(i,1,r-1){
			int id=qid(i,j);
			++m;
			scanf("%d%d",x+m,y+m);
			a[m]=id;
			b[m]=id+r;
		}
	}
	ans=-linf;
	dbl tm=CLOCKS_PER_SEC*0.76;
	while(clock()<=tm){
		int dx=rand()%20000001-10000000,dy=rand()%20000001-10000000;
		rep(i,1,m) val[i]=x[i]*dx+y[i]*dy;
		solve();
	}
//	cerr<<ans<<endl;
	rep0(i,ed.size()){
		int u=a[ed[i]],v=b[ed[i]];
		printf("%d %d %d %d\n",(u-1)/r+1,(u-1)%r+1,(v-1)/r+1,(v-1)%r+1);
	}
	return 0;
}