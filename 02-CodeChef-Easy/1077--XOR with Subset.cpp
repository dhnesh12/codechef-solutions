#include <bits/stdc++.h>

typedef long long int ll;
#define pll pair <ll, ll>
#define pii pair <int, int>
#define f first
#define s second
#define pb push_back
#define vll vector <ll>
#define mll map <ll ,ll>
#define prtq priority_queue <long long>
#define all(c) c.begin(), c.end()
#define rep(a,b) for(i=a;i<b;i++)
#define IOS ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define inf 1e12
using namespace std;
#define Mod 1000000007
#define endl "\n"
////////////////////////////////////////////////////////////////////

void fio() // file input output
{
#ifndef ONLINE_JUDGE
  freopen("input1.txt", "r", stdin);
  freopen("output1.txt", "w", stdout);
#else
#endif
}

void tim()
{
#ifndef ONLINE_JUDGE
  cerr << "Time elapsed: " << clock() / 1000 << " ms" << endl;
#endif
}
int dp[1001][5001];
vll a(1001);
int N, K;
int solve(int i,int p)
{
    if(i==N)
    { 
        return p;
    }
    if(dp[i][p]!=-1)
    {
        return dp[i][p];
    }
    else
    {
      return dp[i][p]=max(solve(i+1,a[i]^p),solve(i+1,p));
    }
}

ll valset(int i,int k)
{
    memset(dp,-1,sizeof(dp));
    return solve(i,k);
}

int main()
{
  fio();
  IOS;
  int t = 1;
  cin >> t;
  // int cnt = 0;
  while (t--)
  {
      ll n,k,i;
    cin>>n>>k;N=n;K=k;int cnt=0;
    for(i=0;i<n;i++)
    {
        cin>>a[i];
        if(a[i]==k)cnt++;
    }
    ll ans=valset(0,k);
    ans=max(ans,k);
    cout<<ans<<endl;

  }
  tim();
  return 0;
}

