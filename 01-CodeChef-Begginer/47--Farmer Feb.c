#include <stdio.h>

int main(void) {
	// your code goes here
	int t;
	scanf("%d",&t);
	while(t--)
	{
	    int f,s,count=0,sum=0,i;
	    scanf("%d %d",&f,&s);
	    sum=f+s+1;
	    count=0;
	    while(++count)
	    { int c=0;
	        for(i=2;i<=sum;i++)
	        if(sum%i==0)
	        c++;
	        if(c==1)
	       { printf("%d\n",count);
	        break;
	       }
	       else
	       sum+=1;
	    }
	}
	   
	   
	    return 0;
}

