#include <stdio.h>

int main(void) 
{
	int i,testcases,n1,n2,sum,number,sticks;
	int matches[10]={6,2,5,5,4,5,6,3,7,6};
	scanf("%d",&testcases);
	for(i=1;i<=testcases;i++)
	{
		scanf("%d %d",&n1,&n2);
		sticks=0;
		sum=n1+n2;
		while(sum)
		{
			number=sum%10;

			sticks=sticks+matches[number];
			sum/=10;
		}
		printf("%d\n",sticks);
	}

	return 0;
}

