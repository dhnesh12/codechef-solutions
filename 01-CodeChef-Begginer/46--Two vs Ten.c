#include <stdio.h>

int main(void) {
    
	// your code goes here
	int s;
	scanf("%d",&s);
	while(s--)
	{
	    int n;
	    scanf("%d",&n);
	    if(n%5==0)
	    {
	        if(n%10==0)
	        {
	            printf("0\n");
	        }
	        else
	        {
	            printf("1\n");
	        }
	    }
	    else
	    {
	        printf("-1\n");
	    }
	}
	return 0;
}

