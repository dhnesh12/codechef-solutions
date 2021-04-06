#include<bits/stdc++.h>
#include<cmath>
#include<iterator>
#include<map>
using namespace std;

#define ll long long

int  main()
{
    ll t,n,k,i,m,j,sum;
    cin>>t;
    while(t--)
    {
        cin>>n;
        ll a[n];
        m=0;
        vector<int> v;
        for(i=0;i<n;i++)
            cin>>a[i];
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++)
                v.push_back(a[i]*a[j]);
        for(i=0;i<v.size();i++)
        {
            sum=0;
            k=v[i];
            while(k)
            {
                sum+=k%10;
                k/=10;
            }
            if(m<sum)
                m=sum;
        }
        cout<<m<<endl;
    }
    
    return 0;
}