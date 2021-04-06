#include <bits/stdc++.h>
using namespace std;

#define optimize() ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define MOD 1000000007;
typedef long long ll;

int main()
{
   optimize();
   int t;
   cin>>t;
   while(t--){
     ll n;
     cin>>n;
     ll res=1,base=2;
     ll p,q;
     p=(n+1)/2;
     q=(n+2)/2;
     while(p>0){
        if(p%2==1) res=(res*base)%MOD;
        base=(base*base)%MOD;
        p/=2;
     }
     ll ans=res;
     res=1; base=2;
     while(q>0){
        if(q%2==1) res=(res*base)%MOD;
        base=(base*base)%MOD;
        q/=2;
     }
     ans=(ans+res-2)%MOD;
     cout<<ans<<endl;
   }
   return 0;
}

