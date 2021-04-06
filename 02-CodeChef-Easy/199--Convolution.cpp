#include<bits/stdc++.h>
#define ll long long int
long long const M=998244353;
using namespace std;
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
       ll n,m;
       cin>>n>>m;
       ll asum=0;
       for(ll i=0;i<n;i++)
       {
          ll x;
          cin>>x;
          asum+=x;
       }
       ll bsum=0;
       for(ll i=0;i<m;i++)
       {
           ll x;
           cin>>x;
           bsum+=x;
       }
       asum%=M;
       bsum%=M;
       ll q;
       cin>>q;
       while(q--)
       {
           ll q1;
           cin>>q1;
           if(q1==3)
           {
               cout<<(((asum)*(bsum))%M+M)%M<<"\n";
           }
           else if(q1==2)
           {
               ll l,r,x;
               cin>>l>>r>>x;
               bsum=((bsum)+(r-l+1)*x)%M;
           }
           else if(q1==1)
           {
               ll l,r,x;
               cin>>l>>r>>x;
               asum=((asum)+(r-l+1)*x)%M;
           }
       }
    }
     return 0;
}