#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define max(a,b) (a>b?a:b)
#define INF 1e18
#define min(a,b) (a<b?a:b)
#define int long long int
#define float long double
void solve()
{
      string s;
      cin>>s;
      int n=s.size();
      stack <int> p;
      vector <int> ans(n,0);
      for(int i=0;i<n;i++)
      {
            if(s[i]=='(')
            {
                  p.push(i);
            }
            else
            {
                  if(!p.empty())
                  {
                        int z=p.top();
                        p.pop();
                        ans[z]=i+1;
                  }
            }
      }
      if(!p.empty())
      {
            while(!p.empty())
            {
                  int z=p.top();
                  p.pop();
                  ans[z]=-1;
            }
      }
      if(ans[n-1]==0)
            ans[n-1]=-1;
      for(int i=n-2;i>=0;i--)
      {
            if(ans[i]==0)
            {
                  ans[i]=ans[i+1];
            }
      }
      int q=0;
      cin>>q;
      while(q--)
      {
            int k=0;
            cin>>k;
            cout<<ans[k-1]<<"\n";
      }
}
signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    //t=1;
    while(t--)
    {
        solve();
    }
   return 0;
}
