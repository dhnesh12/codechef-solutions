#include <stdio.h>
#include<string.h>
int main(void) {
    int s,n,no,lf;
    char b[100001];
    scanf("%d",&s);
    while(s--)
    { lf=0;
        scanf("%d",&n);
        while(n--)
        {
            scanf("%d",&no);
            lf^=no;
        }
        printf("%d\n",lf);
    }
	// your code goes here
	return 0;
}

