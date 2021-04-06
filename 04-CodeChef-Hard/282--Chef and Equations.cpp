//#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,a,b) for(i=(a);i<=(b);++i)
#define per(i,a,b) for(i=(a);i>=(b);--i)
#define REP(i,a,b) for(i=(a);i< (b);++i)
#define PER(i,a,b) for(i=(a);i> (b);--i)
const int N=1<<17;
const ll p=998244353ll,pp=p*p;
inline ll expo(ll a,int b=998244351){
	ll c=1ll;
	while(b){
		if(b&1)c=c*a%p;
		b>>=1; a=a*a%p;
	}
	return c;
}
inline void add(ll &a){if(a>= p)a-=p;}
inline void sub(ll &a){if(a<0ll)a+=p;}
namespace ntt{
	ll G[N];
	int R[N],n;ll ni;
	inline void I0(int n){
		register int i,k;ll wn,wnk;
		for(k=1;k!=n;k<<=1){
			wn=expo(3ll,p/(k<<1));
			G[k]=wnk=1ll;
			REP(i,1,k)G[k|i]=wnk=wnk*wn%p;
		}
	}
	struct ntt_init{ntt_init(){I0(N);}}ntt_init_0;
	inline void I(int _){
		ni=expo(n=_);
		register int i,k;
		for(k=0;;++k)if((2<<k)==n)break;
		REP(i,1,n)R[i]=(R[i>>1]>>1)|((i&1)<<k);
	}
	#define NTT false
	#define INTT true
	inline void T(ll *A,bool intt){
		register int k,i,j;
		ll e,o;
		//REP(i,0,n)printf("%lld ",A[i]);printf("INTT=%d\n",intt);
		REP(i,1,n)if(R[i]<i)swap(A[R[i]],A[i]);
		for(k=1;k!=n;k<<=1){
			for(i=0;i!=n;i+=(k<<1)){
				REP(j,i,i|k){
					e=A[j];o=A[j|k]*G[(j^i)|k]%p;
					add(A[j  ]=e+o);
					sub(A[j|k]=e-o);
				}
			}
		}
		//printf("G41=%lld G41^2=%lld\n",G[3],G[3]*G[3]%p);
		if(intt){
			reverse(A+1,A+n);
			REP(i,0,n)A[i]=A[i]*ni%p;
		}
		//REP(i,0,n)printf("%lld ",A[i]);printf("\n");
	}
	namespace inv{
		//2n<=N
		ll B[N],J[N];
		inline void sol(ll *A,ll *X,int n){
			int i,j;
			J[0]=expo(A[0]);
			for(i=1;i!=n;i<<=1){
				I(i<<2);
				REP(j,0,i<<1)B[j]=A[j];REP(j,i<<1,i<<2)B[j]=0ll;
				REP(j,i,i<<2)J[j]=0ll;
				T(B,NTT);
				T(J,NTT);
				REP(j,0,i<<2)J[j]=J[j]*((2ll+pp-J[j]*B[j])%p)%p;
				T(J,INTT);
			}
			REP(i,0,n)X[i]=J[i];
		}
	};
	namespace divmod{
		//2n<=N
		ll T1[N],T2[N],T3[N];
		inline void sol(ll *A,ll *B,ll *Q,ll *R,int a,int b){
			int i,n=1;
			while(n<=a)n<<=1;
			rep(i,0,a)T1[i]=A[a-i];REP(i,a+1,n)T1[i]=0;
			rep(i,0,b)T2[i]=B[b-i];REP(i,b+1,n)T2[i]=0;
			inv::sol(T2,T3,n);
			REP(i,a+1,n)T3[i]=0ll;
			REP(i,n,n<<1)T1[i]=0ll;
			REP(i,n,n<<1)T2[i]=0ll;
			REP(i,n,n<<1)T3[i]=0ll;
			I(n<<=1);
			T(T1,NTT);
			T(T3,NTT);
			REP(i,0,n)T1[i]=T1[i]*T3[i]%p;
			T(T1,INTT);
			reverse(T1,T1+(a-b+1));
			REP(i,a-b+1,n)T1[i]=0ll;
			if(Q)rep(i,0,a-b)Q[i]=T1[i];
			if(R){
				T(T1,NTT);
				rep(i,0,b)T2[i]=B[i];
				T(T2,NTT);
				REP(i,0,n)T1[i]=T1[i]*T2[i]%p;
				T(T1,INTT);
				REP(i,0,b)R[i]=(A[i]-T1[i]+p)%p;
			}
		}
	};
	const int K=17,K2=11;
	namespace multi_evaluate{
		//2n<=N,2n<=2^K,do brute force at n<=2^K2
		ll P[K][N],R[N],T1[N],T2[N],n,m,k,*X;
		inline void build(ll *X0,int _){
			X=X0;n=_;
			int i,j,t;
			REP(i,0,n){sub(P[0][i<<1]=-X[i]);P[0][i<<1|1]=1ll;}
			for(m=1,k=0;;m<<=1,++k)if(m>=n)break;
			REP(i,n,m){P[0][i<<1]=0ll;P[0][i<<1|1]=1ll;}
			REP(i,0,k){
				I(4<<i);
				for(j=0;j!=m<<1;j+=4<<i){
					rep(t,0,1<<i)T1[t]=P[i][j|t     ];REP(t,(1<<i)+1,4<<i)T1[t]=0ll;
					rep(t,0,1<<i)T2[t]=P[i][j|t|2<<i];REP(t,(1<<i)+1,4<<i)T2[t]=0ll;
					T(T1,NTT);
					T(T2,NTT);
					REP(t,0,4<<i)T1[t]=T1[t]*T2[t]%p;
					T(T1,INTT);
					rep(t,0,2<<i)P[i+1][j|t]=T1[t];
				}
			}
			//rep(i,0,m)printf("%lld ",P[k][i]);printf("\n");
		}
		inline void sol(ll *A,ll *S,int a){
			int i,j,t,z;
			if(a<m){rep(t,0,a)R[t]=A[t];REP(t,a+1,m)R[t]=0ll;}
			else divmod::sol(A,P[k],NULL,R,a,m);
			per(i,k-1,0){
				if(i<K2){
					ll f;
					for(j=0;j!=m;j+=2<<i){
						REP(z,j,j+(2<<i))if(z<n){
							f=0ll;
							per(t,(2<<i)-1,0)f=(f*X[z]+R[j|t])%p;
							S[z]=f;
						}
					}
					break;
				}else for(j=0;j!=m;j+=2<<i){
					REP(t,0,2<<i)T1[t]=R[j|t];
					divmod::sol(T1,P[i]+( j      <<1),NULL,R+ j      ,(2<<i)-1,1<<i);
					divmod::sol(T1,P[i]+((j|1<<i)<<1),NULL,R+(j|1<<i),(2<<i)-1,1<<i);
				}
			}
		}
	};
};
ll A[N],X[N],T1[N],T2[N],FZ[N],FM[N];
int main(){
	//freopen("A_2.in","r",stdin);
	//freopen("A.out","w",stdout);
	int n,m=1,i,j,k;
	scanf("%d",&n);
	while(m<n)m<<=1;
	REP(i,0,n)scanf("%lld",&A[i]);
	//REP(i,0,n){X[i<<1]=A[i];X[i<<1|1]=1ll;}
	//REP(i,n,m)X[i<<1]=1ll;
	//printf("Init m=%d\n",m);
	//=================================================================
	/*
	for(k=1;k!=m;k<<=1){
		//printf("k=%d\n",k);
		ntt::I(k<<2);
		for(i=0;i!=m<<1;i+=(k<<2)){
			rep(j,0,k)T1[j]=X[j|i     ];REP(j,k+1,k<<2)T1[j]=0ll;
			rep(j,0,k)T2[j]=X[j|i|k<<1];REP(j,k+1,k<<2)T2[j]=0ll;
			ntt::T(T1,NTT);
			ntt::T(T2,NTT);
			REP(j,0,k<<2)T1[j]=T1[j]*T2[j]%p;
			ntt::T(T1,INTT);
			rep(j,0,k<<1)X[j|i]=T1[j];
		}
	}*/
	ntt::multi_evaluate::build(A,n);
	int o=ntt::multi_evaluate::m-n;
	rep(i,0,n){
		if((n^i)&1)sub(X[i]=-ntt::multi_evaluate::P[ntt::multi_evaluate::k][i+o]);
		else X[i]=ntt::multi_evaluate::P[ntt::multi_evaluate::k][i+o];
	}
	//rep(i,0,n)printf("%lld ",X[i]);printf("\n");
	//fprintf(stderr,"\nTime = %dms\n",clock());
	//printf("X\n");
	//REP(i,0,m)printf("%lld ",X[i]);printf("\n");
	//=================================================================
	m<<=1;
	T1[0]=0ll;
	rep(i,1,n){
		if(i&1)T1[i]=X[i];
		else sub(T1[i]=-X[i]);
	}
	REP(i,n+1,m)T1[i]=0ll;
	per(i,n-1,0)scanf("%lld",&T2[i]);
	REP(i,n,m)T2[i]=0ll;
	ntt::T(T1,NTT);
	ntt::T(T2,NTT);
	REP(i,0,m)T1[i]=T1[i]*T2[i]%p;
	ntt::T(T1,INTT);
	REP(i,0,n)T1[i]=T1[i+n];
	//REP(i,0,n)printf("%lld ",T1[i]);printf("\n");
	ntt::multi_evaluate::sol(T1,FZ,n-1);
	//fprintf(stderr,"\nTime = %dms\n",clock());
	//REP(i,0,n)printf("%lld ",FZ[i]);printf("\n");
	//=================================================================
	rep(i,1,n){
		if(i&1)T2[i-1]=i*X[i]%p;
		else T2[i-1]=(p-i)*X[i]%p;
	}
	//REP(i,0,n)printf("%lld ",T2[i]);printf("T2\n");
	ntt::multi_evaluate::sol(T2,FM,n-1);
	//fprintf(stderr,"\nTime = %dms\n",clock());
	//REP(i,0,n)printf("%lld ",FM[i]);printf("\n");
	//=================================================================
	REP(i,0,n)printf("%lld ",FZ[i]*expo(FM[i])%p);
	//fprintf(stderr,"\nTime = %dms\n",clock());
	return 0;
}