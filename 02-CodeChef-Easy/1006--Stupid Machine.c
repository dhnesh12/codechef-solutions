#include <stdio.h>

int main(void) {
   int t;
   long long int n,i,total,min,c;
   scanf("%d",&t);
   while(t--)
   {
       min=2000000000;
       total=0;
     scanf("%lld",&n);
     long long int arr[n];
     for(i=0;i<n;i++)
     {
     scanf("%lld",&arr[i]);
     if(arr[i]<min)
     min=arr[i];
     total=total+min;
     }
     printf("%lld\n",total);
   }
	return 0;
}

