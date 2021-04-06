// RDF

#include <stdio.h>

inline int getn(){
	int n=0, c=getchar_unlocked();
	while(c < '0' || c > '9') c = getchar_unlocked();
	while(c >= '0' && c <= '9')
		n = (n<<3) + (n<<1) + c - '0', c = getchar_unlocked();
	return n;
}
double a[100001][31] = {{0}};
int main(){
	int T = getn(), N, K, i,j;
	a[2][1] = 0.5, a[3][1] = 1.0, a[3][2] = 1.0/6.0;
	for(i = 4; i < 100001; i++){
		for(j = 1; j <= 30 && j < i; j++){
			if(j == 1) a[i][j] = a[i-1][j] + 0.5;
			else a[i][j] = (a[i-1][j-1] + a[i-1][j]*(i-1))/(double)i;
			if(a[i][j] <= 1.0/500000.0) break;
		}
	}
	while(T--){
		N = getn(), K = getn();
		if(!K) printf("%d\n",N);
		else if(K <= 30 && N > K) printf("%.7lf\n",a[N][K]);
		else printf("0\n");
	}
	return 0;
}
