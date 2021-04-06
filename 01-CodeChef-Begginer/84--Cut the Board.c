#include <stdio.h>
#include<stdlib.h>
int main(void) {
	int t,n,m;
	scanf("%d",&t);
	for(int i=0;i<t;i++)
	{
	    scanf("%d%d",&n,&m);
	    printf("%d\n",(n-1)*(m-1));
	}
	return 0;
}