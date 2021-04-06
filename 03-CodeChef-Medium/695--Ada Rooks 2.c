#include<stdio.h>
int main()
{
int test;
scanf("%d",&test);
int n;
while(test--)
{
scanf("%d",&n);
int count=0;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j||i-8==j||i+10==j||i-13==j||i+24==j||i-17==j||i+46==j||i-19==j||i+62==j||i-20==j||i+77==j)
            {printf("O");count++;}
            else
        printf(".");
        }
        printf("\n");
    }
  // printf("%d",count);

}
}