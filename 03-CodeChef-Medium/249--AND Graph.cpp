#include<cstdio>
#include<cstring>
#include<algorithm>
#define MN 5001
using namespace std;
 
const int MOD=998244353;
int T,n,dp[MN][MN],k,F[MN],MMH;
char s[MN],t[MN];
int main(){
	F[0]=0;F[1]=1;
	for (int i=2;i<=5000;i++) F[i]=F[i-1]+F[i-2],F[i]-=F[i]>=MOD?MOD:0;
	scanf("%d",&T);
	while (T--){
		scanf("%s%s",s,t);MMH=0;
		n=strlen(s);k=0;
		while (s[k]=='0') k++;
		for (int i=0;i<n;i++)
		for (int j=0;j<=n;j++) dp[j][i]=0;
		dp[0][0]=1;
		for (int i=0;i<n;i++){
			for (int j=0;j<k;j++){
				dp[j+1][i]=(1LL*dp[j][i]*F[i+2-(t[j]=='1')]+dp[j+1][i])%MOD;
				dp[j+1][i+1]=(1LL*dp[j][i]*F[i+1-(t[j]=='1')]+dp[j+1][i+1])%MOD;
			}
			for (int j=k;j<n;j++) dp[j+1][i]=(1LL*dp[j][i]*F[i+2-(t[j]=='1')-(s[j]=='1')]+dp[j+1][i])%MOD;
			(MMH+=dp[n][i])%=MOD;
		}
		printf("%d\n",MMH);
	}
}