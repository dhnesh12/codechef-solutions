#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast cin.tie(0);ios_base::sync_with_stdio(0);cin.tie(NULL);
#define w(t) long long int t;cin>>t;while(t--)
#define f for(ll i=0;i<n;i++)

int main(){
    w(t){
        ll n;
        cin>>n;
        ll a[n];
        f{
            cin>>a[i];
        }
        ll ans=0;
        sort(a,a+n,greater<int>());
        for(ll i=0;i<n;i+=2)
        {
            ans+=a[i];
        }
        cout<<ans<<"\n";
    }
}

  
  

