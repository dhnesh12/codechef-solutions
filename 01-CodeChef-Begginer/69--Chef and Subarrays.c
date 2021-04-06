#include<stdio.h>
 
int main()
{
    int testcase;
    int number,count,i,j,add,mul,arr[100];
    scanf("%d",&testcase);
    while(testcase>0)
    {
        testcase--;
        scanf("%d",&number);
        count = 0;
        for(i=0;i<number;i++)
            scanf("%d",&arr[i]);
        for(i =0; i<number;i++)
        {
            add = arr[i];
            mul = arr[i];
            for(j=i+1;j<number;j++)
            {
                add += arr[j];
                mul *= arr[j];
                if(add == mul)
                {
                    count++;
                }
            }
        }
        printf("%d\n",count+number);
     }
    }  