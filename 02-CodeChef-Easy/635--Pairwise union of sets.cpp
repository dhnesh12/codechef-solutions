#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main()
{
   int t;
   cin>>t;
   while(t--)
   {
       ll n,k;
       cin>>n>>k;
       vector<vector<ll>> a(n);
       for(ll i=0;i<n;i++)
       {
           ll m;
           cin>>m;
           while(m--)
           {
               ll x;
               cin>>x;
               a[i].push_back(x);
           }
           sort(a[i].begin(),a[i].end());
       }
       ll res=0;
       vector<ll> b(k+1);
       for(ll i=0;i<n;i++)
       for(ll j=i+1;j<n;j++)
       {
           auto it=set_union(a[i].begin(),a[i].end(),a[j].begin(),a[j].end(),b.begin());
           ll val=it-b.begin();
           if(val==k)
           ++res;
       }
       cout<<res<<'\n';
   }
   return 0;
}