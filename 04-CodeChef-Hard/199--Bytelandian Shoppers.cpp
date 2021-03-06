#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long int64;

#define MOD 1000000007

long long C[1001][1001];
void comb(int lim) {
	int n,r;
	C[0][0]=1;
	for (n=1;n<=lim;n++) {
		C[n][0]=1;
		for (r=1;r<=n-1;r++) {
			C[n][r]=(C[n-1][r-1]+C[n-1][r])%MOD;
		}
		C[n][n]=1;
	}
}

int64 modPow(int n, int k) {
	if (k==0) return 1;
	if (k%2==0) {
		int64 x=modPow(n,k/2);
		return (x*x)%MOD;
	} else {
		return (modPow(n,k-1)*n)%MOD;
	}
}

int64 fakt[40001], invFakt[40001];
void factorials(int lim) {
	fakt[0]=1; invFakt[0]=1;
	for (int i=1;i<=lim;i++) {
		fakt[i]=(fakt[i-1]*i)%MOD;
		invFakt[i]=modPow(fakt[i],MOD-2);
	}
}

int64 getC(int n, int r) {
	if (r>n) return 0;
	return (((fakt[n]*invFakt[n-r])%MOD)*invFakt[r])%MOD;
}

int64 f[202][202];
int64 g[202][202];

int main() {
	//gen(); return 0;
	//freopen("byteshop.in","r",stdin);
	comb(1000);
	factorials(40000);

	int tests;
	scanf("%d",&tests);
	while (tests--) {
		int N,M,R;
		scanf("%d %d %d",&N,&M,&R);
		memset(f,0,sizeof(f));
		for (int x=0;x<=N;x++) {
			for (int y=0;y<=M;y++) {
				f[x][y]=((getC((N-x)*(M-y),R)*C[N][x])%MOD*C[M][y])%MOD;
			}
		}
		int64 rez=0;
		for (int x=0;x<=N;x++) {
			for (int y=0;y<=M;y++) {
				if ((x+y)%2==0) rez+=f[x][y]; else rez-=f[x][y];
			}
		}
		rez%=MOD;
		if (rez<0) rez+=MOD;
		printf("%lld\n",rez);
	}
    return 0;
}

