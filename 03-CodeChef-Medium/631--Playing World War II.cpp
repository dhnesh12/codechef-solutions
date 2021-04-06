#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
#define pi 3.141592653589793238
#define int long long
#define ll long long
#define ld long double
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
 
 
long long powm(long long a, long long b,long long mod) {
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a %mod;
        a = a * a %mod;
        b >>= 1;
    }
    return res;
}
 
 
int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);      
}

int dp[105][20005];


signed main()
{
 
ios_base::sync_with_stdio(false); 
cin.tie(NULL);  
cout.tie(0);   
 
#ifndef ONLINE_JUDGE
    if(fopen("INPUT.txt","r"))
    {
        freopen("INPUT.txt","r",stdin);
        freopen("OUTPUT.txt","w",stdout);
    }
#endif          


    int t;
    cin>>t;
    int tt=t;
    while(t--)
    {
        int n;
        cin>>n;
        int a[n+1];
        double x;
        int lim=10000;

        for(int i=1;i<=n;i++)
        {
            cin>>x;
            a[i]=(100*x+0.5);
        }   

        for(int i=0;i<=n;i++)
        {
            for(int j=0;j<=2*lim;j++)
                dp[i][j]=-1e17;
        }  

        dp[0][lim]=0;
        int mm[n+1];
        for(int i=1;i<=n;i++)
            cin>>mm[i];
        cin>>x;
        int s=(100*x+0.5);

        for(int i=0;i<n;i++)
        {
            for(int j=0;j<=2*lim;j++)
            {
                if(j+(100-a[i+1])-lim<s*(i+1) && j+(100-a[i+1])<=2*lim)
                {
                    dp[i+1][j+(100-a[i+1])]=max(dp[i+1][j+(100-a[i+1])],dp[i][j]+mm[i+1]);
                }
                if(j-a[i+1]>=0 && (j-a[i+1]-lim)<s*(i+1))
                {
                    dp[i+1][j-a[i+1]]=max(dp[i+1][j-a[i+1]],dp[i][j]);
                }
            }
        }

        int mx=0;

        for(int i=0;i<=2*lim;i++)
        {
            if((i-lim)<s*(n))
                mx=max(mx,dp[n][i]);
        }

        cout<<"Case "<<tt-t<<": "<<mx<<'\n';

    }

}  
