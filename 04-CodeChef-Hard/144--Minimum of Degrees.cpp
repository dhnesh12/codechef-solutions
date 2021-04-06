#include <bits/stdc++.h>
 
#define For(i,l,r) for(int _r=r,i=l;i<=_r;++i)
#define rep(i,l,r) for(int _r=r,i=l;i<_r;++i)
#define dto(i,r,l) for(int _l=l,i=r;i>=_l;--i)
#define x first
#define y second
#define pb push_back
#define mk make_pair
#define oo (c=getchar())
#define SZ(V) (int(V.size()))
#define ALL(V) V.begin(),V.end()
 
using namespace std;
 
typedef double db;
typedef long long LL;
typedef pair<int ,int> PII;
typedef vector<int> VI;
typedef complex<db> cpx;
typedef vector<PII> VII;
// typedef __int128 bigint;
 
int ran(){return (rand()<<15)+rand();}
 
int IN(){
	int x=0;char c;
	for(;oo<48 && c^'-' || c>57;);bool f=c=='-';if(f)oo;
	for(;c>47 && c<58;oo)x=(x<<1)+(x<<3)+c-48;return f?-x:x;
}
void print(int x,char en='\n'){
	printf("%d",x);if(en)putchar(en);
}
 
void hello(){
	freopen("remi.in","r",stdin);
//	freopen("remi.out","w",stdout);
//	srand(time(0));
}
 
int n;
 
const int mo = 998244353, lim = 600000;
typedef int Arr[lim+10];
Arr ga,invga,inv;
 
int Pow(int x,int y){
	int z = 1;
	for(;y;y>>=1,x=1ll*x*x%mo)if(y&1)z=1ll*z*x%mo;
	return z;
}
 
void inc(int &x, int y){if((x+=y)>=mo)x-=mo;}
void dec(int &x, int y){if((x-=y)<0)x+=mo;}
 
int tri(int n){
	return 1ll*n*(n-1)/2%mo;
}
 
int binom(int n,int m){
	assert(n>=0 && m>=0);
	if(m>n)return 0;
	assert(n<=lim && m<=lim);
	return 1ll*ga[n]*invga[m]%mo*invga[n-m]%mo;
}
 
int suan(int n,int S,int up){
	int now = S-1>>1;
	int ans = binom(2*n,S);
	if(~S&1)dec(ans, binom(n,S/2)*1ll*binom(n,S/2)%mo);
	ans = 1ll*ans*inv[2]%mo;
	if(up>now)For(i,now+1,up)inc(ans, 1ll*binom(n,i)*binom(n,S-i)%mo);
	if(up<now)For(i,up+1,now)dec(ans, 1ll*binom(n,i)*binom(n,S-i)%mo);
	return ans;
}
 
int calc(int S,int n){
	int res = 0;
	if(S==2){
		For(i,1,S/2)inc(res,1ll*i*binom(n,i)%mo*binom(n,S-i)%mo);
	}else{
		res = suan(n-1,S-1,S/2-1);
		inc(res,suan(n-1,S-2,S/2-1));
		res = 1ll*res*n%mo;
	}
	res = 2ll*res%mo;
	if(~S&1)dec(res,S/2ll*binom(n,S/2)%mo*binom(n,S/2)%mo);
	return res;
}
 
int Main(int n){
	int res = 0;
	For(S,3,2*n-3){
		int an = 1;
		an = ga[S-1]*1ll*ga[2*n-3-S]%mo;
		an = 1ll*an*calc(S-1,n-2)%mo;
		inc(res,an);
	}
	return 1ll*res*invga[2*n-3]%mo;
}
 
int main(int argc, char* argv[]){
	// hello();
	int n = IN();
	*ga = 1;
	For(i,1,lim)ga[i] = 1ll*ga[i-1]*i%mo;
	invga[lim] = Pow(ga[lim],mo-2);
	dto(i,lim,1)invga[i-1] = invga[i]*1ll*i%mo, inv[i] = 1ll*invga[i]*ga[i-1]%mo;
	int an = Main(n);
	print(1ll*an*tri(n)%mo);
}