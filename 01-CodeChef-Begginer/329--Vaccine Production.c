#include <stdio.h>
int main()
{
    int D1,D2,V1,V2,p;
    int D,c=0;
    scanf("%d %d %d %d %d",&D1,&V1,&D2,&V2,&p);
     for (D=1;D<=100000; D++)
     {
        if(D1<=D)
        c=c+V1;
        
        if(D2<=D)
        c=c+V2;
        
        if(c>=p)
        break;
     }
     printf("%d",D);
    return 0;
}
