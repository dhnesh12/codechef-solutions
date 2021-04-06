#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

long long m;
vector < long long > ans;
vector < long long > divs;
vector < long long > cntd;

void getDivs ( long long x ) {
    for ( long long i = 2 ; i*i <= x ; i ++ ) {
        if ( x%i == 0 ) {
            long long cnt = 0;
            while ( x%i == 0 ) {
                cnt ++;
                x /= i;
            }
            divs.push_back( i );
            cntd.push_back( cnt );
        }
    }
    if ( x != 1 ) {
        divs.push_back( x );
        cntd.push_back( 1 );
    }
}
void gg ( long long ind, long long km, long long p ) {

    if ( ind == divs.size() ) {
        //if ( m + km*km*p <= (m + km*km*p)*m/( km*km*p ) ) {
            ans.push_back( m + km*km*p );
        //}
        return;
    }
    long long cc = 1;
    for ( long long i = 0 ; i <= 2*cntd[ind] ; i ++ ) {

        double cp = 1.*cc;
        cp *= p;
        if ( cp - 10 > m ) {break; }

        if ( p*cc > m ) {break; }
        gg( ind+1, km, p*cc );
        cc *= divs[ind];
    }


}
void solve () {
    divs.clear();
    cntd.clear();
    ans.clear();
    cin >> m;
    getDivs( m );
    gg( 0, 1, 1 );

    sort( ans.begin(), ans.end() );
    cout << ans.size() << "\n";
    for ( long long i = 0 ; i < ans.size() ; i ++ ) {
        cout << ans[i] << "\n";
    }

}
int main () {
    int t;
    cin >> t;
    while ( t -- ) {
        solve();
    }
    return 0;
}

