#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll dp[3005][2], dp2[3005][2];
int main(){ll n; cin >> n; ll a[n], ans = 0, m = 987654319;for (int i = 0; i < n; i++){cin >> a[i];}
    for (int i = 0; i < n; i++){ll cnt = 0;
        for (int j = 0; j < i; j++){if (a[j] > a[i]){(dp[i][1] += dp[j][0])%=m;cnt++;}
            else if(a[j] < a[i]){(dp[j][0] += cnt)%=m;}}}for (int i = n-1; i >= 0; i--){ll cnt = 0;
        for (int j = n-1; j > i; j--){if (a[j] < a[i]){(dp2[i][1] += dp2[j][0])%=m;cnt++;}
            else if(a[j] > a[i]){(dp2[j][0] += cnt)%=m;}}}
            for(int i=0;i<n;i++){(ans += (dp[i][1]*dp2[i][1])%m)%=m;}cout << ans;}