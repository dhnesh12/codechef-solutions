#include<bits/stdc++.h>
#define ll long long
using namespace std;
ll n,k;
string s;
bool func(ll reql);
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t;
    cin>>t;
    while(t--)
    {
        cin>>n>>k>>s;
        if(s[n-1]=='0')
            s+='1';
        else
            s+='0';
        ll c1=0,c2=0;
        for(ll i=0;i<n;i++){
            if(i&1)
                (s[i]=='1')?c1++:c2++;
            else
                (s[i]=='0')?c1++:c2++;
        }
        if(min(c1,c2)<=k){
            cout<<1<<"\n";
            continue;
        }
        ll s=2,e=n,ans=n;
        while(s<=e)
        {
            ll mid=(s+e)/2;
            if(func(mid))
            {
                ans=mid;
                e=mid-1;
            }
            else
                s=mid+1;
        }
        cout<<ans<<"\n";
    }
}
bool func(ll reql)
{
    ll i=0,j=0,op=0;
    while(i<n)
    {
        while(j<=n && s[j]==s[i])
            j++;
        if(j-i<=reql){
            i=j;
            continue;
        }
        i+=reql;
        while(i<j)
        {
            op++;
            i+=reql+1;
        }
        i=j;
    }
    return (op<=k);
}
