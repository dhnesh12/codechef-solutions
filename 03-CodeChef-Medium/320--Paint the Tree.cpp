#include <bits/stdc++.h>
using namespace std;
#define pb push_back
#define mp make_pair
#define fs first
#define sc second
#define pii pair<int,int>
#define ll long long
#define mod 1000000007
int dp[301][301][8],dp2[301][301][8];
int nc[301][301];
vector<int>ac[301],vc[301];
int ara[4];
int sz[301],sum[301];
int ncr(int n,int r)
{
    if(n<r)return 0;
    if(r==0)return 1;
    if(r==1)return n;
    if(n==r)return 1;
    if(nc[n][r]!=-1)return nc[n][r];
    int ret=ncr(n-1,r-1)+ncr(n-1,r);
    return nc[n][r]=ret%mod;
}
bool check(int mask,int pos)
{
    return (bool)(mask&(1<<pos));
}
void dfs(int v,int par)
{
     sz[v]=1;
     vector<pii>tp;
     for(int i=0;i<ac[v].size();i++)
     {
         int w=ac[v][i];
         if(w==par)continue;
         dfs(w,v);
         sz[v]+=sz[w];
         tp.pb(mp(sz[w],w));
       //  vc[v].pb(w);
     }
    // vc[v].pb(-1);
     sort(tp.begin(),tp.end());
     int s=0;
     for(int i=0;i<tp.size();i++)
     {
          int w=tp[i].sc;
          int x=tp[i].fs;
          sum[w]=s;
          s+=x;
          vc[v].pb(w);
     }
     reverse(vc[v].begin(),vc[v].end());
     vc[v].pb(-1);

}
int dp_func(int v,int rem,int mask);
int dist_func(int v,int par,int pos,int rem,int mask)
{
    //cout<<mask<<endl;
    if(v==-1)return rem==0;
    if(dp2[v][rem][mask]!=-1)return dp2[v][rem][mask];
    ll ret=0;
    for(int i=min(sz[v],rem);i>=0;i--)
    {
          int g=rem-i;
          if(g>sum[v])break;
          ret+=1LL*dp_func(v,i,mask)*dist_func(vc[par][pos+1],par,pos+1,rem-i,mask)%mod;
    }
    return dp2[v][rem][mask]=ret%mod;
}
int dp_func(int v,int rem,int mask)
{
    // cout<<mask<<endl;
     if(dp[v][rem][mask]!=-1)return dp[v][rem][mask];

     ll ret=0;
     if(rem)
     {
         ret+=dist_func(vc[v][0],v,0,rem-1,mask);
     }
   //  cout<<mask<<" "<<v<<endl;
     for(int i=0;i<3;i++)
     {
        if(check(mask,i)==0)continue;
        int space=(sz[v]-1)-rem;
        for(int j=0;j<=min(space,ara[i]-1);j++)
        {
                  ret+=1LL*dist_func(vc[v][0],v,0,rem+j,mask^(1<<i))*ncr(rem+j,j)%mod;
        }
     }

     return dp[v][rem][mask]=ret%mod;
}
int main()
{
   memset(dp,-1,sizeof dp);
   memset(dp2,-1,sizeof dp2);
   memset(nc,-1,sizeof nc);
   int i,j,k,l,m,n;
   scanf("%d%d%d%d",&n,&ara[0],&ara[1],&ara[2]);
   int mask=0;
   for(int i=0;i<3;i++)
   {
      if(ara[i])mask|=(1<<i);
   }
   for(int i=1;i<n;i++)
   {
       scanf("%d%d",&l,&k);
       ac[l].pb(k);
       ac[k].pb(l);
   }
 //  cout<<mask<<endl;
   dfs(1,-1);
   int ans=dp_func(1,0,mask);
   cout<<ans<<endl;



}
