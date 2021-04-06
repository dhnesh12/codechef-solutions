#pragma GCC optimize ("O3")
#pragma GCC target ("sse4")
#include <bits/stdc++.h>
#define ll  long long
#define ull unsigned long long  
using namespace std;
#define  inf 1e15+18
#define fastio ios_base::sync_with_stdio(false); cin.tie(NULL)
#define mod 1000000007
#define  f1(i,n) for(i=1;i<=n;i++)
#define f0(i,n)  for(i=0;i<n;i++)
#define w(x)   while(x--)
const int maxn=200004;
#define vpll  vector<pair<ll,ll>>
#define  pq priority_queue
#define  ff first
#define  ss second 
#define pb  push_back
#define pob pop_back
#define lb lower_bound
#define ld long double
#define ub upper_bound
#define LB 60
#define setp(x) cout<<fixed<<setprecision(x)
#define PQ_MIN  priority_queue <ll, vector<ll>, greater<ll> >
#define setbit(x)   __builtin_popcount(x)
#define all(x) (x).begin(),(x).end()
#define pie 3.14159265358
#define enter(a)   for(ll i=0;i<a.size();i++) cin>>a[i];
#define show(a)     for(ll e: a) cout<<e<<" "; cout<<"\n";
int main()
{

  int z;
  cin >>z;
  w(z){
  int i,j,k,l,m,n;
  
  string s,r,t;
  cin >>s>>r;
  t=r+'#'+s;
  n=t.size();
  int lps[n+4]={};
  l=0;
  m=0;
  int ans=0;
  for(i=1;i<t.size();i++)
  {
    j=lps[i-1];
    while(j>0&&t[j]!=t[i])
    {
      j=lps[j-1];
    }
    if(t[i]==t[j])
      j++;
    lps[i]=j;
  
  }
  int a[n+2]={};
  for(i=r.size()+1;i<t.size();i++)
  {
    if(lps[i]==r.size())
      a[i-r.size()]=1;
  }
  int dp[n+2]={};
   dp[0]=1;
  for(i=1;i<=s.size();i++)
  {
        if(a[i])
        {
            dp[i]=dp[i-r.size()];
        }
        dp[i]+=dp[i-1];
        dp[i]=dp[i]%mod;
  }
  cout<<(dp[s.size()]-1+mod)%mod<<"\n";

  }

}



