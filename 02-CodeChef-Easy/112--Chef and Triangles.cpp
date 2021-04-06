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
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;


long long power(long long a, long long b,long long mod) {
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


int pre[2005];

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
    while(t--)
    {
        int n;
        cin>>n;
        vector<int>a[4];
        int x,y;
        for(int i=0;i<n;i++)
        {
            cin>>x>>y;
            a[x].push_back(y);
        }
        ordered_set<ld>s;
        for(auto i:a[2])
            s.insert(i);
        for(int i=1;i<4;i++)
            sort(a[i].begin(),a[i].end());
        int ssz=a[2].size();
        for(int i=0;i<ssz;i++)
            pre[i+1]=pre[i]+a[2][i];
        ld ans=0;
        // cout<<pre[1]<<" "<<pre[2]<<endl;
        for(auto i:a[1])
        {
            for(auto j:a[3])
            {
                ld kad=i+j;
                int num=s.order_of_key(kad/2);
                // cout<<i<<" "<<j<<" "<<num<<endl;
                ans+=(kad*num-2*pre[num]);
                // cout<<ans<<endl;
                ans+=(2*(pre[ssz]-pre[num])-kad*(ssz-num));
                // cout<<ans<<endl;
            }
        }
        // cout<<ans<<endl;
        int sz=a[1].size();
        for(int i=0;i<sz;i++)
        {
            for(int j=i+1;j<sz;j++)
            {
                ans+=(a[1][j]-a[1][i])*(a[2].size());
                ans+=(a[1][j]-a[1][i])*(a[3].size())*2;
            }
        }

        sz=a[2].size();
        for(int i=0;i<sz;i++)
        {
            for(int j=i+1;j<sz;j++)
            {
                ans+=(a[2][j]-a[2][i])*(a[1].size());
                ans+=(a[2][j]-a[2][i])*(a[3].size());
            }
        }
        sz=a[3].size();
        for(int i=0;i<sz;i++)
        {
            for(int j=i+1;j<sz;j++)
            {
                ans+=(a[3][j]-a[3][i])*(a[2].size());
                ans+=(a[3][j]-a[3][i])*(a[1].size())*2;
            }
        }
        cout<<fixed<<setprecision(5)<<ans/2<<'\n';

    }

}    
