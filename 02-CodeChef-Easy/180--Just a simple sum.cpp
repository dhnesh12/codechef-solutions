#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

ll power(ll x,ll y,ll m)
{
    ll res=1;
    while(y>0)
    {
        if(y&1)
            res=(res*x)%m;
        x=(x*x)%m;
        y=y>>1;
    }
    return res;
}

ll gp(ll r,ll k,ll m)
{
    if(k==0)
        return 1;
    ll total=0;
    ll temp=1;
    r=r%m;

    while(k>0)
    {
        if(k&1)
            total=(r*total+temp)%m;
        temp=((r+1)*temp)%m;
        r=(r*r)%m;
        k=k>>1;
    }
    return total;
}

int main()
{
    int t;
    cin>>t;
    while(t--)
    {
        ll n,m;
        cin>>n>>m;
        ll ans=0;
        for(int i=1;i<=min(m-1,n);i++)
        {
            ll a=power(i,i,m);
            ll r=power(i,m,m);

            ll k=(n-i)/m+1;

            ans=(ans+a*gp(r,k,m)%m)%m;
        }
        cout<<ans<<"\n";
    }
    return 0;
}
