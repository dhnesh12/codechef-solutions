#include <iostream>
#include <map>
#include <set>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>

#define ll long long int
#define pb push_back
using namespace std;

int main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int t;
  ll n,bi,ai,i,j,x,tot;
  vector<stack<ll>> in;
  bool flg;
  cin>>t;
  while(t--)
  {
    cin>>n;
    in.clear();
    tot=0;
    flg=true;
    for(i=0;i<n;i++)
    {
      cin>>ai;
      tot+=ai;
      stack<ll> v;
      for(j=0;j<ai;j++)
      {
        cin>>x;
        v.push(x);
      }
      in.pb(v);
    }
    for(i=0;i<tot;i++)
    {
      cin>>x;
      for(j=0;j<in.size();j++)
      {
        if(!in[j].empty() && in[j].top()==x)
        {
          in[j].pop();
          break;
        }
      }
      if(j==in.size())
      {
        flg=false;
        break;
      }
    }
    if(flg==true)
      cout<<"Yes"<<endl;
    else
      cout<<"No"<<endl;
  }
  return 0;
}
