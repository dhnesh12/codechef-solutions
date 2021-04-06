#include<set>
#include<map>
#include<ctime>
#include<cmath>
#include<queue>
#include<bitset>
#include<string>
#include<cstdio>
#include<cctype>
#include<cassert>
#include<cstdlib>
#include<cstring>
#include<sstream>
#include<iostream>
#include<algorithm>

#define For(i,x,y) for (int i=x;i<y;i++)
#define Rep(i,x,y) for (int i=x;i<=y;i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define lf else if

#define dprintf(...) fprintf(stderr,__VA_ARGS__)
using namespace std;

typedef long long ll;
typedef long double db;
typedef pair<int,int> pii;
typedef vector<int> Vi;

ll IN(){
	int c,f;ll x;
	while (!isdigit(c=getchar())&&c!='-');c=='-'?(f=1,x=0):(f=0,x=c-'0');
	while (isdigit(c=getchar())) x=(x<<1)+(x<<3)+c-'0';return !f?x:-x;
}

const int p=900000011;
const int top=25;
const int N=top+5;

int Pow(int a,int b){
	int res=1;
	for (;b;b>>=1,a=1ll*a*a%p) if (b&1) res=1ll*res*a%p;
	return res;
}

int f[top][N],g[top][N],h[top][N],val[N],fac[N],inv[N];
ll n,A,B;
int K,L,res,M;

int Co(int n,int m){
	if (n<m) return 0;
	return 1ll*fac[n]*inv[m]%p*inv[n-m]%p;
}
void work(int n,int *res){
	static int f[N],g[N];
	memset(f,0,sizeof(f));
	f[0]=1;
	For(i,0,n){
		for (int j=i+1;~j;j--){
			f[j]=1ll*f[j]*(p-i)%p;
			if (j>0) f[j]=(f[j]+f[j-1])%p;
		}
	}
	For(i,0,n){
		int tmp=1;
		For(j,0,n) if (j!=i) tmp=1ll*tmp*(i-j+p)%p;
		tmp=1ll*val[i]*Pow(tmp,p-2)%p;
		memcpy(g,f,sizeof(f));
		for (int j=n;j;j--){
			res[j-1]=(res[j-1]+1ll*g[j]*tmp)%p;
			g[j-1]=(g[j-1]+1ll*g[j]*i)%p;
		}
	}
}
void Init(){
	fac[0]=1;
	For(i,1,N) fac[i]=1ll*fac[i-1]*i%p;
	inv[N-1]=Pow(fac[N-1],p-2);
	for (int i=N-1;i;i--) inv[i-1]=1ll*inv[i]*i%p;
	f[0][0]=1;
	For(m,1,top){
		For(i,0,m) f[m][i]=f[m-1][i];
		for (int i=m;~i;i--){
			f[m][i]=1ll*f[m][i]*(1-m+p)%p;
			if (i>0) f[m][i]=(f[m][i]+f[m][i-1])%p;
		}
	}
	For(m,0,top){
		For(i,0,m+1) f[m][i]=1ll*f[m][i]*inv[m]%p;
	}
	For(m,0,top){
		val[0]=0;
		For(i,1,m+2) val[i]=(val[i-1]+Pow(i,m))%p;
		work(m+2,g[m]);
	}
	For(m,0,top){
		For(i,0,m){
			h[m][i]=Co(m,i);
			if ((m-i+1)&1) h[m][i]=(p-h[m][i])%p;
		}
	}
}
int sum(ll n,int b){
	int x=1,res=0;
	For(i,0,b+2){
		res=(res+1ll*g[b][i]*x)%p;
		x=1ll*x*(n%p)%p;
	}
	return res;
}

int ans[400][N][N],w[N];

ll Div(ll a,ll b){
	if (a>=0) return a/b;
	return a%b==0?a/b:a/b-1;
}
void cal(int dep,ll n,ll A,ll B,ll C){
	assert(n>=0);
	if (n==0) return;
	if (A==0){
		For(a,0,M) For(b,0,M-a){
			ans[dep][a][b]=1ll*Pow(Div(B,C)%p,a)*sum(n,b)%p;
		}
		return;
	}
	if (A>=C){
		ll T=A/C;
		cal(dep+1,n,A%C,B,C);
		For(a,0,M) For(b,0,M-a){
			int x=1;
			Rep(i,0,a){
				ans[dep][a][b]=(ans[dep][a][b]+1ll*Co(a,i)*x%p*ans[dep+1][a-i][b+i])%p;
				x=1ll*x*(T%p)%p;
			}
		}
		return;
	}
	ll m=ll((db(A)*n+B)/C);
	ll tmp=A*n+B-C*m;
	while (tmp<0) tmp+=C,m--;
	while (tmp>=C) tmp-=C,m++;
	cal(dep+1,m,C,-B-1,A);
	For(b,0,M){
		int s=sum(n,b),x=1;
		For(j,0,M-b){
			w[j]=0;
			Rep(i,0,b+1){
				w[j]=(w[j]+1ll*g[b][i]*ans[dep+1][i][j])%p;
			}
		}
		For(a,0,M-b){
			int res=1ll*s*x%p;
			Rep(j,0,a-1) res=(res-1ll*w[j]*h[a][j])%p;
			ans[dep][a][b]=(res+p)%p;
			x=1ll*x*(m%p)%p;
		}
	}
}
void Main(){
	memset(ans,0,sizeof(ans));
	n=IN(),A=IN(),B=IN(),K=IN(),L=IN();
	res=0;
	M=K+1+L+1;
	cal(0,n,A,0,B);
	Rep(i,0,K+1) Rep(j,0,L){
		int c1=0,c2=0;
		Rep(k,i,K+1) c1=(c1+1ll*Co(k,i)*f[K+1][k])%p;
		Rep(k,j,L) c2=(c2+1ll*Co(k,j)*Pow(n%p,k-j)%p*f[L][k])%p;
		if (j&1) c2=(p-c2)%p;
		res=(res+1ll*c1*c2%p*ans[0][i][j])%p;
	}
	printf("%d\n",res);
}

int main(){
	Init();
	for (int T=IN();T--;) Main();
}