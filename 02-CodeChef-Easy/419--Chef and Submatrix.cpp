#include<bits/stdc++.h>
#define MOD 1000000007
using namespace std;
typedef long long int ll;
double PI=4.00*(atan(1));

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        ll arr1[n][n];
        for(ll i=0;i<n;i++)
        {
            for(ll j=0;j<n;j++)
            {
                cin>>arr1[i][j];
            }    
        }
        // let us precalculate a dp[i][j] that denotes xorsum of rectangle from (1,1) to (i,j);
        ll dp[n+1][n+1];
        for(ll i=0;i<=n;i++)
        {
            dp[i][0]=0;
            dp[0][i]=0;
        }
        for(ll i=1;i<=n;i++)
        {
            for(ll j=1;j<=n;j++)
            {
                dp[i][j]=dp[i-1][j]^dp[i][j-1]^dp[i-1][j-1];
                dp[i][j]=dp[i][j]^arr1[i-1][j-1];
            }    
        }
        ll max_val=-1,temp;
        for(ll i=1;i<=n;i++)
        {
            for(ll j=i;j<=n;j++)
            {
                for(ll k=1;k<=n;k++)
                {
                    for(ll l=k;l<=n;l++)
                    {
                        temp=dp[j][l]^dp[j][k-1]^dp[i-1][l]^dp[i-1][k-1];
                        if(max_val<temp)
                        {
                            max_val=temp;
                        }
                    }
                }        
            }
        }
        cout<<max_val<<endl;
    }
    return 0;
}