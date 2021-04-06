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
      int n=0;
      cin>>n;
      int flag=0;
      vector <int> a(n);
      for(int i=0;i<n;i++)
      {
            cin>>a[i];
            if(a[i]==0)
            {
                  flag=1;
            }
      }
      if((flag==1)&&(n>1))
      {
          cout<<"NO\n";
          return;
      }
      if(n>61)
      {
            cout<<"NO\n";
            return;
      }
      vector <int> ar;
      for(int i=0;i<n;i++)
      {
            int temp=a[i];
            ar.push_back(a[i]);
            for(int j=i+1;j<n;j++)
            {
                  temp=temp|a[j];
                  ar.push_back(temp);
            }
      }
      sort(ar.begin(),ar.end());
      for(int i=1;i<ar.size();i++)
      {
            if(ar[i]==ar[i-1])
            {
                  cout<<"NO\n";
                  return;
            }
      }
      cout<<"YES\n";
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
