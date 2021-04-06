#include <bits/stdc++.h>
#define PR pair
#define fi first
#define se second
#define mk make_pair
#define pb push_back
#define CH (ch=getchar())
#define Exit(...)    printf(__VA_ARGS__),exit(0)
#define dprintf(...) fprintf(stderr,__VA_ARGS__)
#define rep(i,V)     for(__typeof(*V.begin()) i:  V)
#define For(i,a,b)   for(int i=(int)a;i<=(int)b;i++)
#define Rep(i,a,b)   for(int i=(int)a;i< (int)b;i++)
#define Forn(i,a,b)  for(int i=(int)a;i>=(int)b;i--)
#define pend(x)      ((x)=='\n'||(x)=='\r'||(x)=='\t'||(x)==' ')
using namespace std;
typedef	double		db;
typedef	long long	ll;
typedef PR<int,int> PII;
const	int N=1005;
const	ll	Inf=(ll)1e10;
const	int inf=(int)1e9;
const	int	mo=ll(1e9+7);

inline int IN(){
	char ch;CH; int f=0,x=0;
	for(;pend(ch);CH); if(ch=='-')f=1,CH;
	for(;!pend(ch);CH) x=x*10+ch-'0';
	return (f)?(-x):(x);
}
int n,m;
ll num[N],Num[N];
db V,S[N],T[N],X[N],f[1005][35],g[1005][10],B[N],fac[N],H[1000005],tmp[1005][35];


int Pow(int x,int y,int p){
	int A=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) A=(ll)A*x%p;
	return A;
}

db Pow(db x,ll y){
	if(x>1e-9) return exp(y*log(1-x));
	return exp(y*-(x+x*x/2));
}

db calc3(ll n,ll k){
	db ans=0;
	if((k+1)/n<2){
		ans+=1.*n/(k+1)/(k+2);
		db tmp=1./n;
		for(int i=2;i<=k&&i<=20;i+=2){
			ans-=B[i]*tmp*(i-1);
			tmp*=1.*(k-i+1)*(k-i+2)/n/n;
		}
	}else{
		ans=0;
		for(int i=1;i<=10&&i<=n;i++) ans+=Pow(db(1.*i/n),k)*i/n;
	}
	return ans;
}

db calc1(ll n){
	if(n<=1e6) return H[n];
	return log(db(n)+1)+.5772156649015328606;
}

db calc2(ll n,ll k){
	db ans=0;
	if((k+1)/n<2){
		ans+=1.*n/(k+1)+.5;
		db tmp=(double)k/n;
		for(int i=2;i<=20&&i<=k;i+=2){
			ans+=B[i]*tmp;
			tmp*=db(k-i)*(k-i+1)/n/n;
		}
	}else{
		ans=1;
		for(int i=1;i<=10&&i<=n;i++) ans+=Pow(db(1.*i/n),k);
	}
	return ans;
}

db calc(ll Pass,ll Comp,db Mean,db Time){
	ll l=1,r=Comp-1,ans=0;
	db lim=Mean/Time;
	while(l<=r){
		ll md=(l+r)>>1;
		if(lim<=md*calc3(Pass,md)) ans=md,l=md+1;
		else r=md-1;
	}
	return Mean*calc1(ans)+Time*calc2(Pass,ans+1);
}

void upd(db &x,db y){
	if(y<x) x=y;
}

int Pos[10005];

inline int cmp(const int &a,const int &b){
	return X[a]<X[b];
}

void Main(){
	scanf("%d%d%lf",&n,&m,&V);
	For(i,1,m) scanf("%lld",&num[i]);
	For(i,1,n) scanf("%lld%lf%lf%lf",&Num[i],&S[i],&T[i],&X[i]);
	int t=(1<<m)-1;
	For(i,0,n) For(j,0,t) f[i][j]=tmp[i][j]=1e200;
	For(i,1,n) Pos[i]=i;
	sort(Pos+1,Pos+n+1,cmp);
	For(i,1,n)
	For(j,1,m) g[i][j]=calc(num[j],Num[i],S[i],T[i]);
	
	For(i,1,n){
		int u=Pos[i];
		For(j,1,m) upd(f[u][1<<(j-1)],fabs(X[u])/V+g[u][j]);
		For(j,1,t) upd(tmp[i][j],tmp[i-1][j]);
		For(j,1,t){
			For(k,1,m){
				if(j&(1<<(k-1)))continue;
				upd(f[u][j|(1<<(k-1))],tmp[i][j]+g[u][k]+X[u]/V);
			}
		}
		For(j,1,t) upd(tmp[i+1][j],f[u][j]-X[u]/V);
	}
	
	db ans=1e200;
	For(i,1,n) ans=min(ans,f[i][t]+fabs(X[i])/V);
	printf("%.10lf\n",ans);
}

int main(){
	B[0]=fac[0]=1;
	For(i,1,50) fac[i]=fac[i-1]*i;
	For(i,1,50)
	Rep(j,0,i) B[i]-=B[j]/fac[i+1-j];
	For(i,1,1000000) H[i]=H[i-1]+1./i;
	int T;
	scanf("%d",&T);
	while(T--) Main();
	return 0;
}


