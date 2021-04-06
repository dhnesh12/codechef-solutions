#include <stdio.h>

int main(void) {
	// your code goes here
	int t,N;
	scanf("%d",&t);
	while(t--)
	{
	    int i,j;
	    scanf("%d",&N);
	    char f[N][20],l[N][20];
	    for(i=0;i<N;i++)
	    {
	        scanf("%s\n %s\n",&f[i],&l[i]);
	    }
	    for(i=0;i<N;i++)
	    {
	        int flag=0;
	        for(j=0;j<N;j++)
	        {
	            if((i!=j)&&(!strcmp(f[i],f[j])))
	            {
	                flag=1;
	                break;
	            }
	        }
	        if(flag==0)
	        printf("%s\n",f[i]);
	        else
	        printf("%s %s\n",f[i],l[i]);
	    }
	}
	return 0;
}

