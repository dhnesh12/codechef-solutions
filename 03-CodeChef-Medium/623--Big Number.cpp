#include <cstdio>
#include <cctype>
#include <cstring>
const int maxn=1e6+5,tt=1e9+7;
int N,M,p2[maxn],K;
char s[maxn];
struct Node{int x,s,lz;}T[maxn<<2];
inline void read(int &Res){
	char ch=getchar();
	for (Res=0;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
}
inline void Mod(int &x){if (x>=tt) x-=tt;}
inline void Pushup(int p){Mod(T[p].x=T[p<<1].x+T[p<<1|1].x),Mod(T[p].s=T[p<<1].s+T[p<<1|1].s);}
inline void Work(int p){T[p].lz^=1,Mod(T[p].s=T[p].x+tt-T[p].s);}
void Build(int p,int L,int R){
	if (L>=R){
		if (s[L]=='1') K^=1;
		if (R<N) T[p].x=p2[N-R-1],T[p].s=s[L]=='1'?T[p].x:0;
		return;
	}
	int mid=(L+R)>>1;
	Build(p<<1,L,mid),Build(p<<1|1,mid+1,R),Pushup(p);
}
inline void Pushdown(int p){
	if (!T[p].lz) return;
	Work(p<<1),Work(p<<1|1),T[p].lz=0;
}
void Modify(int p,int L,int R,int x,int y){
	if (L<R) Pushdown(p);
	if (x<=L&&R<=y) return Work(p);
	int mid=(L+R)>>1;
	if (x<=mid) Modify(p<<1,L,mid,x,y);
	if (y>mid) Modify(p<<1|1,mid+1,R,x,y);
	Pushup(p);
}
inline int Query(){
	int Ret=T[1].s;
	if (s[N]=='1'||!(K&1)) Mod(++Ret);
	return Ret;
}
int main(){
	scanf("%s",s+1),N=strlen(s+1),read(M),*p2=1;
	for (int i=1;i<=N;++i) Mod(p2[i]=p2[i-1]<<1);
	Build(1,1,N),printf("%d\n",Query());
	for (int l,r;M--;printf("%d\n",Query())){
		read(l),read(r),K^=(r-l+1)&1;
		if (r==N) s[r--]^=1;
		if (l<=r) Modify(1,1,N,l,r);
	}
	return 0;
}