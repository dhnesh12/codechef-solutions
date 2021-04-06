#include <cstdio>
#include <cctype>
#include <bitset>
#include <cmath>
inline void read(int &Res){
	char ch=getchar();
	for (Res=0;!isdigit(ch);ch=getchar());
	for (;isdigit(ch);ch=getchar()) Res=(Res<<3)+(Res<<1)+ch-48;
}
int T,N,M,l,x[40005],y[40005];
std::bitset<1024> F[1024];
inline void Solve(){
	read(N),read(M),l=log2(N);
	for (int i=0;i<N;++i) F[i].reset();
	for (int i=0;i<M;++i) read(x[i]),read(y[i]),F[--x[i]].set(--y[i]),F[y[i]].set(x[i]);
	if ((1<<l)^N){puts("NO"); return;}
	if ((M<<2)^(l*(l+1)*N)){puts("NO"); return;}
	for (int i=0;i<N;++i) if ((F[i].count()<<1)^l*(l+1)){puts("NO"); return;}
	for (int i=0;i<M;++i) if ((F[x[i]]&F[y[i]]).count()^(l-1)*2){puts("NO"); return;}
	puts("YES");
}
int main(){
	for (read(T);T--;Solve());
	return 0;
}