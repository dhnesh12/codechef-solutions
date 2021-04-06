#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define SPEED ios::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define loop(i,j,n) for(ll i=j;i<n;i++)
int main()
{
    SPEED;
    ll t;
    cin>>t; 
    while(t--)
    {
        string s;
        int n;
        cin>>n;
        cin>>s;
        int dp1[n],dp2[n];
        if(s[0]=='0')
        {
            dp1[0]=1;
        }else{
            dp1[0]=0;
        }
        if(s[n-1]=='1')
        {
            dp2[n-1]=1;
        }else{
            dp2[n-1]=0;
        }
        int j=n-1;
        for(int i=1;i<n;i++)
        {
            if(s[i]=='0')
            {
                dp1[i]=dp1[i-1]+1;
            }else{
                dp1[i]=dp1[i-1];
            }
            if(s[j-i]=='1'){
                dp2[j-i]=dp2[j-i+1]+1;
            }else{
                dp2[j-i]=dp2[j-i+1];
            }
        }
        int ans=0;
        for(int i=0;i<n;i++)
        {
            if(dp1[i]+dp2[i]>=ans)
            {
                ans=dp1[i]+dp2[i];
            }
        }
        // for(auto a: dp1)
        // {
        //     cout<<a<<" ";
        // }
        // cout<<"\n";
        // for(auto a: dp2)
        // {
        //     cout<<a<<" ";
        // }
        // cout<<"\n";
        cout<<n-ans<<"\n";
    }
}