#include <stdio.h>

int main(void) {
	// your code goes here
	int t;
	scanf("%d",&t);
	while(t--)
	{
	    int n,i,j=0;
	    scanf("%d",&n);
	    long int hand[n],glove[n];
	    for(i=0;i<n;i++){
	        scanf("%ld",&hand[i]);
	    }
	    for(i=0;i<n;i++){
	        scanf("%ld",&glove[i]);
	    }
	    int front=1,back=1;
	    for(i=0;i<n;i++)
	    {
	        if(hand[i]>glove[i])
	        {
	            front=0;
	            break;
	        }
	    }
	    for(i=n-1;i>=0;i--)
	    {
	        if(hand[i]>glove[j])
	        {
	            back=0;
	            break;
	        }
	        j++;
	    }
	    
	    if(front==1 && back==1)
	        printf("both\n");
	    else if(front==1 && back==0)
	        printf("front\n");
	    else if(front==0 && back==1)
	        printf("back\n");
	    else
	        printf("none\n");
	}
	return 0;
}

