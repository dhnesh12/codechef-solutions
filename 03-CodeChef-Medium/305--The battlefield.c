#include <stdio.h>
#define siz 2000
#define _T for(i=2;i<=siz;i++)
long long a[siz+10][siz+10];
main()
{
int fall, i, j, n, k;
_T for(j=0; ++j<i; a[i][j]=(j==1)?(2):(((j*a[i-1][j]+2*a[i-1][j-1]+(i-j)*a[i-1][j-2])%30041975)));
_T for(j=i-1; --j>0; a[i][j]=(a[i][j]+a[i][j+1])%30041975);
for(scanf("%d",&fall); fall--; scanf("%d %d",&n,&k),printf("%lld\n",a[n][k+1]));
return 0;
}