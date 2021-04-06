/* by Natsu Kinmoe */
#include <bits/stdc++.h>
using namespace std;

#define loop(i,n) for(int i=0;i<(n);i++)
#define pool(i,n) for(int i=(n)-1;i>=0;i--)
#define cont(i,n) for(int i=1;i<=(n);i++)
#define tnoc(i,n) for(int i=(n);i>=1;i--)
#define circ(i,a,b) for(int i=(a);i<=(b);i++)
#define cric(i,a,b) for(int i=(b);i>=(a);i--)
#define sub(i,a) for(int i=a;i;i=((i-1)&(a)))
#define subs(i,a) for(int i=a;i>=0;i=(!i?-1:((i-1)&(a))))
#define subt(i,a) for(int i=((a-1)&a);i;i=((i-1)&(a)))
#define subst(i,a) for(int i=((a-1)&a);i>=0;i=(!i?-1:((i-1)&(a))))
#define range(i,a,b,c) for(int i=(a);((c)>0?i<=(b):i>=(b));i+=(c))
#define foreach(it,v) for(__typeof((v).begin()) it=(v).begin(),_e_D_=(v).end();it!=_e_D_;it++)
#define parse(i,s) for(int i=0;s[i];i++)

#define pub push_back
#define pob pop_back
#define puf push_front
#define pof pop_front
#define mak make_pair

#define y0 y0O0OO00OO0OO0OO0OOO00OO0OO0O0O000OO0
#define y1 y1II11II11III11I1III11II111IIII1II1I1
#define ws WSrAkIoi2333wSraKIoIWSraKiOi
#define left left_jTjTJtJtIoiiOiioIAuaU66666jtIOIau
#define hash whYusEthiSnamE_caNyoUusEothERnaMesliKeHSH

#define Mas(a) (1<<(a))
#define Mask(a) (1ull<<(a))
#define Maskx(a,x) ((a)<<(x))
#define Full(a) ((1ll<<(a))-1)
#define Bit(a,x) (((a)>>(x))&1)
#define all(a) (a).begin(),(a).end()
#define SZ(a) ((int)((a).size()))

typedef long long ll;
typedef long double lf;
typedef unsigned long long ull;

const int Inf=0x3f3f3f3f;
const ll INF=0x3f3f3f3f3f3f3f3fll;
const lf inF=11451419198101145141919810.1145141919810;
const lf pi=acosl(-1);
/* Source code starts here */

int n,m,N;
double p[6][105];
ull szs[6];
map<ull,int> ids;
ull idx[3800];
int nxt[3800][64];
int mcs[3800];
int siz;
double dp[2][3800];

int getid(ull x){
	if(!ids.count(x)){
		idx[siz]=x;
		return ids[x]=siz++;
	}else return ids[x];
}

int main(){
	scanf("%d%d",&n,&m);
	N=Mas(n);
	loop(msk,N){
		int cnts=0;
		loop(i,n) if(msk&Mas(i)) cnts++;
		szs[cnts]|=Mask(msk);
	}
	getid(1);
	loop(i,siz){
		ull stat=idx[i];
		vector<ull> nxts(6,0);
		loop(msk,N) if(stat&Mask(msk)) loop(j,n) nxts[j]|=Mask(msk|Mas(j));
		loop(msk,N){
			ull St=stat;
			loop(j,n) if(msk&Mas(j)) St|=nxts[j];
			nxt[i][msk]=getid(St);
		}
		pool(j,n+1) if(szs[j]&stat){
			mcs[i]=j;
			break;
		}
	}
	loop(i,n) loop(j,m) scanf("%lf",&p[i][j]);
	dp[0][0]=1;
	int now=1,lst=0;
	loop(i,m){
		loop(j,siz) dp[now][j]=0.;
		loop(msk,N){
			double Pr=1.;
			loop(j,n) Pr*=(msk&Mas(j))?p[j][i]:(1.-p[j][i]);
			loop(j,siz) dp[now][nxt[j][msk]]+=Pr*dp[lst][j];
		}
		swap(now,lst);
	}
	double ans=0.;
	loop(j,siz) ans+=dp[lst][j]*mcs[j];
	printf("%.8lf\n",ans);
	return 0;
}