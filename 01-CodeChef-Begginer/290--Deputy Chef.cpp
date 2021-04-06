#include<bits/stdc++.h>
#define ll long long int
using namespace std;
void solve()
{
    ll t;cin>>t;
    while (t--)
    {
        ll n;
        cin>>n;
        ll arr[n];
        ll drr[n];
        ll ans=INT_MIN;
        for(ll i=0;i<n;i++)
        {
            cin>>arr[i];
        }
        for(ll i=0;i<n;i++)
        {
            cin>>drr[i];
        }
        for(ll i=0;i<n;i++)
        {
            
            if(i==0)
            {
                if(arr[n-1]+arr[i+1]<drr[i])
                {
                    ans=max(drr[i],ans);
                }
            }
            else if(i==n-1)
            {
                if(arr[i-1]+arr[0]<drr[i])
                {
                    ans=max(drr[i],ans);
                }
               
            }
            else
             {
                    if(arr[i-1]+arr[i+1]<drr[i])
                    {
                        ans=max(ans,drr[i]);
                    }
             }
                
        }
        if(ans==INT_MIN)
        {
            cout<<-1<<'\n';
        }
        else
        {
            cout<<ans<<'\n';
        }
        
    }
    
}
int main(int argc, char const *argv[])
{
    solve();
    return 0;
}
