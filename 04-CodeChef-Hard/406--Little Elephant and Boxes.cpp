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
#define For(i,a,b)   for(int i=(int)(a);i<=(int)(b);i++)
#define Rep(i,a,b)   for(int i=(int)(a);i< (int)(b);i++)
#define Forn(i,a,b)  for(int i=(int)(a);i>=(int)(b);i--)
#define pend(x)      ((x)=='\n'||(x)=='\r'||(x)=='\t'||(x)==' ')
using namespace std;
typedef	double		db;
typedef	long long	ll;
typedef PR<int,int> PII;
const	int N=35;
const	ll	Inf=(ll)1e10;
const	int inf=(int)1e9;
const	int	mo=ll(1e9+7);

inline int IN(){
	char ch;CH; int f=0,x=0;
	for(;pend(ch);CH); if(ch=='-')f=1,CH;
	for(;!pend(ch);CH) x=x*10+ch-'0';
	return (f)?(-x):(x);
}

int Pow(int x,int y,int p){
	int A=1;
	for(;y;y>>=1,x=(ll)x*x%p) if(y&1) A=(ll)A*x%p;
	return A;
}

db P[N];
int n,m,V[N],C[N],D[N];
int f[N][N],n1,n2,tf[20],tg[20];
struct node{
	int mon;
	db pro;
	bool operator <(const node &a)const{
		if(mon==a.mon) return pro<a.pro;
		return mon<a.mon;
	}
}G[20][40005],F[20][40005];

void upd(int &x,int y){
	if(x>y) x=y;
}

void dfs(int x,int r,int mon,int dio,db pro){
	if(!pro) return;
	if(x>r){
		if(r<n){
			F[dio][++tf[dio]]=(node){mon,pro};
		}else{
			G[dio][++tg[dio]]=(node){mon,pro};
		}
		return;
	}
	dfs(x+1,r,mon,dio+1,pro*(1-P[x]));
	dfs(x+1,r,mon+V[x],dio,pro*P[x]);
}

void Main(){
	scanf("%d%d",&n,&m);
	For(i,1,n){
		int c;
		scanf("%d%d",V+i,&c);
		P[i]=.01*c;
	}
	For(i,1,m) scanf("%d%d",C+i,D+i);
	memset(f,0x3f,sizeof f);
	f[0][0]=0;
	For(i,1,m)
	Forn(j,i-1,0)
	Forn(k,n,0)
	if(k+D[i]<=n)upd(f[j+1][k+D[i]],f[j][k]+C[i]);

	
	n1=n>>1;
	n2=n-(n>>1);
	
	For(i,0,n1) tf[i]=0;
	For(i,0,n2) tg[i]=0;
	
	dfs(1,n1,0,0,1);
	dfs(n1+1,n,0,0,1);
	
	For(i,0,n1){
		sort(F[i]+1,F[i]+tf[i]+1);
		F[i][tf[i]+1].pro=0;
		Forn(j,tf[i],1) F[i][j].pro+=F[i][j+1].pro;
	}
	For(i,0,n2){
		sort(G[i]+1,G[i]+tg[i]+1);
		G[i][tg[i]+1].pro=0;
		Forn(j,tg[i],1) G[i][j].pro+=G[i][j+1].pro;
	}
	
	For(i,1,n)
	For(j,1,n) upd(f[i][j],f[i][j-1]);
	
	db re=0;
	static db RE[10005]={};
	memset(RE,0,sizeof RE);
	For(j,0,n1)
	For(k,0,n2){
		if(!tf[j]||!tg[k])continue;

		db Pre=0;
		Forn(i,m,1){
			int mon=f[i][j+k];
			if(mon>1e9)continue;
			int v=tg[k];
			db Ans=0;
			For(u,1,tf[j]){
				while(v&&F[j][u].mon+G[k][v].mon>=mon) --v;
				Ans+=(F[j][u].pro-F[j][u+1].pro)*G[k][v+1].pro;
			}
			RE[i]+=Ans-Pre;
			re+=i*(Ans-Pre);
			Pre=Ans;
		}
	}
	
//	For(i,1,n) printf("%.10lf ",RE[i]);
//	puts("");
	
	printf("%.4lf\n",re);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--) Main();
	return 0;
}


