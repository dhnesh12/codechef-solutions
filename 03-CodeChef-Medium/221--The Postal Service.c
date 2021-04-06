#include <stdio.h>
#include <string.h>
 
#define LL long long
 
typedef struct {
LL x, y;
} xta1;
 
LL abs(LL x){return x<0?-x:x;}
 
main()
{
LL fall, N, qq, i, j, Q, res, a1, a2, a3, a4, a5, a6, a7;
int B[500];
xta1 A[500];
for(scanf("%lld",&fall); fall--&&scanf("%lld",&N);)
	{
	for(i=0; i<N; scanf("%lld",&(A[i++].x)));
	for(i=0; i<N; scanf("%lld",&(A[i++].y)));
	for(qq=-scanf("%lld",&Q); ++qq<Q; res=A[a3].x,res=A[a3].y?res+a2:res-a2,printf("%lld %lld\n",res,a7))
		{
		for(memset(B,0,sizeof(B)),scanf("%lld %lld",&a1,&a2),a3=a1,a5=a1,B[a3]=!(a7=0); 1;)
			{
			for(a6=(A[a3].y)?1:-1,a4=-1,i=a5; i>=0&&i<N; i+=a6)
				if(A[i].y!=A[a3].y&&!B[i])
					{
					if(abs(A[i].x-A[a3].x)>2*a2) break;
					B[i]=1;
					a4=i;
					a7++;
					break;
					}
			if(a4==-1) break;
			a5=a3;
			a3=a4;
			}
		}
	}
return 0;
}
 