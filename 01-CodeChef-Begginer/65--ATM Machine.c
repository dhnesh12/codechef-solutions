#include<stdio.h>
int main(){
	int testcases;
	scanf("%d",&testcases);
	while(testcases--)
	{
	int arr1[110];
	int arr2[110];
	int number,k,i;
	scanf("%d%d",&number,&k);
	for(i=0;i<number;i++)
	{
		scanf("%d",&arr1[i]);
	}
	for(i=0;i<number;i++)
	{
	if(arr1[i]<=k)
	{
		k=k-arr1[i];
		arr2[i]=1;
	}
	else
	arr2[i]=0;
   }
   for(i=0;i<number;i++)
   printf("%d",arr2[i]);
   printf("\n");
	}
	return 0;
}