#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define MX 2022
#define INF 2123456789

int R, C, A[MX][MX];
int dp[2][MX];
int leftSum[MX], rightSum[MX];
int leftDown[MX], rightDown[MX];

int solve()
{
	memset(dp,0,sizeof(dp));

	int c = 0, p = 1;

	for(int i=R-1;i>=0;i--)
	{
		c^=1; p^=1;
		
		for(int j = 0, sum = 0; j < C; j++)
		{
			leftSum[j] = sum;
			sum = max(0,sum+A[i][j]);
		}
		
		for(int j = C-1, sum = 0; j >= 0; j--)
		{
			rightSum[j] = sum;
			sum = max(0,sum+A[i][j]);
		}
		
		for(int j = 0; j < C; j++)
			leftDown[j] = A[i][j] + max( leftSum[j] + dp[p][j], j-1>=0 ? leftDown[j-1] : -INF );
		
		for(int j = C-1; j >= 0; j--)
			rightDown[j] = A[i][j] + max( rightSum[j] + dp[p][j], j+1<C ? rightDown[j+1] : -INF );
		
		for(int j = 0; j < C; j++) 
			dp[c][j] =  max( leftDown[j] + rightSum[j] , rightDown[j] + leftSum[j]  );	
	}

	int ans = -INF;
	for(int j=0;j<C;j++) ans = max(dp[c][j],ans);

	return ans;
}

int main()
{
	int kases, X, P, Q, M, I, cur;

	for(scanf("%d",&kases);kases--;)
	{
		scanf("%d %d %d",&R,&C,&I);
		if(I==2)
		{
			scanf("%d %d %d %d",&X,&P,&Q,&M);
			cur = X;
		}
		for(int i=0;i<R;i++)
			for(int j=0;j<C;j++)
				if(I==1) scanf("%d",&A[i][j]);
				else
				{
					cur = ( cur * P + Q ) % M;
					A[i][j] = X - cur;
				}
				
		printf("%d\n",solve());
	}
	
	return 0;
}