#include<bits/stdc++.h>

#define ll long long

using namespace std;

int main(){
    cin.tie(NULL);
    ios_base::sync_with_stdio(0);
    int T = 1;
    cin >> T;
    while(T--){
        ll n, m, x0, xl, xr, x2;
        cin >> n >> m >> x0 >> xl >> xr >> x2;

        ll sz = n * m;

        if(sz - xl - xr - x0 <= 0){
            cout << sz << "\n";
            continue;
        }

        ll S, rest;

        S = n * m - xl - xr;
        rest = S;

        ll k = S + n - m * n;

        ll can=0;

        if (k<0) k=0;

        can += (m+1) / 2 * k;
        S -= (m + 1) / 2 * k;
        rest -= m*k;

        n-=k;

        can += n-1;
        S -= n-1;
        rest -= n-1;

        can += (rest + 1) / 2;
        S -= (rest + 1) / 2;

        if (x2 < can){
            S += can - x2;
            can = x2;
        }

        can += min(S, x0);

        cout << min(can + xl + xr, sz) << "\n";
    }
}