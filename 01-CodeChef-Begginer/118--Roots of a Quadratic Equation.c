#include <stdio.h>
#include<math.h>
int main(void) {
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    float r1,r2,c1;
    c1=sqrt(b*b-4*a*c);
    r1=(-1*b+c1)/(2*a);
    r2=(-1*b-c1)/(2*a);
    printf("%f\n%f",r1,r2);
	// your code goes here
	return 0;
}

