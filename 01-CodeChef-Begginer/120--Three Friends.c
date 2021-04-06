#include <stdio.h>
#include<math.h>
int main(void) {
    int s,a,b,c;
    scanf("%d",&s);
    while(s--)
    {
        scanf("%d%d%d",&a,&b,&c);
        a=abs(a);
        b=abs(b);
        c=abs(c);
        if(a+b==c || b+c==a || c+a==b)
            printf("yes\n");
        else
            printf("no\n");
    }
	// your code goes here
	return 0;
}



