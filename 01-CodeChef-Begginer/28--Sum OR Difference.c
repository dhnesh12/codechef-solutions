#include <stdio.h>

int main(void) {
	int a,b,sum,diff;
	scanf("%d",&a);
	scanf("%d",&b);
	if(a>b)
	{
	    diff=a-b;
	    printf("%d",diff);
	}
	else
	{
	    sum=a+b;
	    printf("%d",sum);
	}
	return 0;
}
