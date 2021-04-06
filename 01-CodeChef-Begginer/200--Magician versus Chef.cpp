#include<bits/stdc++.h>
#define ll          long long
#define start       ll n;cin>>n;
#define inputn      vector<ll>v(n);for(int i=0;i<n;i++)cin>>v[i];
#define outputn     for(int i=0;i<n;i++)cout<<v[i]<<" ";
#define en          cout<<ans<<endl;
#define fast        ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define tc          ll t1; cin>>t1; while(t1--)
using namespace std;
int main()
{fast
tc{ start
 ll x,s;cin>>x>>s;
 vector<ll>v(n+1,0);
 v[x]=1;
 while(s--)
 {
      ll x,y;cin>>x>>y;
      swap(v[x],v[y]);
 }
 ll ans;
  for(ll i=1;i<=n;i++)
  {
       if(v[i]==1)
       {
            ans=i;
            break;
       }
  }
  cout<<ans<<endl;
  }
 return 0;
}
//sort(v.begin(),v.end());
//reverse(v.begin(),v.end());

