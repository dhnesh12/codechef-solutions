#include<bits/stdc++.h>
#define ll long long int
using namespace std;
ll dp[64];
void solve()
{
    set<ll>s;
    for(ll i=0;i<31;i++)
    {
       for(ll j=0;j<31;j++)
       {
           if(i!=j)
           {
               ll val=(1<<i)+(1<<j);
               s.insert(val);
           }
       }

    }
    ll t;cin>>t;
    while(t--)
    {
        ll n;cin>>n;
        ll ans=INT_MAX;
        for(ll ele:s)
        {
            ans=min(ans,abs(ele-n));
        }
        cout<<ans<<"\n";
        
    }
}
int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
