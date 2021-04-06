#include <stdio.h>

int main(void) {
	// your code goes here
	int s,n,a[10000],b[10000],c,d,i;
	a[0]=0;
	scanf("%d",&s);
	while(s--)
	{
	    c=0;
	    scanf("%d",&n);
	    for(i=1;i<=n;i++)
	    {
	        scanf("%d",&a[i]);
	    }
	    for(i=1;i<=n;i++)
	    {
	        scanf("%d",&b[i]);
	    }
	    for(i=1;i<=n;i++)
	    {
	        d=a[i]-a[i-1];
	        if(b[i]<=d)
	        c++;
	    }
	    printf("%d\n",c);
	}
	return 0;
}

