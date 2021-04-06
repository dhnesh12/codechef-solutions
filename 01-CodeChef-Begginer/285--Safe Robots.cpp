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
char _s[100009] ;
int32_t main()
{
    ios_base::sync_with_stdio(0) ; cin.tie(0) ; cout.tie(0) ;
    int t ; cin>>t ;
    while(t--)
    {
       //getchar() ;
        string s ; cin>>s ;
        int sa,sb,fl=1,pa,pb ; cin>>sa>>sb ;
        s=" "+s ;
        for(int i = 1 ; i < s.size() ; i++)
        {
            if(s[i]=='A') pa=i ;
            else if(s[i]=='B') {pb=i ; break ; }
        }
        int sz=s.size()-1 ;
      //  cout<<pa<<" "<<pb<<" "<<sz<<endl ; cout<<s<<endl ;
        for(int i = 1 ; ; i++)
        {
            int a=pa+i*sa,b=pb-i*sb ;
          //  cout<<i<<" "<<a<<" "<<b<<endl ;
            if(a==b){fl=0 ; break ; }
            if(a>b || a>sz || b<=0) break ;
        }
        if(fl) cout<<"safe"<<endl ; else cout<<"unsafe"<<endl ;
    }
}
/*
2
A..B
1 1
A...B
1 1
*/
