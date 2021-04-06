#include<bits/stdc++.h>
#include<queue>
#define ll long long int
#define pb push_back
#define ppb pop_back
#define pii pair<ll,ll>
using namespace std;
ll bin_srch(ll l, ll r, ll ans[],ll x){
    if(l==r) return l;
     ll mid=(l+r)/2;
     if(ans[mid]>x)
     return bin_srch(mid+1,r,ans,x);
     return bin_srch(l,mid,ans,x);
}
int main()
{
    ll t;
    cin>>t;
    ll mod=1<<30LL;
    while(t--)
    {
        ll n,c,q,a,b,d;
        cin>>n>>c>>q>>a>>b>>d;
        ll arr[n];
        for(ll i=0;i<min(10000LL,n);i++)
        {
            cin>>arr[i];
        }
        for(ll j=min(10000LL,n);j<n;j++)
        {
            arr[j]=(a*arr[j-1]+b*arr[j-2]+d)%mod;
        }
        ll ans[n+1];
        for(ll i=0;i<=n;i++)
        ans[i]=0;
        deque<ll>mxdq;
        deque<ll>mndq;
        ans[1]++;
        mxdq.pb(0);
        mndq.pb(0);
        ll l,r;
        l=0;
        r=0;
        while(r!=n-1)
        {
            r++;
            while(!mxdq.empty()&&arr[r]>=arr[mxdq.back()])
            mxdq.ppb();
            while(!mndq.empty()&&arr[r]<=arr[mndq.back()])
            mndq.ppb();
            mxdq.pb(r);
            mndq.pb(r);
            if((arr[mxdq.front()]-arr[mndq.front()])<=c)
            {
                ans[r-l+1]++;
                //cout<<r-l+1<<endl;
                continue;
            }
            
           while(arr[mxdq.front()]-arr[mndq.front()]>c)
            {
                if(mxdq.front()==l)
                mxdq.pop_front();
                if(mndq.front()==l)
                mndq.pop_front();
                //cout<<arr[mxdq.front()]<<" "<<arr[mndq.front()]<<endl;
                l++;
            }
            ans[r-l+1]++;
            //cout<<r-l+1<<endl;}
            //cout<<"arr["<<r-l+1<<"]"<<"="<<arr[r-l+1]<<" ";
        }
       // cout<<mxdq.front()<<" "<<mndq.front()<<" ";
       
        for(ll i=n-1;i>1;i--)
        ans[i]=ans[i]+ans[i+1];
        ans[1]=n;
       // for(ll i=1;i<=n;i++)
       // cout<<ans[i]<<" ";
        
       
        while(q--)
        {
            ll m;
            cin>>m;
            ll an;
            ll a=1;
            ll b=n;
            an=bin_srch(1,n,ans,m);
           cout<<an<<" "<<ans[an]<<endl;
        }
    }
    return 0;
}