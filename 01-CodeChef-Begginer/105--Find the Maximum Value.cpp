#include<bits/stdc++.h>
#include<cmath>
#include<iterator>
#include<map>
using namespace std;

#define ll long long

int  main()
{
    ll t,n,k,i,m;
    cin>>t;
    while(t--)
    {
        string s;
        vector<ll> v;
        getline(cin,s);
        while(s.length()==0)
            getline(cin,s);
        stringstream g(s);
        ll n;
        while(g>>n)
            v.push_back(n);
        k=v.size()-1;
        for(i=0;i<v.size();i++)
        {
            if(v[i]==k)
                {v[i]=0;break;}
        }
        m=0;
        for(i=0;i<v.size();i++)
        {
            if(m<v[i])
                m=v[i];
        }
        cout<<m<<endl;

    }
    
    return 0;
}