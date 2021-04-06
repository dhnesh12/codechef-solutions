#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define mod 1000000007
int dp[(1<<17)][18],dp2[(1<<17)][18];
int ara[18],k,n,L;
int cnt_bit(int mask)
{
   return __builtin_popcount(mask);
}
bool check(int mask,int pos)
{
   return (bool)(mask&(1<<pos));
}
int dp_func2(int mask,int j)
{
   int cnt=0;
   if(dp2[mask][j]!=-1)return dp2[mask][j];
   int tp[17],jar[17];;
   for(int i=0;i<n;i++)
   {
       if(check(mask,i))cnt++;
       tp[i]=cnt;
   }
   for(int i=0;i<n;i++)
   {
      if(ara[i]==j)
      {
         jar[i]=1;
         if(i)jar[i]+=tp[i-1];
      }
      else{
         jar[i]=tp[i];
         if(i)jar[i]=max(jar[i-1],jar[i]);
      }
   }
   int dmask=0;
   cnt=0;
   for(int i=0;i<n;i++)
   {
     if(jar[i]>cnt)
     {
        assert(jar[i]-1==cnt);
        dmask|=(1<<i);
        cnt=jar[i];
     }
   }
   return dp2[mask][j]=dmask;
}
int dp_func(int mask,int pos)
{
   if(pos==n)
   {
       return cnt_bit(mask)==L;
   }
   if(dp[mask][pos]!=-1)return dp[mask][pos];
   ll ret=0;
   for(int i=1;i<=k;i++)
   {
       int mask2=dp_func2(mask,i);
       ret+=dp_func(mask2,pos+1);
   }
   ret%=mod;
   return dp[mask][pos]=ret;

}

int main()
{
     int ts;
     cin>>ts;
     while(ts--){
    scanf("%d%d%d",&n,&k,&L);
      for(int i=0;i<n;i++)scanf("%d",&ara[i]);
      memset(dp,-1,sizeof dp);
      memset(dp2,-1,sizeof dp2);
      int ans=dp_func(0,0);
      cout<<ans<<endl;

    }
}
//kldfjaslfjadsl
