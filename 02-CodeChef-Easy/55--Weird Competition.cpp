#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) \
    for ( i = (a); i < (b); i++ )
#define ROF(i, a, b) \
    for ( i = (b); (a) < i--; )
inline int paritybit(int n){return n % 2;}
int main(int argc, char* argv[]){ios_base::sync_with_stdio(false); int ntest, t; cin >> ntest;
    FOR(t, 0, ntest){int n, k, i, j; cin >> n >> k; int kmax = n * (n-1) * (2*n-1) / 6, kmin;
        if (paritybit(n)){kmin = n * ((n-1)/2) * ((n-1)/2);}
        else{kmin = n * ((n/2-1) * (n/2-1) + (n/2) * (n/2)) / 2;}
        if (k < kmin || k > kmax || paritybit(k) != paritybit(kmax))
        {fwrite_unlocked("-1\n", 1, 3, stdout);continue;}static char m[1000][1000]; static int  z[1000];
        FOR(i, 0, n){FOR(j, 0, i+1){m[i][j] = '0';}FOR(j, i+1, n){m[i][j] = '1';}z[i] = n-1-i;}int u=kmax - k;
        for (i = 0; i < n/2 && u != 0; i++){
            ROF(j, i+1, n){int v = 2*(z[i] - z[j] - 1); if (v < 2){break;}
                if (v <= u){swap(m[i][j], m[j][i]); u -= v;
                    if (u == 0)
                    break;
                    z[i] -= 1;
                    z[j] += 1;}}}
        FOR(i, 0, n){fwrite_unlocked(m[i], 1, n, stdout);putchar_unlocked('\n');}}}