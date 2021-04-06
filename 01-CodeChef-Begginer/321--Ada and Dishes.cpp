#include <bits/stdc++.h>
#define fob(i,n) for(i=0;i<n;i++)
#define ll long long
using namespace std;

void solve()
{
    ll n,i;
    cin>>n;
    vector<int>v;
    fob(i,n)
    {
        ll c;
        cin>>c;
        v.push_back(c);
    }
    sort(v.begin(),v.end());
    ll mini=*min_element(v.begin(),v.end());
    ll maxa=*max_element(v.begin(),v.end());
    if(n==1)cout<<v[0];
    else if(n==2)cout<<maxa;
    else if(n==3)
    {
        int check1=v[0]+v[1];
        int out=max(check1,v[2]);
        cout<<out;
    }
    else if(n==4){
        int check=v[0]+v[3];
        int check1=v[1]+v[2];
        int out=max(check,check1);
        cout<<out;
    }
}

int main()
{
    int t;cin>>t;
    while(t--)
    {
	    solve();
        cout<<'\n';
    }
    return 0;
}




