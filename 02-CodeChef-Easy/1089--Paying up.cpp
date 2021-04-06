#include<bits/stdc++.h>
using namespace std;
#define ll long long int

int main()
{
    ll t,i;
    cin>>t;
    while(t--)
    {
        ll n,m;
        cin>>n>>m;
        ll a[n];
        for(i=0;i<n;i++)
        cin>>a[i];
        
        ll total = 1<<n;
        ll flag=0;
        for(ll k=1;k<total;k++)
        {
            ll sum=0;
            for(i=0;i<n;i++)
            {
                if(k&(1<<i))
                {
                    sum = sum +a[i];
                }
            }
            if(sum==m)
            {
                flag=1;
                break;
            }
            
        }
        if(flag==1)
        cout<<"Yes\n";
        else
        cout<<"No\n";
    }
}