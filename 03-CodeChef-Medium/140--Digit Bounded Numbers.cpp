#include <bits/stdc++.h>
using namespace std;
#define M 1000000007
inline int read(){
	char ch=getchar(); int x=0;
	for (;ch>'9'||ch<'0';ch=getchar());
	for (;ch>='0'&&ch<='9';ch=getchar()) x=x*10+ch-'0';
	return x;
}
int dp[9][8][8][10][128],L[8],R[8],a[9][9],ALL,n,A,B;
int getdp(int i,int j,int jw,int S,int P){//9*7*7*10*128
	if (dp[i][j][jw][S][P]!=-1) return dp[i][j][jw][S][P];
	if (i==8 && j==n){
		if ((jw>=A && jw<=B || jw==0)&& S>=A && S<=B && P==0){
			dp[i][j][jw][S][P]=1;
		}else 
			if (jw==0 && S==0 && P==0) dp[i][j][jw][S][P]=1; else
				dp[i][j][jw][S][P]=0;
		return dp[i][j][jw][S][P];
	}
	if (j==n){
		if (S>=A && S<=B){
			dp[i][j][jw][S][P]=getdp(i+1,0,0,jw,P);
			return dp[i][j][jw][S][P];
		}else {
			if (S==0 && jw==0 && i!=0) {
				bool flag=1;
				for (int k=0;k<n && flag;k++){
					if ((P>>k)&1){
						bool tag=0;
						for (int l=i+1;l<9 && !tag;l++) if (a[k][l]>0) tag=1;
						if (!tag) flag=0;
					}
				}
				if (flag) return (dp[i][j][jw][S][P]=1);
			}
			return (dp[i][j][jw][S][P]=0);
		}
	}
	bool tag=0;
	for (int k=i;k<9;k++) if (a[j][k]>0) tag=1;
	if (!tag && ((P>>j)&1)){
		dp[i][j][jw][S][P]=0;
		return 0;
	}
	int &res=dp[i][j][jw][S][P]; res=0;
	for (int k=0;k<=9;k++){
		int NP=P;
		if (k==a[j][i]) NP=P;
		else if (k>a[j][i]) NP=P|(1<<j);
		else NP=P&(ALL^(1<<j));
		(res+=getdp(i,j+1,(S+k)/10+jw,(S+k)%10,NP))%=M;
	}
	return res;	
}
int getans(int P){
	memset(dp,-1,sizeof(dp));
	for (int i=0;i<n;i++){
		int t;
		if ((P>>i)&1) t=L[i]-1; else t=R[i];
		if (t<0) return 0;
		for (int len=0;len<9;t/=10){
			a[i][len++]=t%10;
		}
	}
	return getdp(0,0,0,0,0);
}
void solve(){
	n=read(),A=read(),B=read(); ALL=(1<<n)-1;
	for (int i=0;i<n;i++){
		L[i]=read(); R[i]=read();
	}
	int ans=0;
	for (int i=0;i<(1<<n);i++){
		int t=__builtin_popcount(i);
		int p=getans(i);
		if (t&1) (ans+=M-p)%=M;
		else (ans+=p)%=M;
	}
	printf("%d\n",ans);	
}
int main(){
	int T=read();
	while (T--) solve();
	return 0;
}