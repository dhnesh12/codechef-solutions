#include<stdio.h>
int main()
{
int t;
scanf("%d",&t);
while(t--)
{
	unsigned long long int n,p;
	scanf("%llu%llu",&n,&p);
	unsigned long long int a[n],sum,i,j,flag=0,max=0;
	for(i=0;i<n;i++)
	scanf("%llu",&a[i]);
	for(i=0;i<n;i++)
	{
		sum=0;
	for(j=i;j<n;j++)
		{
			sum += a[j];
			sum %= p;
			if(sum >= max){	
			    if( sum == max)
			    flag++;
			    else {
			        max = sum;	
			        flag=1;}
		}}
//printf("\n");
	}
	printf("%llu %llu\n",max,flag);
}
return 0;
} 