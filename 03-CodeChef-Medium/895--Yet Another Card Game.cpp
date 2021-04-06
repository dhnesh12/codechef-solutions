#include<iostream>
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    ll t;
    cin>>t;
    while(t--){
        long double r,b,p,q;
        cin>>r>>b>>p;
        q = r+b-p;
        long double ans = p*(r)/(r+b) + q*(b)/(r+b);
        cout << fixed;
        cout << setprecision(10);
        cout << ans;
        cout<<"\n";
    }
    return 0;
}