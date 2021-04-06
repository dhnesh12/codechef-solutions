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
int32_t main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
        int n,k,x=0,fl=1 ; cin>>n>>k ; string as="",s="" ;
        if(n==k){cout<<"-1"<<endl ; continue ; }
        if(k+2==n && n>8 && (n/2)%2)
        {
            int p=n/2 ; p-- ; n-=p ;
            p/=2 ; int q=n/2 ;
            //cout<<p<<" "<<q<<endl ;
            s="" ;
            while(p--) {s="("+s ; s+=")" ; } as+=s ;
            s="" ;
            while(q--) {s="("+s ; s+=")" ; } as+=s ;
            cout<<as<<endl ;
        }
        else
        {
            int fl=0 ;
            for(int i = 1 ; i <= n ; i++)
            {
                int j=i*2 ;
                if(j>=k){break ; }
                if(j<k && j*2>k && n-(j*2)>=0)
                {
                   // cout<<i<<" "<<j<<endl ;
                    fl=1 ;
                    int p=j/2,q=j/2 ;
                    s="" ;
                    while(p--) {s="("+s ; s+=")" ; } as+=s ;
                    s="" ;
                    while(q--) {s="("+s ; s+=")" ; } as+=s ;
                    int d=n-(j*2) ; d/=2 ;
                    while(d--){as="("+as ; as+=")" ; }
                    cout<<as<<endl ; //cout<<as.size()<<endl ;
                    break ;
                }
            }
            if(!fl) cout<<"-1"<<endl ;
        }
    }
}
