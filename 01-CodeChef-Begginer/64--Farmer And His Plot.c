#include<stdio.h>
int gcd(int x,int y)
{
    if(y==0)
    return x;
    else
    return gcd(y,x%y);
}
main()
{
    int s,x,y,z; 
    scanf("%d",&s);
    while(s--)
    {
        scanf("%d%d",&x,&y);
        z=gcd(x,y);
        printf("%d\n",(x*y)/(z*z));
    }
    return 0;
}  