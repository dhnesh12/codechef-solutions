#include<stdio.h>
int main() {
    int t;
    scanf("%d",&t);
    while (t--)
    {
        int n,d,risk=0,days1,days2,x;
        scanf("%d %d", &n, &d);
        for(int i=0;i<n;i++)
        {
            scanf("%d",&x);
            if(x<=9||x>=80)
            {
                risk++;
            }
        }
        if(risk%d==0)
        {
            days1= risk/d;
        }
        else
        {
            days1=(risk/d)+1;
        }
        if((n-risk)%d==0)
        {
            days2=(n-risk)/d; 
        }
        else
        { 
            days2=((n-risk)/d)+1; 
        }
        printf("%d\n",days1+days2);
    }
    return 0;
}