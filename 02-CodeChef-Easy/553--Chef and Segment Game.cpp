#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define F first
#define S second
#define pb push_back
#define all(v) v.begin(),v.end()
#define pi acos(-1.0)
using namespace std;
int32_t main()
{
    //ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
        int n,k ; cin>>n>>k ;
        int p=0 ;
        while(p*2+1<=k) p=p*2+1 ;
       // cout<<p<<" "<<k-p<<endl ;
        if(k-p==0)
        {
            int x=p+1 ;
            double dd=(n*1.0)/(x*1.0) ;
            dd*=(p*1.0) ;
            cout.precision(8);
            cout<<fixed<<dd<<endl;
        }
        else
        {
            int x=p+1 ;
            double dd=(n*1.0)/(x*1.0) ;
            double l=dd*((k-p)*1.0) ;
            l-=(dd/2.0) ;
           // double ab=abs(177375316.6198730500000000-l) ;
            cout.precision(8);
            cout<<fixed<<l<<endl; //cout<<fixed<<ab<<endl;
        }
    }
}
