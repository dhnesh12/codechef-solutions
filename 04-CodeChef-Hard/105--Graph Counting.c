#include <math.h>
#include <stdio.h>

int main()
{
	int T,casecnt,n,m,n1;
	scanf("%d",&T);
	for(casecnt=0;casecnt<T;casecnt++)
	{
		scanf("%d %d",&n,&m);
		if(n<=4)
		{
			if((n==1 && m==0) || (n==2 && m==1) || (n==3 && m==3) || (n==4 && m==6))
				printf("1\n");
			else if(n==4 && m==4)
				printf("3\n");
			else if(n==4 && m==5)
				printf("6\n");
			else
				printf("0\n");
		}
		else
		{
			n1=2*n-4;
			if(m==n1 || m==(n1+1))
				printf("%d\n",n*(n-1)/2);
			else
				printf("0\n");
		}
	}
	return 0;
}