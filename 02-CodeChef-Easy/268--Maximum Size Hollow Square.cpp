//BISMILLAHIR RAHMANIR RAHIM
//RABBI ZIDNI ILMA
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"
#define ff first
#define ss second
#define inf (1LL<<61)
#define pi acos(-1)
#define mod 1000000007
#define MOD 998244353
#define all(x) x.begin(), x.end()
#define intPow(n, p) (ll)(pow(n, p) + 0.5)
#define fastio ios_base::sync_with_stdio(0); cin.tie(NULL);
#define debug(x) cout<<"["<<#x<<": "<<x<<"]\n"
#define debug2(x, y) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]\n"
#define debug3(x, y, z) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]"<<"  ["<<#z<<": "<<z<<"]\n"
#define debug4(x, y, z, k) cout<<"["<<#x<<": "<<x<<"]"<<"  ["<<#y<<": "<<y<<"]"<<"  ["<<#z<<": "<<z<<"]"<<"  ["<<#k<<": "<<k<<"]\n"

const ll N = 1e3 + 9;

ll cntR[N][N], cntC[N][N], tot;
ll n, m, k;
ll cnt[1002][1002];

ll possible(ll side)
{
    //debug(side);

    for(int i=0; i<=n; i++){
        for(int j=0; j<=m; j++) cnt[i][j] = 0;
    }

    for(int i=1; i+side-1<=n; i++){
        for(int row=i; row<=i+side-1; row++) cnt[i][1] += cntR[row][side];
        for(int j=2; j+side-1<=m; j++){
            cnt[i][j] += cnt[i][j-1];
            cnt[i][j] -= cntC[j-1][i+side-1] - cntC[j-1][i-1];
            cnt[i][j] += cntC[j+side-1][i+side-1] - cntC[j+side-1][i-1];
        }
    }
    //debug(side);
    for(int i=1; i+side-1<=n; i++){
        for(int j=1; j+side-1<=m; j++){
            //debug3(i, j, cnt[i][j]);
            ll one = tot - cnt[i][j];
            ll zer = n*m - side*side - one;
            if(zer>=cnt[i][j] && cnt[i][j]<=k) return 1;
        }
    }
    return 0;
}

int main()
{
    fastio
    ll tt;
    cin>> tt;
    while(tt--){
        cin>> n >> m >> k;

        tot = 0;
        for(int i=0; i<=n; i++){
            for(int j=0; j<=m; j++){
                cntR[i][j] = 0;
                cntC[i][j] = 0;
            }
        }
        vector<string> a(n+1);
        for(int i=1; i<=n; i++){
            cin>> a[i];
            a[i] = '.' + a[i];
        }

        for(int i=1; i<=n; i++){
            for(int j=1; j<=m; j++){
                //debug3(i,j,a[i][j]);
                cntR[i][j] = cntR[i][j-1] + (a[i][j]-'0');
                cntC[j][i] = cntC[j][i-1] + (a[i][j]-'0');
                tot += (ll)(a[i][j]=='1');
                //debug3(i,j,cntR[i][j]);
                //debug3(j,i,cntC[j][i]);
            }
        }

        ll l=1, r=min(n,m), ans = 0;
        while(l<=r){
            ll m = (l+r)/2;
            //debug(m);
            if(possible(m)){
                ans = max(ans, m);
                l = m+1;
            }
            else r = m-1;
        }

        cout<< ans << endl;
    }
}
