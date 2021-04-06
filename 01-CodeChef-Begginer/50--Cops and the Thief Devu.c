

#include<stdio.h>
int main()
{
    int total;
    scanf("%d",&total);
    if(total>=1&&total<=10000)
    {
        while(total--)
        {
            int x,y,m,n,i,j,z,arr1[15]={0},count=0,arr2[150]={0},minimum,maximum;
            scanf("%d %d %d",&m,&x,&y);
            if(m>=1&&m<=10&&x>=1&&x<=10&&y>=1&&y<=10)
            {
                z=x*y;
                for(i=1;i<=m;i++)
                 {
                  scanf("%d",&arr1[i]);
                  if(z+1>=arr1[i])
                    minimum=1;
                  else
                    minimum=arr1[i]-z;
                   maximum=arr1[i]+z;
                  for(j=minimum;j<=maximum&&j<=100;j++)
                   arr2[j]=1;
                 }
                 for(i=1;i<=100;i++)
                 {
                     if(arr2[i]==0)
                     {
                         count++;
                     }
                 }
                 printf("%d\n",count);

            }
        }
    }
    return 0;
}
