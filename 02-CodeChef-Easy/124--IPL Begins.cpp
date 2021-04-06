#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int p=998244353;
int foot,cric,room;
int dp[103][103][103];
int ncr[103][103];
int fact[105];
int inv[105];
int power(int a,int b)
{
    a%=p;
    int res=1;
    while(b)
    {
        if(b&1)
        {
            res=(res*a)%p;
        }
        a=(a*a)%p;
        b=b/2;
    }
    return res;
}
int nCr(int n,int r)
{
    int &ans=ncr[n][r];
    if(ans!=-1) return ans;
    if(n==r) return 1;
    if(r==1) return n;
    return ans=(nCr(n-1,r)%p+nCr(n-1,r-1)%p)%p;
}
int solve(int f,int c,int r)
{
    int &ans=dp[f][c][r];
    if(ans!=-1) return ans;
    if(f+c==0) return r==0;
    if(r==0) return f+c==0;
    int res=0;
    for(int i=1; i<=f; i++)
    {
        res+=(nCr(f,i)%p*solve(f-i,c,r-1)%p)%p;
        res%=p;
    }
    for(int i=2; i<=c; i++)
    {
          res+=(nCr(c,i)%p*solve(f,c-i,r-1)%p)%p;
        res%=p;
    }
    return  ans=res;
}
int32_t main()
{
     ios_base::sync_with_stdio(false);
     cin.tie(NULL);
     memset(ncr,-1,sizeof ncr);
     fact[0]=1;
     for(int i=1; i<=100; i++)
        fact[i]=(fact[i-1]*i)%p;
    inv[100]=power(fact[100],p-2)%p;
    for(int i=99; i>=1; i--)
        inv[i]=(inv[i+1]*(i+1))%p;
     memset(dp,-1,sizeof dp);
     int t;
     cin>>t;
     while(t--)
     {

         cin>>foot>>cric>>room;
         int ans=solve(foot,cric,room);
        ans=(ans*inv[room])%p;
        cout<<ans<<endl;
     }
}
