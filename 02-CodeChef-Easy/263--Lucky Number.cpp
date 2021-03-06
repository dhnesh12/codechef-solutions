#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long LL;
typedef vector<int> VI;

const int N = 1000;
const int MOD = 1000000007;
int dp[N+1][N+1];

int DP(int n,int k)
{
	if(n<0 || k<0 || k>n) return 0;
	return dp[n][k];
}

int lucky(int d)
{
	return d==4 || d==7;
}

int calc(VI& a,int k)
{
	int n=a.size();
	int ans=0;
	for(int i=0;i<n;i++)
	{
		if(n-i<k) break;
		for(int d=0;d<a[i];d++)
			ans=(ans+DP(n-i-1,k-lucky(d)))%MOD;
		if(lucky(a[i])) k--;
	}
	return ans;
}

int calc(VI &a)
{
	int Lucky[14]={4,7,44,47,74,77,444,447,474,477,744,747,774,777};
	int ans=0;
	for(int i=0;i<14;i++)
		ans=(ans+calc(a,Lucky[i]))%MOD;
	return ans;
}

int main()
{
	int n,k,i,j;
	dp[0][0]=1;
	for(n=1;n<=N;n++)
	{
		dp[n][0]=8LL*dp[n-1][0]%MOD;
		for(k=1;k<=n;k++)
			dp[n][k]=(2LL*dp[n-1][k-1]+8LL*dp[n-1][k])%MOD;
	}
	int TST;
	scanf("%d",&TST);
	for(int tst=0;tst<TST;tst++)
	{
		char buf[N+2];
		scanf("%s",buf);
		n=strlen(buf);
		VI cur(n);
		for(i=0;i<n;i++) cur[i]=buf[i]-'0';
		int ans=calc(cur);

		scanf("%s",buf);
		n=strlen(buf);
		for(i=n-1;i>=0 && buf[i]=='9';i--);
		if(i>=0)
		{
			for(j=n-1;j>i;j--) buf[j]='0';
			buf[i]++;
		}
		cur=VI(n);
		for(i=0;i<n;i++) cur[i]=buf[i]-'0';
		ans=(calc(cur)+MOD-ans)%MOD;
		printf("%d\n",ans);
	}
	return 0;
}
