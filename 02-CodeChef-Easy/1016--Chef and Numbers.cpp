#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast cin.tie(0);ios_base::sync_with_stdio(0);cin.tie(NULL);
#define w(t) long long int t;cin>>t;while(t--)
#define f for(ll i=0;i<n;i++)

ll sum(ll n)
{
    ll s=0;
    while(n>0)
    {
        s=s+n%10;
        n/=10;
    }
    return s;
}

int main(){
    ll n;
    cin>>n;
    ll x=n-97;
    int c=0;
    for(ll i=x;i<n;i++)
    {
        ll s=sum(i);
        ll k=sum(s);
        if(n==(i+k+s))
            c++;
    }
    cout<<c;
}

  
  

