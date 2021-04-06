#include<bits/stdc++.h>
using namespace std;

#define Uni All Right
#define REP(i,a,b) for(int i=(a),i##_end_=(b);i<i##_end_;++i)
#define DREP(i,a,b) for(int i=(a),i##_end_=(b);i>i##_end_;--i)
#define LREP(i,a) for(int i=Head[a];i;i=Next[i])
#define LL long long
#define Mod 1000000007 

static const int M=200004,N=50004;
int T,Mark[M],Eul[M],Ord[M];
LL L,R;
int Pri[M>>1],pt;
LL Pow(LL k,LL p,LL md){
	LL x=1;
	for(;p;k=(__int128)k*k%md,p>>=1)if(p&1)x=(__int128)x*k%md;
	return x; 
}
LL GetOrd(LL x,LL eul){
	if(!(x%2))return 1;
	LL res=eul,t=eul;
	REP(i,0,pt){
		if((LL)Pri[i]*Pri[i]>t)break;
		if(t%Pri[i])continue;
		int p=Pri[i];
		
		while(t%p==0)t/=p;
		while(res%p==0 && Pow(2,res/p,x)==1) res/=p;
	}
	if(t!=1)
		if(Pow(2,res/t,x)==1)res/=t;
	return res;
}
LL ltx,ltd;
LL GetOrd2(LL x,LL eul){
	if(x<M)return Ord[x];
	else if(ltx==x)return ltd;
	else return ltx=x,ltd=GetOrd(x,eul);
}
void Init(){
	REP(i,2,M){
		if(!Mark[i]){
			Pri[pt++]=i;
			Eul[i]=i-1;
			Ord[i]=GetOrd(i,Eul[i]);
		}
		REP(j,0,pt){
			int k=Pri[j]*i;
			if(k>=M)break;
			Mark[k]=Pri[j];
			if(!(i%Pri[j]))Eul[k]=Eul[i]*Pri[j];
			else Eul[k]=Eul[i]*(Pri[j]-1);
			Ord[k]=GetOrd(k,Eul[k]);
			if(!(i%Pri[j]))break;
		}
	}
}
LL P[N][20];
int V[N],Pv[20];
LL Res,Cnt;
int SqR,q,mx;
LL s;
inline LL LCM(LL a,LL b){return a/__gcd(a,b)*b;}
LL Calc(LL *P,LL d){
	if(d==1)return 1;
	LL Eul=1,Ord=1;
	REP(i,0,mx)if(Pv[i]){
		LL u=P[i],ep=P[i]-1;
		REP(j,1,Pv[i])u*=P[i],ep*=P[i];
		Ord=LCM(Ord,GetOrd2(u,ep));
		Eul*=ep;
	}
	return Eul/Ord;
}
void Solve(LL *P,int x,LL d){//d=1,eul=ord=1
	Pv[x]=0;
	if(x<mx)Solve(P,x+1,d);
	if(x==mx){
		Cnt+=Calc(P,d);
		return;
	}
	
	d*=P[x],++Pv[x];
	while(d<=s && !(s%d)){
		Solve(P,x+1,d);
		d*=P[x],++Pv[x];
	}
}
LL Work(){
	LL _R=R,_L=L;
	++R;
	if(L&1)--L;
	
	SqR=sqrt(R+1),q=R-L+1;

	REP(i,0,q)V[i]=0;
	REP(i,0,pt){
		int p=Pri[i];
		if(p>SqR)break;
		LL j=R/p*p-L;
		for(;j>=0;j-=p){
			P[j][V[j]++]=p;
		}
	}
	Res=0;
	LL as=0;
	REP(i,1,q){
		LL u=L+i,sp=1;
		REP(j,0,V[i]){
			int p=P[i][j];
			while(!(u%p))u/=p;
		}
		if(u!=1)P[i][V[i]++]=u;
		int t=0;
		if(i==1 && L!=_L)t=-1;
		if(i==q-1 && R!=_R)t=1;
		mx=V[i];
		Cnt=0,s=L+i;
		Solve(P[i],0,1),--Cnt;
//		cerr<<s<<','<<Cnt<<','<<t<<endl;
		if(t<=0)Res+=Pow(26,Cnt+1,Mod);
		if(t>=0)Res+=Pow(26,Cnt,Mod);
		++i;
	}
	return Res%Mod;
}
int Vis[M];
int Work(int n){
	int s=0;
	n++;
	REP(i,1,n)if(Vis[i]!=n){
		for(int j=i;Vis[j]!=n;j=(j<<1)%n)
			Vis[j]=n;
		++s;
	}
	return s;
}
//LL Phi(LL n){
//	LL Res=1;
//	for(int i=2;(LL)i*i<=n;++i)if(!(n%i)){
//		Res*=i-1,n/=i;
//		while(!(n%i))Res*=i,n/=i;
//	}
//	if(n!=1)Res*=n-1;
//	return Res;
//}
//int PW(LL k,int p,int md){
//	LL x=1;
//	for(;p;k=k*k%md,p>>=1)if(p&1)x=(x*k)%md;
//	return x;
//}
int main(){
//	cerr<<Work(44)<<','<<Work(46)<<','<<Work(48)<<','<<Work(50)<<endl;
	Init();
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld",&L,&R);
		printf("%lld\n",Work());
	}
	return 0;
}