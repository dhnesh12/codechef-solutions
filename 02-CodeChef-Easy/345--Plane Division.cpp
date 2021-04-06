#include<iostream>
#include<vector>
#include<utility>
#include<bits/stdc++.h>
using namespace std ;
#define INF 200000000000.0 
int main() 
{
    int t ;
    cin >> t ;
    while ( t -- > 0 )
    {
        int n ;
        cin >> n ;
        vector< pair < double , double > > pro ;
        int a [ n ]  , b [ n ] , c [ n ] ;
        double slope , intercept ;
        for ( int i = 0 ; i < n ; i ++ )
        {
            cin >> a[ i ] >> b[ i ] >> c[ i ] ;
            slope = ( a[ i ] == 0 ) ? INF : ( ( b[ i ] * 1.0 ) / a[ i ] ) ;
            intercept = ( a[ i ] == 0 ) ? ( ( c[ i ] * 1.0 ) / b[ i ] ) : ( ( c[ i ] * 1.0 ) / a[ i ] ) ;
            pro.push_back( make_pair( slope , intercept ) ) ; 
        }
        sort( pro.begin() , pro.end() ) ;
        int ans = 0 , curr = 1 ;
        for ( int i = 1 ; i < n ; i ++ )
        {
            if ( pro.at( i ).first == pro.at( i - 1 ).first && pro.at( i ).second != pro.at( i - 1 ).second )
            {
                curr ++ ;
            }
            else
            {
                if ( pro.at( i ).first != pro.at( i - 1 ).first )
                {
                    ans = max( ans , curr ) ;
                    curr = 1 ;
                }
            }
        }
        ans = max( ans , curr ) ;
        cout << ans << endl ;
    }
    return 0 ;
}