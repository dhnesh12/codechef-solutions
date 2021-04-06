#include <bits/stdc++.h>
using namespace std;
#define int long long
const int nax=5e6+100,mod=1e9+7;
int pr[nax],pref[nax],dp[nax];
void init()
{
    pr[1]=0;
    for(int i=2;i<nax;i++)
    pr[i]=1;
    for(int i=2;i*i<nax;i++)
    if(pr[i])
    {
        for(int j=2*i;j<nax;j+=i)
        pr[j]=0;
    }
    pref[0]=0;
    for(int i=1;i<nax;i++)
    pref[i]=pref[i-1]+(pr[i]?1:0);
    dp[1]=1;
    for(int i=2;i<nax;i++)
    {
        dp[i]=(1+pref[i])*dp[i-1];
        dp[i]%=mod;
    }
}
int32_t main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    cout.tie(nullptr);
    init();
    int t=1;
    cin>>t;
    while(t--)
    {
        int n;
        cin>>n;
        //--n;
        cout<<dp[n]<<'\n';
    }
    return 0;
}