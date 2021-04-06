#include<stdio.h>
int main()
{
    int t, a, b, flag;
    char str[10];
    
    scanf("%d", &t);
    while(t!=0)
    {
        scanf("%d %d", &a, &b);
        flag=0;
        for(int x=1;x<=a;x++)
        {
            for(int y=1;y<=b;y++)
            {
                if((x+y)%2==0)
                {    
                    flag++;
                }
            }
        }
        printf("%d\n", flag);
        t--;
    }
    return 0;
}