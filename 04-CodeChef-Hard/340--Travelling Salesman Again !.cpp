#include <bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,n,m) for(int i=n;i<=m;i++)
#define pre(i,n,m) for(int i=n;i>=m;i--)
const int nax=1005,inf=1<<29;
int dp[nax][nax][2],cnt[nax][nax];
void solve()
{
    int n,k;
   cin>>n>>k;
   memset(cnt,0,sizeof(cnt));
   memset(dp,80,sizeof(dp));
   rep(i,1,k)
   {
       int x,y;
       cin>>x>>y;
       cnt[x][y]++;
   }
   pre(i,n-1,0)
   rep(j,0,n-1)
   cnt[i][j]+=cnt[i+1][j];
   rep(i,0,n-1)
   rep(j,1,n-1)
   cnt[i][j]+=cnt[i][j-1];
   dp[1][0][0]=0;
   rep(i,1,n-2)
   rep(j,0,i-1)
   rep(f,0,1)
   {
       if(dp[i][j][f]<1e9)
       {
           int a=i-1,b=j;
           if(f==1)
           swap(a,b);
           dp[i+1][b][0]=min(dp[i+1][b][0],dp[i][j][f]+cnt[a][i]);
           dp[i+1][a][1]=min(dp[i+1][a][1],dp[i][j][f]+cnt[i][b]);
       }
   }
   int res=inf;
   rep(j,0,n-1)
   rep(f,0,1)
   if(dp[n-1][j][f]<1e9)
   {
       int a=n-2,b=j;
       if(f==1)
       swap(a,b);
       res=min(res,dp[n-1][j][f]+cnt[a][n-1]+cnt[n-1][b]);
   }
   cout<<res<<'\n';
}
int32_t main()
{
    int t;
    cin>>t;
    while(t--)
    solve();
   return 0;
}