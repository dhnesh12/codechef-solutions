#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
typedef long long ll;
const int maxn=1e5+5,maxq=1e6+5,maxp=1e7+5,tt=1e9+7,inf=233333;
int N,K,p[maxn],MinD[maxn],Alp,T,A,B,C[maxq],M,Ans;
bool vis[maxn];
typedef std::pair<int,int> pii;
inline void read(int &Res){
	char ch=getchar();
	for (Res=0;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
}
std::vector<pii> E[maxn];
inline int Power(int x,int y){
	int S=1;
	for (;y;y>>=1,x=(ll)x*x%tt) if (y&1) S=(ll)S*x%tt;
	return S;
}
namespace PT{
	int Root[maxn],tot,x,y,z,M;
	struct Node{int l,r,x;}T[maxp];
	inline void Clear(int len){T[tot=0].x=1,M=len;}
	void Update(int &p,int L,int R){
		T[++tot]=T[p],p=tot;
		if (x<=L&&R<=y){T[p].x=(ll)T[p].x*z%tt; return;}
		int mid=(L+R)>>1;
		if (x<=mid) Update(T[p].l,L,mid);
		if (y>mid) Update(T[p].r,mid+1,R);
	}
	void Query(int p,int L,int R){
		if (!p) return;
		z=(ll)z*T[p].x%tt;
		int mid=(L+R)>>1;
		if (x<=mid) Query(T[p].l,L,mid);
			else Query(T[p].r,mid+1,R);
	}
	inline void Update(int i,int l,int r,int v){x=l,y=r,z=v,Update(Root[i],1,M);}
	inline int Query(int i,int v){return x=v,z=1,Query(Root[i],1,M),z;}
}
inline void Pre(int N){
	for (int i=2;i<=N;++i){
		if (!vis[i]) MinD[p[Alp++]=i]=i;
		for (int j=0;j<Alp;++j){
			if (i*p[j]>N) break;
			vis[i*p[j]]=true,MinD[i*p[j]]=p[j];
			if (!(i%p[j])) break;
		}
	}
	for (int i=2;i<=N;++i) if (MinD[i]==i) E[i].push_back(pii(0,inf));
	PT::Clear(N);
	for (int i=2,tmp,val,cnt;i<=N;++i)
		for (PT::Root[tmp=i]=PT::Root[i-1];tmp>1;E[val].push_back(pii(i,cnt))){
			for (cnt=0,val=MinD[tmp];!(tmp%val);tmp/=val,++cnt);
			E[val].push_back(pii(i,0));
			for (pii pre,lst;E[val].back().second<=cnt;){
				lst=E[val].back(),E[val].pop_back(),pre=E[val].back();
				if (lst.second<cnt) PT::Update(i,pre.first+1,lst.first,Power(val,cnt-lst.second));
			}
		}
}
int main(){
	read(T),read(N),read(K),read(A),read(B),read(M),Pre(M);
	printf("%d\n",Ans=PT::Query(N,N-K+1));
	for (int i=1;i<T;++i) read(C[i]);
	for (int i=1,D;i<T;++i) read(D),N=((ll)A*Ans+C[i])%M+1,K=((ll)B*Ans+D)%N+1,printf("%d\n",Ans=PT::Query(N,N-K+1));
	return 0;
}