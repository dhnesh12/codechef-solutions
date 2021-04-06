#include <bits/stdc++.h>

using namespace std ;
bool dbg = false ;

//----------------------------------------------------------------------------------------------------------------------------------------------

typedef long long int LLI ;
typedef long double LD ;
typedef pair < int , int > PII ;
typedef pair < LLI , LLI > PLLILLI ;

typedef vector < int > VI ;
typedef vector < LLI > VLLI ;
typedef vector < bool > VB ;
typedef vector < string > VS ;
typedef vector < float > VF ;
typedef vector < double > VD ;
typedef vector < LD > VLD ;
typedef vector < PII > VPII ;
typedef vector < PLLILLI > VPLLILLI ;

#define FIE(i,start,stop) for ( int i = start , _stop = stop ; i < _stop ; i ++ )
#define FII(i,start,stop) for ( int i = start , _stop = stop ; i <= _stop ; i ++ )
#define FDEI(i,start,stop) for ( int i = start - 1 , _stop = stop ; i >= _stop ; i -- )
#define FDII(i,start,stop) for ( int i = start , _stop = stop ; i >= _stop ; i -- )
#define TR(it,container) for ( __typeof ( container.begin () ) it = container.begin () ; it != container.end () ; it ++ )
#define ASSERT(condition) if ( ! ( condition ) ) { cout << "ASSERT FAILED : " << #condition << " at line no - " << __LINE__ << endl ; }
#define DASH "<---------------------------------------------------------------->"
#define PV1(x) if ( dbg ) { cout << "--> " << #x << ":" << x << endl ; }
#define PV2(x1,x2) if ( dbg ) { cout << "--> " << #x1 << ":" << x1 << ", " << #x2 << ":" << x2 << endl ; }
#define PV3(x1,x2,x3) if ( dbg ) { cout << "--> " << #x1 << ":" << x1 << ", " << #x2 << ":" << x2 << ", " << #x3 << ":" << x3 << endl ; }
#define ALL(x) x.begin () , x.end ()
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define LB lower_bound
#define UB upper_bound
#define endl '\n'
#ifndef ONLINE_JUDGE
    #define DBG 1
#endif

void WAIT ()
{
    #ifdef SHELL
        cout << endl << endl << DASH << endl ;
        cout << "ENTER 0 TO EXIT" << endl ;
        fflush ( stdin ) ; fflush ( stdout ) ; cout.flush () ; cin.clear () ; 
        char ch ; do { cin >> ch ; } while ( ch != '0' ) ;
    #endif
}

void FAST ()
{
    #ifndef ONLINE_JUDGE
        dbg = true ;
    #endif
    ios::sync_with_stdio ( false ) ; cin.tie ( NULL ) ;
}

#define INF 1000000000
#define LINF 1000000000000000000LL
#define FERROR 0.000001
#define DERROR 0.0000000001

//----------------------------------------------------------------------------------------------------------------------------------------------

const int N = 1e4 ;
int n , e , u , v ;
LLI ans , MOD = 1000000007 ;
VI edges [ N + 1 ] ;
LLI sz [ N + 1 ] , temp [ N + 1 ] ;

void dfs ( int cur , int par )
{
    FIE ( i , 0 , edges [ cur ].size () )
    {
        int to = edges [ cur ] [ i ] ;
        if ( to != par )
        {
            dfs ( to , cur ) ;
            sz [ cur ] += sz [ to ] ;
        }
    }
    PV1 ( sz [ cur ] ) ;
    temp [ cur ] = ( sz [ cur ] + sz [ cur ] - 1 ) % MOD ;
    FIE ( i , 0 , edges [ cur ].size () )
    {
        int to = edges [ cur ] [ i ] ;
        if ( to != par )
        {
            temp [ cur ] = ( temp [ cur ] + ( ( sz [ cur ] - 1 - sz [ to ] ) * sz [ to ] ) % MOD ) % MOD ;
        }  
    }
    PV1 ( temp [ cur ] ) ;
}

void solve ()
{
    fill_n ( & sz [ 0 ] , N + 1 , 1 ) ;
    dfs ( 1 , 1 ) ;
    ans = 0 ;
    FII ( i , 1 , n )
    {
        ans = ( ans +  ( i * temp [ i ] ) % MOD ) % MOD ;
    }
    cout << ans << endl ;
}

int main ()
{
    FAST () ;
    
    int t ;
    cin >> t ;
    while ( t -- )
    {
        cin >> n ;
        FII ( i , 1 , n )
        {
            edges [ i ].clear () ;
        }
        e = n - 1 ;
        FIE ( i , 0 , e )
        {
            cin >> u >> v ;
            edges [ u ].PB ( v ) ;
            edges [ v ].PB ( u ) ;
        }
        solve () ;
    }

    WAIT () ;
    return 0 ;
}