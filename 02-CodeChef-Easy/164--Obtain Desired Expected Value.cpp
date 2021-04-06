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
        ld e;
        cin>>e;
        pair<ld,int> x[n];
        for(int i=0;i<n;i++)
        {
            cin>>x[i].first;
            x[i].second=i;
        }
        sort(x,x+n);
        if(n==1)
        {
            if(x[0].first!=e)
            {
                cout<<-1<<'\n';
            }
            else
            {
                cout<<fixed<<setprecision(8);
                cout<<1.0000000<<'\n';
            }
                continue;
        }
        ld a=x[0].first;
        ld b=x[n-1].first;

        if(e<a||e>b)
            cout<<-1<<'\n';
        else
        {
            ld l=0,r=1;
            ld eps=1e17;
            eps=1/eps;
            // cout<<a<<" "<<b<<endl;
            while(r-l>eps)
            {
                ld mid=(l+r)/2;
                // cout<<l<<" "<<r<<" ";
                // cout<<mid*a+(1-mid)*b<<endl;
                if(mid*a+(1-mid)*b>e)
                    l=mid;
                else
                    r=mid;
            }
            // cout<<l*a+(1-l)*b<<endl;s
            cout<<fixed<<setprecision(13);
            for(int i=0;i<n;i++)
            {
                if(x[0].second==i)
                    cout<<l<<" ";
                else if(x[n-1].second==i)
                    cout<<1-l<<" ";
                else
                    cout<<0<<" ";
            }
            cout<<'\n';
        }
    }

}    
