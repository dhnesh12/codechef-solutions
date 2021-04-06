#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main()
{
  ll T;
  cin>>T;
  while(T--)  
  {
      ll n,q;
      cin>>n>>q;
      ll count = 0;
      vector<ll> a;
      a.push_back(0);
      while(q--)
      {
        ll f,d;
        cin>>f>>d;
        a.push_back(f);
        a.push_back(d);
      }
      for(int i=0;i<a.size()-1; i++)
      {
       count+=abs(a[i]-a[i+1]);
      }
      cout<<count<<endl;
  }
}