#include<bits/stdc++.h>
#include<math.h>
#define rep(i,k,n) for(int i=k;i<n;i++)
#define ll long long
#define MOD 998244353ll
#define MOD2 1000000009ll
#define MOD3 1000000007ll
#define INF 1e16
#define MIN(a,b) (a>b?b:a)
using namespace std;
#define mp make_pair
#define pb push_back
#define  piii pair<pair<ll,ll>,ll>
#define pii pair<ll,ll>
#define fi first
#define se second
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#define time__(d) \
    for ( \
        auto blockTime = make_pair(chrono::high_resolution_clock::now(), true); \
        blockTime.second; \
        debug("%s: %lld ms\n", d, chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - blockTime.first).count()), blockTime.second = false \
    )
ll tr[505][505],dp[505][505];
ll n,m,er[505],st[505];
vector <ll> vr;
vector <pii> pr;
ll func(ll,ll);
int main()
{
    // freopen("input.txt","r",stdin);
    memset(dp,-1,sizeof(dp));
    scanf("%lld %lld",&n,&m);
    rep(i,0,m)
    {
        ll x;
        scanf("%lld",&x);
        vr.pb(x);
    }
    st[vr[0]]++;
    rep(i,0,m-1)
    {   
        ll x=vr[i],y=vr[i+1];
        pr.pb(mp(min(x,y),max(x,y)));
        st[min(x,y)]++;
        st[max(x,y)]--;
        // cout<<min(x,y)<<" "<<max(x,y)<<"\n";
    }
    // rep(i,1,n+1)
    // cout<<st[i]<<" ";
    sort(pr.begin(),pr.end());
    ll ptr=0;    
    rep(i,1,n+1)
    {
        ll tot=0;
        rep(j,i,n+1)
        {
            tot+=st[j];
            tr[i][j]=tot;
        }
        while(ptr<m-1&&pr[ptr].fi==i)
        {
            st[pr[ptr].se]+=2;
            ptr++;
        }        
    }

    // rep(i,1,n+1)
    // {
    //     rep(j,1,n+1)
    //     {
    //         cout<<tr[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    cout<<func(1,n)-1<<"\n";
    // rep(i,1,n+1)
    // {
    //     rep(j,1,n+1)
    //     cout<<dp[i][j]<<" ";
    //     cout<<"\n";
    // }
}
ll func(ll l,ll r)
{  
    // cout<<l<<" "<<r<<"\n";
    if(l>r)
        return 0;
    if(dp[l][r]!=-1)
        return dp[l][r];
    if(l==r)
    {
        return dp[l][r]=tr[l][l];
    }
    ll min_=INF;
    rep(i,l,r+1)
    {
        // if(l==2&&r==3)
        //     cout<<func(l,i-1)<<" "<<func(i+1,r)<<" "<<tr[l][r]<<"AAA\n";
        min_=min(min_,func(l,i-1)+func(i+1,r)+tr[l][r]);
    }
    return dp[l][r]=min_;
}