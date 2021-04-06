#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sci(fd) scanf("%d",&fd)
#define scll(fd) scanf("%lld",&fd)
#define pb push_back
#define mp make_pair
#define MOD 1000000007
#define PI 3.1415926535897932
#define pii pair < int,int > 
#define fi first
#define se second
#define MAX 100009
const ll infi=1000000000000000009;
int ar[MAX+5];
ll facto_barca[MAX+2];
ll reverse_barca[MAX+2];
vector <int> v[MAX+4]; 
long long power(ll x,ll y)
{
	if(y==0)
	return 1;
	ll temp=power(x,y/2);
	if(y&1)
	return (((temp*temp)%MOD)*(x%MOD))%MOD;
	return (temp*temp)%MOD;
}
void compute()
{
	facto_barca[0]=1;
	reverse_barca[0]=1;
	ll i;
	for(i=1;i<=MAX;i++)
	{
		facto_barca[i]=(i*facto_barca[i-1])%MOD;
		reverse_barca[i]=power(facto_barca[i],MOD-2);
	}
}
ll ncr(ll a,ll b)
{
	ll ans=facto_barca[a];
	ll deno1=reverse_barca[b];
	ll deno2=reverse_barca[a-b];
	ans=(ans*deno1)%MOD;
	ans=(ans*deno2)%MOD;
	//printf("%lld %lld %lld\n",a,b,ans);
	return ans;
}
int doit(int start,int en)
{
	if(start>en)
	return 1;
	int i,j;
	/*vector<int>::iterator it;
	it=lower_bound(v[en+1].begin(),v[en+1].end(),start);
	if(it==v[en+1].end())*/
	for(i=start;i<=en;i++)
	{
		if(ar[i]+i+1==en+1)
		break;
		if(ar[i]+i+1>en+1)
		return 0;
	}
	//return 0;
	//i=(*it);
	int len=en-start;
	ll a=(ncr(len,i-start)*((ll)doit(start,i-1)))%MOD;
	ll ans=(a*((ll)doit(i+1,en)))%MOD;
	int aa=ans;
	return aa;
}
int main()
{
    int t;
    compute();
    scanf("%d",&t);
    while(t--)
    {
    	int n,i,j;
    	sci(n);
    	/*for(i=0;i<=MAX+3;i++)
    	v[i].clear();*/
    	for(i=0;i<n;i++)
    	{
    		sci(ar[i]);
    	}
    	/*for(i=0;i<n;i++)
    	{
    		if(ar[i]+i+1>MAX)
    		break;
    		v[ar[i]+i+1].pb(i);
    	}*/
    	if(i!=n)
    	{
    		printf("0\n");
    		continue;
    	}
    	int ans=doit(0,n-1);
    	printf("%d\n",ans);
    }
    return 0;
} 