#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
// #define pi 3.141592653589793238
#define int long long
#define ll long long
#define ld long double
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;


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


vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
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
        string a,b,c;
        cin>>a>>b>>c;
        string str=c+"#"+a;
        vector<int>kad=prefix_function(str);
        vector<int>lol;
        int len=str.length();
        while(kad[len-1]>0)
        {
            lol.push_back(kad[len-1]);
            len=kad[len-1];
        }
        lol.push_back(0);
        reverse(c.begin(),c.end());
        reverse(b.begin(),b.end());
        str=c+"#"+b;
        kad=prefix_function(str);
        int tot=c.length();
        vector<int>lol2;
        len=str.length();
        while(kad[len-1]>0)
        {
            lol2.push_back(kad[len-1]);
            len=kad[len-1];
        }
        lol2.push_back(0);
        sort(lol.begin(),lol.end());
        sort(lol2.begin(),lol2.end());
        int mx=0;
        int sz1=lol.size();
        int sz2=lol2.size();
        int x=0;
        int y=sz2-1;
        while(x<sz1 && y>=0)
        {
            while(lol[x]+lol2[y]>tot)
            {
                y--;
            }
            mx=max(mx,lol[x]+lol2[y]);
            x++;
        }
        int len1=a.length();
        int len2=b.length();
        int len3=c.length();
        cout<<(len1+len2+len3-mx)<<'\n';
    }

}    
    