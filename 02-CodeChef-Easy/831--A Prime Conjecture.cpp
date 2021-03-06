#include <cstdio>
 
int isprime(int N){
	if(N<2 || (!(N&1) && N!=2))
		return 0;
	for(int i=3; i*i<=N; i+=2){
		if(!(N%i))
			return 0;
	}
	return 1;
}
 
void solve(int N, int &p1, int &p2, int &p3){
	for(p3=100; p3>0; p3--){
		if(p3*p3*p3<N && isprime(p3)){
			for(p2=2; p2*p2+p3*p3*p3<N; p2++){
				p1=N-p3*p3*p3-p2*p2;
				if(isprime(p2) && isprime(p1))
					return;
			}
		}
	}
	p1=p2=p3=0;
}
 
int main(){
	int N, p1, p2, p3;
	while(scanf("%d", &N) && N){
		solve(N, p1, p2, p3);
		printf("%d %d %d\n", p1, p2, p3);
	}
}