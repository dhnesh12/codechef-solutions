#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>

using namespace std;

#define LL long long
#define debug(a) cerr<<#a<<": "<<a<<endl;
#define fgx cerr<<"--------------"<<endl;
#define dgx cerr<<"=============="<<endl;

inline int read(){
	int x=0,f=1; char c=getchar();
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-1;
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}

const int MAXN = 100010;
const int INF = 1e9;
const LL Mod = 1e9+7;

int T; LL C[1010][1010];
inline LL Pow(LL a,LL b,LL md){LL ret=1; for(;b;b>>=1,a=a*a%md) if(b&1) ret=ret*a%md; return ret;}
inline LL Add(LL &a,LL b){a=(a+b>=Mod?a+b-Mod:a+b);}
inline LL F(LL D,LL N){
	if(!D){ return 1; }
	LL ans=0;
	for(int i=0;i<=N;i++){
		LL opr=((i&1)?Mod-1:1);
		Add(ans,opr*Pow(2,Pow(D,i,Mod-1)*Pow(D+1,N-i,Mod-1)%(Mod-1),Mod)%Mod*C[N][i]%Mod);
	} return ans;
}
LL D,N;

int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	C[0][0]=1;
	for(int i=1;i<=1000;i++){
		C[i][0]=C[i][i]=1;
		for(int j=1;j<i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
	}
	T=read();
	while(T--){
		N=read(); D=read();
		printf("%lld\n",(F(D,N)-F(D-1,N)+Mod)%Mod);
	}
	return 0;
}
//2^((d-1)^i*d^(n-i))