/*  AUTHOR:AKASH JAIN
*   USERNAME:akash19jain    
*   DATE:21/05/2019 
*/
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#define MOD 1000000007

int main()
{
    long long t=1;
    //scanf("%lld",&t);
    while(t--)
    {
        long long n,s;
        scanf("%lld%lld",&n,&s);
        
        long long arr[s][n+1];
        memset(arr,0,sizeof(arr));
        long long x;
        for(long long i=0;i<s;i++)
        {
            scanf("%lld",&x);
            arr[i][0]=x;
            for(long long j=1;j<=x;j++)
            {
                scanf("%lld",&arr[i][j]);
            }
        }
        printf("%lld\n",s-n+1);
        for(long long i=0;i<s-n+1;i++)
            printf("%lld ",i);
    }
    return 0;
}