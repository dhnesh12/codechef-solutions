#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast cin.tie(0);ios_base::sync_with_stdio(0);cin.tie(NULL);
#define w(t) long long int t;cin>>t;while(t--)
#define f for(ll i=0;i<n;i++)

int main(){
    ll n;
    cin>>n;
    ll a[n],sum[n];
    f{
        cin>>a[i];
    }
    sort(a,a+n);
    sum[0]=a[0];
    for(ll i=1;i<n;i++)
        sum[i]=a[i]+sum[i-1];
    ll q;
    cin>>q;
    while(q--)
    {
        ll k;
        cin>>k;
        ll c = ceil(1.0*n/(k+1));
        cout<<sum[c-1]<<"\n";
    }
    
}

  
  

