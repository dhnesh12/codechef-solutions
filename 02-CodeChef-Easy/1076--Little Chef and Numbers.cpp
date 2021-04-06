#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std ;


int32_t main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t ; cin >> t;
    while(t--)
    {
        int n;  cin >> n ;
        int a[n] ;
        int x1 = 0, x2 = 0 ;
        for(int i=0;i<n;i++) 
        {
            cin >> a[i] ;
            if(a[i] >= 2) x2++ ;
            if(a[i] == 2) x1++ ;
             
        }

        cout << x2*(x2-1)/2 - x1*(x1-1)/2 << endl ;

        
    }

}