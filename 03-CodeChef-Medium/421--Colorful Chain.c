#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define LL long long
#define M 1000000007
#define siz 200000
int n, m;
LL o[siz],v[siz],w[siz];
LL losen(int n)
{
    int i=-1,j,k;
    LL res=0;
    if(n<=0)
    return 1;
    if(o[n]>=0)
    return o[n];
    for(;++i<m; res=(res+losen(n-i-1))%M);
    return o[n]=res;
}
main()
{
    int fall, i=0, j, k, l, x, y;
    LL res;
    for(w[0]=1; ++i<siz; w[i]=(w[i-1]*i)%M);
    for(scanf("%d",&fall); fall--&&scanf("%d%d",&n,&m); res%=M,res=(res*w[m])%M,res%=M,printf("%d\n",(int)res))
	{
	    for(v[0]=!(i=o[0]=v[1]=1); i<n+1; i++)
	    {
	        y=i-1;
	        x=i-m;
	        o[i]=0;
	        if(x<0)
			{
			    o[i]=-x;
			    x=0;
			}
			o[i]+=v[y+1]-v[x];
			o[i]%=M;
			if(o[i]<0)
			o[i]+=M;
			v[i+1]=(v[i]+o[i])%M;
	    }
	    for(i=-!(res=0); ++i<m; res+=(n-i-m-1>=0)?((o[n-i-m-1]*(m-i))%M):((m-i)%M));
	}
	return 0;
}