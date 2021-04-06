#include <stdio.h>
#include <stdlib.h>
#define MOD 1000000007
long long modInverse(long long a,long long mod);void solve_r(long long n,long long *res,int SIZE);void solve_a(long long n,long long *res,int SIZE);long long p[300],e[300],first_line[300][300],two_help[300][300],A[300][300];
int main(){int T,n,Q,i,j,k,l;long long x;scanf("%d",&T);while(T--){scanf("%d%d",&n,&Q);for(i=0;i<n;i++){scanf("%lld",p+i);}e[0]=p[0];for(i=1;i<n;i++){for(j=x=0;j<i;j++){if(j%2){x=(x-e[i-j-1]*p[j]%MOD+MOD)%MOD;}else{x=(x+e[i-j-1]*p[j])%MOD;}}if(j%2){x=(x-p[i]+MOD)%MOD;}else{x=(x+p[i])%MOD;}e[i]=x*modInverse(i+1,MOD)%MOD;}for(i=0;i<n;i++){for(j=0;j<n;j++){A[i][j]=0;}}for(i=0;i<n;i++){if(i%2){A[0][i]=MOD-e[i];}else{A[0][i]=e[i];}}for(i=0;i<n-1;i++){A[i+1][i]=1;}for(i=0;i<n;i++){first_line[0][i]=0;}first_line[0][0]=1;for(i=1;i<n;i++){for(j=0;j<n;j++){first_line[i][j]=first_line[i-1][0]*A[0][j]%MOD;if(j!=n-1){first_line[i][j]=(first_line[i][j]+first_line[i-1][j+1])%MOD;}}}for(i=0;i<n;i++){two_help[0][i]=A[0][i];}for(i=1;i<n-1;i++){for(j=1;j<n;j++){two_help[i][j-1]=two_help[i-1][j];}two_help[i][n-1]=0;for(j=0;j<n;j++){two_help[i][j]=(two_help[i][j]+two_help[i-1][0]*two_help[0][j])%MOD;}}while(Q--){scanf("%lld",&x);solve_r(x-n,e,n);for(i=x=0;i<n;i++){x=(x+e[i]*p[n-i-1])%MOD;}printf("%lld ",x);}printf("\n");}return 0;}
long long modInverse(long long a,long long mod){long long b0 = mod, t, q;long long x0 = 0, x1 = 1;while (a > 1) {q = a / mod;t = mod; mod = a % mod; a = t;t = x0; x0 = x1 - q * x0; x1 = t;}if (x1 < 0) x1 += b0;return x1;}
void solve_r(long long n,long long *res,int SIZE){int i,j;long long t[SIZE];if(n<SIZE){for(i=0;i<SIZE;i++){res[i]=first_line[n][i];}return;}solve_a(n,t,SIZE);for(i=0;i<SIZE;i++){for(j=res[i]=0;j<SIZE;j++){res[i]=(res[i]+t[j]*first_line[SIZE-j-1][i])%MOD;}}return;}
void solve_a(long long n,long long *res,int SIZE){int i,j;long long t[SIZE],*tt;if((n>=SIZE && n<2*SIZE-1) || (SIZE==1 && n==SIZE)){for(i=0;i<SIZE;i++){res[i]=two_help[n-SIZE][i];}return;}if(n%2){solve_a(n-1,t,SIZE);for(i=0;i<SIZE-1;i++){res[i]=t[i+1];}res[SIZE-1]=0;for(i=0;i<SIZE;i++){res[i]=(res[i]+t[0]*A[0][i])%MOD;}}else{solve_a(n/2,t,SIZE);tt=(long long*)malloc(2*SIZE*sizeof(long long));for(i=0;i<2*SIZE;i++){tt[i]=0;}for(i=0;i<SIZE;i++){for(j=0;j<SIZE;j++){tt[i+j]=(tt[i+j]+t[i]*t[j])%MOD;}}for(i=0;i<SIZE;i++){res[i]=tt[i+SIZE-1];}for(i=0;i<SIZE-1;i++){for(j=0;j<SIZE;j++){res[j]=(res[j]+tt[i]*two_help[SIZE-i-2][j])%MOD;}}free(tt);}return;}