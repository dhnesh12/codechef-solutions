#include<bits/stdc++.h>
#define pi 3.141592653589793238
#pragma GCC target ("avx2")
#pragma GCC optimization ("O3")
#pragma GCC optimization ("unroll-loops")
#define MOD 1000000007
#define INF 999999999999999999 
#define pb push_back
#define ff first
#define ss second
 
#define mt make_tuple
#define ll long long
#define fast ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
#include <ext/pb_ds/assoc_container.hpp>

using namespace __gnu_pbds;
 
 
typedef tree<ll, null_type, less_equal<ll>, rb_tree_tag, tree_order_statistics_node_update> indexed_set;
 
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const int N = 1e3 + 1;
double dp[N][N], a[N];
ll n;
double f(ll l, ll r){
    if(l > r){
        return 0;
    }
    if(dp[l][r] != -1){
        return dp[l][r];
    }
    double res;
    if((r - l + 1) % 2 == n % 2){
        res = (a[l] + a[r]) / 2 + (f(l + 1, r) + f(l, r - 1)) / 2;
    }
    else{
        res = (f(l + 1,r) + f(l, r - 1)) / 2;
    }
    //cout << res << endl;
    return dp[l][r] = res;
} 
int main() {
    //freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    fast;
    ll T = 1, i, j;
    
    cin >> T;
    while (T--) {
        cin >> n;
        for(i = 1; i <= n; i++){
            cin >> a[i];
        }
        for(i = 1; i <= n; i++){
            for(j = 1; j <= n; j++){
                dp[i][j] = -1;
            }
        }
        double ans = f(1, n);
        cout << fixed << setprecision(10) << ans << endl;
    }
    return 0;
}