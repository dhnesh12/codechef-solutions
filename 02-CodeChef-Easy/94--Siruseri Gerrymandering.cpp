#include <bits/stdc++.h>
using namespace std;
#define rep(i,a) for(int i = 0 ; i < a; i++)
#define F first
#define S second
#define ll long long
#define pii pair<int,int>
void solve(){int a,b; cin >> a >> b; int n = a*b; int x[n],y[n]; rep (i,n){cin >> x[i];}
    int ct[n],ptr = 0; pii p[n];
    rep (i,n){cin >> y[i]; ct[i] = 1; p[i].F = -max(x[i],y[i]); p[i].S = (x[i]>y[i]);}
    sort (p,p+n); int ans = 0, done = 0;
    rep (i,n){if (ptr == n){ans += (n-done)/b; break;}
        if (ct[i]){done++; ptr = max(ptr,i+1); int cnt = 0;
            while (ptr < n){if (cnt == b-1){break;} if (p[ptr].S == 0){ct[ptr] = 0; cnt++; done++;}ptr++;}
            if (p[i].S == 1){ans++;}}}cout << ans << endl;}
int main(){ios_base::sync_with_stdio(0); cin.tie(NULL); cout.tie(NULL); cout << fixed << setprecision(13);
    clock_t beg = clock(); int t = 1, n; cin >> t; while(t--){solve();} clock_t end = clock();
    fprintf (stderr, "%lf sec\n", (double)(end-beg)/(CLOCKS_PER_SEC));}