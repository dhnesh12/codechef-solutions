#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define fast cin.tie(0);ios_base::sync_with_stdio(0);cin.tie(NULL);
#define w(t) long long int t;cin>>t;while(t--)
#define f for(ll i=0;i<n;i++)

int main(){
    ll a,b,c,d;
    cin>>a>>b>>c>>d;
    if(a*b==c*d)
        cout<<"Possible";
    else if(a*c==b*d)
            cout<<"Possible";
    else if(a*d==c*b)
            cout<<"Possible";
    else 
        cout<<"Impossible";
}

  
  

