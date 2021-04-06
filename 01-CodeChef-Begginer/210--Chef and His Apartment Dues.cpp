/* 
                        Author: Abhayanand Kumar (IIIT Gwalior)
      "One day all my imaginations found a syntax to express,coding since then!"
*/
#include<bits/stdc++.h>
using namespace std;

    #define ll           long long
    
    //functions
    ll gcd(ll a,ll b)
    {
        return b%a==0?a:gcd(b%a,a);
    }
int main ()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t,n,i;
    cin>>t;
    while(t--)
    {
        cin>>n;
        int a[n];
        for(i=0;i<n;i++) cin>>a[i];
        int f=0,fc=-1;
        for(i=0;i<n;i++)
        {
            if(f==0 && a[i]==0) {fc=i; f++;}
            else if(a[i]==0) f++;
        }
        if(f==0) cout<<0<<endl;
        else
        {
            ll r=f*1000+(n-fc)*100;
            cout<<r<<endl;
        }
    }
}