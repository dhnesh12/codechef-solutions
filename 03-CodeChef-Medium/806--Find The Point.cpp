#include <iostream>
using namespace std;
#define ll long long
#include<bits/stdc++.h>
#include<vector>
#include<map>
#include<string>
#define I 1000000000

void solve()
{
    double r,k;
    cin>>r>>k;
    k=k/100;
    ll x=r-1;
    ll y;
    y=floor(sqrt(r*r - x*x));
    double d=r-sqrt(x*x + y*y);
    if(d<=k){
        cout<<x<<" "<<y<<"\n";
    }else{
        cout<<"-1"<<"\n";
    }
}

int main()
{
    ll t;
    cin>>t;
    
    while(t--){
        solve();
    }
    return 0;
}
