#include <stdio.h>

int main(void) {
	// your code goes here
	int t;
	scanf("%d",&t);
	while(t--)
	{
	    int n,z,i,j;
	    char a[100000],temp,k;
	    scanf("%d",&n);
	    scanf("%s",a);
	    if(n%2!=0)
	    z=n-1;
	    else
	    z=n;
	    for(i=0; i<z-1; i+=2)
	    {
	       temp=a[i];
	       a[i]=a[i+1];
	       a[i+1]=temp;
	    }
	    for(i=0; i<n; i++)
	    {
	        k='z';
	        for(j='a'; j<='z'; j++)
	        {
	            if(a[i]==j)
	            {
	                a[i]=k;
	                break;
	            }
	            k=k-1;
	        }
	    }
	    printf("%s\n",a);
	}
	
	return 0;
}

