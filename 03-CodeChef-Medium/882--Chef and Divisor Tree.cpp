#include <bits/stdc++.h>
using namespace std;
#define fast ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define ll long long
#define pll pair<ll,ll>
#define f first
#define s second
#define all(arr) arr.begin(),arr.end()
#define pb(v) push_back(v)
#define MOD 1000000007
void sieve(ll B,vector<ll>&primes)
{
  vector<bool>arr(floor(sqrt(B))+1,true);
  arr[0]=arr[1]=false;
  for(ll i=2;i*i<=arr.size();i++)
  {
    if(arr[i])
    {
      for(ll j=i*i;j<arr.size();j+=i)
        arr[j]=false;
    }
  }
  for(ll i=2;i<arr.size();i++)
  {
    if(arr[i])
      primes.push_back(i);
  }
}
void solve()
{
  ll A,B;
  cin>>A>>B;
  vector<ll>primes;
  sieve(B,primes);
  // for(int i=0;i<primes.size();i++)
  //   cout<<primes[i]<<" ";
  // cout<<endl;
  vector<multiset<ll,greater<ll>>>ct(B-A+1);
  vector<ll>num(B-A+1);
  for(int i=0;i<B-A+1;i++)
    num[i]=A+i;
  for(ll i=0;i<primes.size();i++)
  {
    for(ll j=ceil(A/(double(primes[i]*1.0)))*primes[i];j<=B;j+=primes[i])
    {
      ll v=j;
      ll count=0;
      while(v!=1&&((v%primes[i])==0))
      {
        count++;
        v/=primes[i];
        num[j-A]/=primes[i];
      }
      ct[j-A].insert(count);
    }
  }
  // for(int i=0;i<ct.size();i++)
  // {
  //   for(auto j=ct[i].begin();j!=ct[i].end();j++)
  //     cout<<*j<<" ";
  //   cout<<endl;
  // }
  for(int i=0;i<num.size();i++)
  {
    if(num[i]!=1)
      ct[i].insert(1);
  }
  vector<ll>res(ct.size(),0);
  for(ll i=0;i<ct.size();i++)
  {
    
    while(!ct[i].empty())
    {
      ll c=1;
      for(auto j=ct[i].begin();j!=ct[i].end();j++)
        c=c*((*j)+1);
      res[i]+=c;
      if((*ct[i].begin())==1)
        ct[i].erase(ct[i].begin());
      else 
      {
        ll g=*ct[i].begin();
        ct[i].erase(ct[i].begin());
        ct[i].insert(g-1);
      }
    }
    
  }
  // for(int i=0;i<res.size();i++)
  //   cout<<res[i]<<" ";
  // cout<<endl;
  ll ans=0;
  for(ll i=0;i<res.size();i++)
    ans+=res[i];
  cout<<ans<<endl;

}

int main()
{
   fast;
   int t=1;
   // cin>>t;
   while(t--)
   {
      solve();
   }
    // cout<<1<<endl;

   return 0;
}