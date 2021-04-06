#include <stdio.h>
#include <string.h>
#include <math.h>
#define N 100

int main(void) {
	long int test_case,n,k,d,a[N],i;
	long long int total_question,days;
	scanf("%ld",&test_case);
	while(test_case--)
	{
	    scanf("%ld %ld %ld",&n,&k,&d);
	    total_question = 0;
	    for(i=0;i<n;i++)
	    {
	        scanf("%ld",&a[i]);
	        total_question += a[i];
	    }
	    days = total_question/k;
	    if(days>=d)
	    {
	        printf("%ld\n",d);
	    }
	    else
	    {
	        printf("%lld\n",days);
	    }
	}
	return 0;
}

