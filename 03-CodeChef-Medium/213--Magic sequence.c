#include <stdlib.h>
#include <stdio.h>
long long vals[20],  mod=1000000;
int Q;
long long a[4],b[4],d[4];
long long solve(long long cons[4], int upto) 
{
	long long next[4];
	long long ret;
	int i,numnew;
	if (upto==Q) 
		return 0;
	 
	numnew = Q-upto-1;
	for ( i=0; i<numnew; i++) 
	{
		next[i] = ((cons[i+1]-(d[upto]*cons[i])%mod)%mod+mod)%mod;
	}
	ret = solve(next,upto+1);
	ret = (ret + (d[upto]*cons[Q-upto-1])%mod)%mod;
	return ret;
}
int main() 
{
	int P;
	int i,j,x;
	long long cons[4];
	long long nextcoeff,ans;
	
	//Input values
	scanf("%d %d",&P,&Q);
	for (i=0; i<P; i++) 
	{
		scanf("%lld",&a[i]);
		a[i] = (a[i]+mod)%mod;
	}
	for (i=0; i<Q; i++) 
	{
		scanf("%lld",&b[i]);
		b[i] = (b[i]+mod)%mod;
	}
	for (i=0; i<Q; i++) 
	{
		scanf("%lld",&d[i]);
		d[i] = (d[i]+mod)%mod;
	}
	for (i=0; i<10; i++) 
	{
		scanf("%lld",&vals[i]);
		vals[i] = (vals[i]+mod)%mod;
	}
 
	
	for (x=0; x<10; x++) 
	{
		// find last Q constants of the equations
		for (i=0; i<Q; i++) 
		{
			cons[Q-1-i] = vals[9+x-i];
			for (j=0; j<P; j++) 
				cons[Q-1-i] = ((cons[Q-1-i]-a[j]*vals[8+x-i-j])%mod+mod)%mod;
		}
		nextcoeff = solve(cons,0);
		ans = nextcoeff;
		for ( j=0; j<P; j++) 
			ans = (ans+a[j]*vals[x+9-j])%mod;
		vals[x+10]=ans;
		printf("%lld ",ans);
	}
	printf("\n");
	return 0;
} 