#include <bits/stdc++.h>
#define int long long int
#define inf 1e9
using namespace std;
const int N=4005;
const int  mod=1e9;

int dp[N][N],comb[N][N];
int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    comb[0][0]=1;
    for(int i=1;i<=4000;i++)
    {
        comb[i][0]=1;
        for(int j=1;j<=i;j++)
        {
            comb[i][j]=(comb[i-1][j]+comb[i-1][j-1])%mod;
            comb[i][j]%=mod;
        }
    }
    int t;
    cin>>t;
    while(t--)
    {
       int x,y;
       cin>>x>>y;
       int i,j,k;
       for(i=1;i<=x;i++)
       {
           for(j=0;j<=y;j++)
           {
               if(j==0)
               dp[i][j]=1;
               else if(i==1)
               {
                   dp[i][j]=comb[j+y-1][y-1];
                   dp[i][j]+=dp[i][j-1];
                   dp[i][j]%=mod;
               }
               else
               {
                   dp[i][j]=(dp[i-1][j]*comb[j+y-1][y-1])%mod;
                   dp[i][j]+=dp[i][j-1];
                   dp[i][j]%=mod;
               }
           }
       }
       cout<<dp[x][y]<<"\n";
    }
}