#include<stdio.h>
long long int bin(long long int x)
{
	long long int r,ca=0;
	while(x!=0)
		{
			r=x%2;
			if(r==1)
			ca++;
			x=x/2;
		}
		return ca;
}
int main()
{
	long long int ans,ca,cb,x,y,t,i,r,a,b;
	scanf("%lld",&t);
	while(t--)
	{
		ca=cb=0;
		scanf("%lld%lld",&a,&b);
		x=a;
		y=b-1;
		//printf("%lld %lld\n",cb,ca);
		ca=bin(x);
		cb=bin(y);
		if(a!=b)
		{
			if(a==0 && b==1)
			{
				ans=1;
				//printf("FBH");
			}
			else if(a>0 && (b==0 ||  b==1))
			ans=-1;
			else
			{
				//printf("%lld %lld\n",ca,cb);
				if(ca>cb)
				ans=2;
				else if(ca<cb)
				ans=cb-ca+1;
				else
				{
					ans=1;
					//printf("bdc");
				}
			}
		}
		else
		ans=0;
		printf("%lld\n",ans);
	}
	return 0;
}