#include<bits/stdc++.h>
#define MOD 1000000007
#define MOD2 1000000006
#define TEMPMOD1 998244353
#define TEMPMOD2 998244352
#define INF 1000000000000000007
#define NEGINF -1000000000000000007
#define vll vector<ll> 
#define vvll vector<vector<ll>>
#define pll pair<ll,ll>
#define pii pair<int,int>
#define plll pair<ll,pll>
#define vpll vector<pll>
using namespace std;
typedef long long int ll;

ll dp[1001][1001];

ll modexpo(ll base, ll power)
{
    ll result=1;
    while(power!=0)
    {
        if(power&1)
        {
            result=(result*base)% MOD;
        }
        base=(base*base)%MOD;
        power=power>>1;
    }
    return result;
}

ll modinverse(ll num)
{
    ll temp= MOD-2;
    return modexpo(num,temp);
}

ll factorial[1000001];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    
    ll store;
    for(ll i=1;i<1001;i++)
    {
        for(ll j=1;j<1001;j++)
        {
            if(i==1)
            {
                if(j==1)
                {
                    dp[i][j]=1;       
                }
                else
                {
                    dp[i][j]=0;
                }
                continue;
            }
            if(j==1)
            {
                dp[i][j]=1;
                continue;
            }
            store=dp[i-1][j]+dp[i-1][j-1];
            store*=j;
            if(store>=MOD)
            {
                store%=MOD;
            }
            dp[i][j]=store;
        }
    }
    
    factorial[0]=1;
    for(ll i=1;i<1000001;i++)
    {
        factorial[i]=(factorial[i-1]*i)%MOD;
    }
    ll t,n,m,k;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>k;
        ll ans=0;
        ll idx= min(m,k);
        for(ll i=1;i<=idx;i++)
        {
            store=factorial[m];
            store=(store*modinverse(factorial[m-i]))% MOD;
            store=(store*modinverse(factorial[i]))% MOD;            
            store= (store*dp[n][i])%MOD;
            ans=(ans+store)%MOD;
        }
        cout<<ans<<endl;
    }
    return 0;
}