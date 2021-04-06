#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<ctime>
#include<cstdlib>
#include<queue>
#include<algorithm>
#include<map>
#include<set>
#include<vector>
using namespace std;
typedef long long ll;
ll Rd(){
	ll ans=0;bool fh=0;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-') fh=1; c=getchar();}
	while(c>='0'&&c<='9') ans=ans*10+c-'0',c=getchar();
	if(fh) ans=-ans;
	return ans;
}
const ll MOD=1E9+7;
#define _ %MOD
ll PMod(ll x){
	if(x>=MOD) return x-MOD;
	else if(x<0) return x+MOD;
	return x;
}
ll QPow(ll x,ll up){
	x=PMod(x);ll ans=1;
	while(up)
		if(up%2==0) x=x*x _,up/=2;
		else ans=ans*x _,up--;
	return ans;
}
ll Inv(ll x){return QPow(x,MOD-2);}

const ll MXN=1E6+5;
char str[MXN];
void Decode(bool A[]){
	cin.getline(str,MXN);
	ll sLen=strlen(str);
	for(ll i=0;i<sLen;i++){
		ll t;
		if(str[i]>='a'&&str[i]<='z') t=str[i]-'a';
		else t=str[i]-'A'+26;
		for(ll j=5;j;t/=2,j--) A[i*5+j]=t%2;
	}
}
ll N,M;bool S1[MXN],S2[MXN];
ll nxt[MXN];
void SpawnNxt(){
	nxt[1]=0;
	for(ll i=2,p=0;i<=N;i++){
		while(S1[i]!=S1[p+1]&&p) p=nxt[p];
		if(S1[i]==S1[p+1]) p++;
		nxt[i]=p;
	}
}
ll fxt[MXN];
void SpawnFxt(){//False Next (µÚiÎ»È¡·´ºóµÄnxt)
	fxt[1]=0;
	for(ll i=2,p=0;i<=N;i++){
		p=nxt[i-1];
		while((S1[i]^1)!=S1[p+1]&&p) p=nxt[p];
		if((S1[i]^1)==S1[p+1]) p++;
		fxt[i]=p;
	}
}
ll pip[MXN];
void Match(){
	pip[0]=0;
	for(ll i=1,p=0;i<=M;i++){
		while(S2[i]!=S1[p+1]&&p) p=nxt[p];
		if(S2[i]==S1[p+1]) p++;
		pip[i]=p;
	}
}

class Line{public:
	ll k,b;
	Line(){}
	Line(ll k,ll b){
		this->k = k;
		this->b = b;
	}
	ll Calc(ll x){return (k*x+b)_;}
};
Line operator + (const Line A,const Line B){return Line(PMod(A.k+B.k),PMod(A.b+B.b));}
Line operator - (const Line A){return Line(PMod(-A.k),PMod(-A.b));}
Line operator - (const Line A,const Line B){return A+(-B);}
Line operator + (const Line A,const ll e){return A+Line(0,e);}
Line operator - (const Line A,const ll e){return A-Line(0,e);}
Line operator * (const Line A,const ll e){return Line(A.k*e _,A.b*e _);}
Line operator * (const ll e,const Line A){return A*e;}

Line cof[MXN];
ll f[MXN];
void Solve(){
	bool fin=0;for(ll i=1;i<=M;i++) if(pip[i]==N) fin=1;
	if(fin){printf("0\n");return;}
	
	cof[0]=Line(1,0);
	for(ll i=0;i<N;i++)
		cof[i+1]=2*cof[i]-cof[fxt[i+1]]-2;
	f[0]=PMod(0-cof[N].b)*Inv(cof[N].k) _;
	for(ll i=1;i<=N;i++)
		f[i]=cof[i].Calc(f[0]);
	ll Ans=f[pip[M]];
	printf("%lld\n",Ans);
}
int main(){
	//freopen("pizza.in","r",stdin);
	//freopen("pizza.out","w",stdout);
	ll T=Rd();while(T--){
		N=Rd();Decode(S1);S1[N+1]=-1;
		M=Rd();Decode(S2);S2[M+1]=-1;
		SpawnNxt();
		SpawnFxt();
		Match();
		Solve();
	}
	return 0;
}