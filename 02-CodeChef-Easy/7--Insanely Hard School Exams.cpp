#include <bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
const int N = 5010;
const int M = mod;
int ans[N][N], sz[N];
int dp[N], dp1[N];
int32_t main(){int t; cin >> t;
    while(t--){int n, c, k, x, y, z; cin >> n >> c >> k;
        for (int i = 0; i <= k; i++){dp[i] = 0; if (i > 0){dp[i] = M * M;}}
        vector <int> v, v1; map<int, int> m[N];
        for(int i = 0; i < n; i++){cin >> x >> y >> z; m[z-1][x]++;}
        for (int i = 0; i < c; i++){cin >> x; v.push_back(x);
            for (auto x : m[i]){v1.push_back(x.second);} sort(v1.begin(), v1.end()); y = 0;
            for (int j = 0; j < v1.size(); j++){
                while (v1[j] > 0){int cnt1,cnt2,cnt3; cnt1 = cnt2 = cnt3 = 0;
                    for(auto z : v1){cnt1 += z; cnt2 += z*z;cnt3 += z*z*z;}
                    ans[i][y++] =  (cnt1*cnt1*cnt1 + 2*cnt3 - 3*cnt2*cnt1) / 6;
                    v1[j]--;}}ans[i][y] = 0; sz[i] = y; v1.clear();}
        for (int i = 0; i < c; i++){for (int j = 0; j <= k; j++){dp1[j] = M * M;}
            for (int j = 0;j <= k; j++){
                for(int l=0;l<=sz[i];l++){x = j + l*v[i]; if (k < x){break;}
                dp1[x] = min(dp1[x] , dp[j] + ans[i][l]);}}
            for (int j = 0; j <= k; j++){dp[j] = dp1[j];}}
        int ans = dp[0]; for (int i = 0; i <= k; i++){ans = min(ans , dp[i]);} cout << ans << endl;}}