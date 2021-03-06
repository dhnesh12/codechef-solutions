/***********Template Starts Here***********/
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#include <deque>
#include <functional>
#include <string>
#include <iostream>
#include <cctype>
#include <set>

#define pb push_back
#define nl puts ("")
#define sp printf ( " " )
#define phl printf ( "hello\n" )
#define ff first
#define ss second
#define popcount __builtin_popcount
#define rightmost __builtin_ctz

using namespace std;

typedef long long vlong;
typedef unsigned long long uvlong;
typedef vector < int > vi;
typedef pair < int, int > ii;
typedef pair < vlong, vlong > lili;
typedef vector < ii > vii;

template < class T > T sq( T x ) { return x * x; }

const vlong inf = 2147383647;
const double pi = 2 * acos ( 0.0 );
const double eps = 1e-9;
const vlong maxint = 2147483647;
const vlong minint = -2147483648;

vlong gcd ( vlong a, vlong b ) {
    a = abs ( a ); b = abs ( b );
    while ( b ) {
        a = a % b;
        swap ( a, b );
    }
    return a;
}

vlong bigmod ( vlong a, vlong p, vlong m ) {
    vlong res = 1, x = a % m;
    while ( p ) {
        if ( p & 1 ) res = ( res * x ) % m;
        x = ( x * x ) % m;
        p >>= 1;
    }
    return res;
}


/***********Template Ends Here***********/

int arr[100010];
int n;

vlong mod = 1000000007;

vlong sum[250][210];

int main () {
    #ifdef forthright48
    //freopen ( "input.txt", "r", stdin );
    //freopen ( "output.txt", "w", stdout );
    #endif

    int kase;
    scanf ( "%d", &kase );


    while ( kase-- ) {

        scanf ( "%d", &n );

        int i;
        for ( i = 0; i < n; i++ ) {
            scanf ( "%d", &arr[i] );
        }

        memset ( sum, 0, sizeof sum );

        vlong res = 1;
        int d;

        for ( i = n - 1; i >= 0; i-- ) {
            vlong a = arr[i];

            for ( d = -100; d <= 100; d++ ){
                vlong r = 1;
                vlong ta = a + d;
                if ( ta >= 0 && ta <= 100 ) {
                    r += sum[d+100][ta];
                    if ( r > mod ) r -= mod;
                }

                sum[d+100][a] += r;
                if ( sum[d+100][a] > mod ) sum[d+100][a] -= mod;

                res += r - 1;
                if ( res > mod ) res -= mod;
            }

            res++;
        }

        res %= mod;
        vlong total = bigmod ( 2, n, mod );

        total = ( total - res ) % mod;
        if ( total < 0 ) total += mod;

        printf ( "%lld\n", total );

    }


    return 0;
}
