#include <bits/stdc++.h>
#define ll long long
#define MOD 1000000007
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll n,ans=0; cin>>n;
    vector<ll> v(n);
    for(ll i=0;i<n;i++)
        cin>>v[i];
    for(ll i=0;i<n;i++)
    {
        for(ll j=i;j<n;j++)
        {
            ll mn=LLONG_MAX;
            if(i==j)
            {
                ans+=v[i];
                continue;
            }
            else if(j-i==1)
            {
                if(v[j]==v[i])
                    ans+=0;
                else
                    ans+=(1LL<<(ll)log2(v[j]^v[i]));
                continue;
            }
            vector<ll> vc;
            vc.assign(v.begin()+i,v.begin()+j+1);
            sort(vc.begin(),vc.end());
            do
            {
                ll x=0;
                for(ll i=0;i<vc.size();i++)
                {
                    if(i==0)
                    {
                        if(vc[i]==vc[i+1])
                            x=0;
                        else
                            x=(1LL<<(ll)log2(vc[i]^vc[i+1]));
                        i++;
                    }
                    else
                    {
                        if(x==vc[i])
                            x=0;
                        else
                            x=(1LL<<(ll)(log2(x^vc[i])));
                    }
                }
                mn=min(mn,x);
            }while(next_permutation(vc.begin(),vc.end()));
            ans+=mn;
        }
    }
    cout<<ans;
    return 0;
}