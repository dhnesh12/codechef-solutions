#include <stdio.h>
#include <stdlib.h>
#define mod 10000000

int main()
{
	int t;
	int p[10001];
	scanf("%d",&t);
	while(t--)
	{
		int noi;
		scanf("%d",&noi);
		int sum=0,ing[noi],a[noi];
		for(int i=0;i<noi;i++)
		{
			scanf("%d",&ing[i]);
			a[i]=0;
			sum=sum+ing[i];
		}
		for(int i=0;i<=sum;i++)
		{
			p[i]=0;
		}
		p[0]=1;
		for(int i=0;i<noi;i++)
		{
			for(int j=sum;j>=0;j--)
			{
				if(p[j]>0)
				{
					if(j+ing[i]<=sum)
				    {
				    	p[j + ing[i]] = ((p[j+ing[i]]) + (p[j]))%mod;
					}
				    
				}
			}
		}
		long long fsum=0;
		for(int i=0;i<=sum;i++)
		{
			long long tempsum = ((long long)((long long)abs(sum-2*i))*p[i])%mod;
			fsum=((long long)fsum+tempsum)%mod;
		
			
		}
	    
		printf("%lld\n",fsum);
	}
}