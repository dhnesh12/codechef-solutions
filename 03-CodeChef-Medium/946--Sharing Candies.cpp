#include <bits/stdc++.h>
#define ll long long
#define pb push_back
#define fi first
#define se second
#define N 1000005
#define mod 1000000007
#define inf 9e17
using namespace std;

ll F[N];
vector<ll> dp(N,0);

bool sorting(pair<ll,ll>&a,pair<ll,ll>&b)
{
   if(a.se==b.se)
   {
      if(a.se==1)
      return (a.fi<b.fi);
      else
      return (a.fi>b.fi);
   }
   else
   {
      return a.se<b.se;
   }
   

}
ll power(ll x,ll y,ll p)
{
   ll res=1;
 
   x=x%p;
   while(y>0)
   {
      if(y%2!=0)
      res=res*x%p;
      y=y/2;
      x=x*x%p;

   }
   return res;
}
ll cnr(ll n,ll r,ll p)
{
     if(r>n)
     return 0;
     ll res =F[n];
     res=(res*power(F[r],p-2ll,p))%p;
     res=(res*power(F[n-r],p-2ll,p))%p;
     return res;
}
ll gcd (ll a,ll b )
{
   if (a>b)
   swap(a,b);
   if(a==0)
   return b;
   else 
   return gcd (b%a,a);
}


int main()
{
     ios_base::sync_with_stdio(false); 
    cin.tie(NULL);    
    ll t;
    cin>>t;
    while(t--)
    {
       ll a,b,x,y;
       cin>>a>>b>>x>>y;
       ll diff=abs(a-b);
       ll g=gcd(x,y);
         cout<<min(diff%g,g-(diff%g))<<"\n";
    }
      
    
      
     
     

   

  
 
}