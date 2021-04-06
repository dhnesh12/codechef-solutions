#include <stdio.h>

int main(void) {
	int t;
	scanf("%d", &t);
	while(t--)
	{
	    int n;
	    scanf("%d",&n);
	    printf("%d\n",n);
	    for (int i=1;i<=n;i++)
	    {
	        printf("%d\n",n);
	        for (int j=1;j<=n;j++)
	        {
	            int recipe1=i+j-1, recipe2=i+j;
	            if (recipe1>n && recipe1%n!=0)
	                recipe1=recipe1%n;
	            else if (recipe1%n==0)
	                recipe1=n;
	            if (recipe2>n && recipe2%n!=0)
	                recipe2=recipe2%n;
	            else if (recipe2%n==0)
	                recipe2=n;
	            printf("%d %d %d\n",j,recipe1,recipe2);
	        }
	    }
	    
	}
	return 0;
}


