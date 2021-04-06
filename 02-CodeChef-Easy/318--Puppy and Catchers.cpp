#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef vector<int> vi;
#define m7 1000000007
#define ff first
#define ss second
#define pb push_back
#define rep(n) for(int i=0; i<n; i++)

void fastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
}

bool pof2(int n){	//Check whether a number is a power of 2.
    if(n < 1)
        return false;
    double logn = log2(n);
    return floor(logn) == ceil(logn);
}

int main() {

    fastIO();

    int n,m;
    string s;
    cin >> n >> m;

    int x[n+1], y[n+1];
    ll xsum[n+1] = {};
    ll ysum[n+1] = {};
    for(int i=1; i<n+1; i++)
        cin >> x[i] >> y[i];
    cin >> s;
    
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);

    xsum[1] = x[1], ysum[1] = y[1];
    for(int i=2; i<n+1; i++){
        xsum[i] = x[i] + xsum[i-1];
        ysum[i] = y[i] + ysum[i-1];
    }

    int u,v;
    u = v = 0;

    rep(m){
        switch(s[i]){
            case 'D':
                v--;
                break;
            case 'U':
                v++;
                break;
            case 'R':
                u++;
                break;
            default:
                u--;
                break;
        }
        int cx,cy;
        cx = upper_bound(x+1,x+n+1,u) - (x+1);
        cy = upper_bound(y+1,y+n+1,v) - (y+1);

        ll ans = 0;
        ans += (1ll*cx*u - xsum[cx]) + (1ll*cy*v - ysum[cy]);
        ans += (xsum[n] - xsum[cx]) - 1ll*(n-cx)*u + (ysum[n] - ysum[cy]) - 1ll*(n-cy)*v;

        cout << ans << endl;
    }
}