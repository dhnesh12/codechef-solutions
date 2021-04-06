#include<stdio.h>
#include<math.h>
#define ll long long int
#define M 1000000007
int main()
{
int t;
scanf("%d",&t);
while(t--)
{
ll n,i,ans=0,x;
scanf("%lld",&n);
x=(ll)floor(sqrt(n));
for(i=1;i<=x;i++)
{
ll val = i;
            val = ((val%M)*((i + (ll)floor(n/i))%M))%M;
            val = ((val%M)*((1 + (ll)floor(n/i) - i)%M))%M;
            ans = (ans%M + val%M)%M;
}
ans = (ans%M - ((x*(x+1)*(2*x + 1))/6)%M + M)%M;
printf("%lld\n",ans);
}
return 0;
}