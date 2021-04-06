#include <stdio.h>
#include <stdlib.h>
int main()
{
    long long int m,n;
    scanf("%lld %lld",&m,&n);
    long long int i,a[m];
    for(i=0;i<m;i++)
    {
        scanf("%lld",&a[i]);
    }
    long long int j,temp,max=0,x=0;
    for(i=0;i<m;i++)
    {
        for(j=0;j<m-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
            if(j==m-i-2)
            {
                if(a[j+1]<=n&&n!=0)
                {
                    max=max+((a[j+1]*(a[j+1]+1))/2)+1;
                    n=n-a[j+1];
                }
                else if(a[j+1]>n&&n!=0)
                {
                    max=max+((n*(n+1))/2)+1;
                    n=0;
                }
                
                if(j==0&&a[j]<=n&&n!=0)
                {
                    max=max+((a[j]*(a[j]+1))/2)+1;
                    n=n-a[j];
                }
                else if(j==0&&a[j]>n&&n!=0)
                {
                    max=max+((n*(n+1))/2)+1;
                    n=0;
                }
                if(n==0)
                {
            
                    x=j+1;
                    break;
                }
            }
        }
        if(n==0)
            break;
    }
    printf("%lld\n",max+x);
    return 0;
}