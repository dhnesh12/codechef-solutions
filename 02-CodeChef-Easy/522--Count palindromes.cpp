#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> PII;
const ll mx = 3e5+10,mod = 1e9+7;

ll dp[2000];
ll ispal[1005][1005];
string s;
bool isp(ll b, ll e)
{
    if(b==e || b+1==e)
        return 1;
    if(ispal[b][e]!=-1)
        return ispal[b][e];
    if(s[b]!=s[e-1])
        return ispal[b][e]=0;
    return ispal[b][e] = isp(b+1,e-1);
}
ll solve(ll n)
{
    if(n==0) return 1;
    if(dp[n]!=-1) return dp[n];
    ll ret =0;
    for(int i=0;i<n;i++)
    {
        if(isp(i,n)) ret = (ret+solve(i))%mod;
    }
    return dp[n]=ret%mod;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);

    cin>>s;
    memset(dp,-1,sizeof dp);
    memset(ispal,-1,sizeof ispal);
    cout<<solve(s.size())<<endl;
}
