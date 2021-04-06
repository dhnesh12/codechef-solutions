#include <stdio.h>

int main(void) {
	int n;
    scanf("%d",&n);
    int a[n];
    int b=0,c=0;
    for (int i=1; i<=n; i++)
    {
        scanf("%d",&a[i]);
        b=b+a[i];
        c=c+i;
    }

    if(b==c){
        printf("YES");
    }
    else{
        printf("NO");
    }
	return 0;
}

