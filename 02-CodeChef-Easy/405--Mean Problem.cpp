#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define F first
#define S second
#define pi acos(-1.0)
#define pb push_back
#define sf(x) scanf("%lld",&x)
#define pf(x) printf("%lld",&x)
using namespace std;
const int mod=1e9+7;
map<int,int>mp ;
int ar[1000099] ;
int32_t main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
        int n,sm=0 ; cin>>n ; mp.clear() ;
        for(int i = 1 ; i <= n ; i++) {cin>>ar[i] ; sm+=ar[i] ; mp[ar[i]]++ ;}
        int lo=1,hi=n ;
        for(int i = n+1 ; i <= 1000000 ; i++)
        {
            ar[i]=sm/n ; mp[ar[i]]++ ; mp[ar[lo]]-- ;
            sm-=ar[lo] ; sm+=ar[i] ; lo++ ; hi++ ;
            if(mp[ar[i]]==n){hi=i ; break ; }
        }
       // for(int i = 1 ; i <= hi ; i++) cout<<ar[i]<<" " ; cout<<endl ;
        int q ; cin>>q ;
        while(q--)
        {
            int x ; cin>>x ;
            if(x>=hi) cout<<ar[hi]<<endl ; else cout<<ar[x]<<endl ;
        }
    }
}
