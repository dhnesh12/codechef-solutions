#include <bits/stdc++.h>
#define MOD 1000000007
using namespace std;
int main(){
    ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); long long t; cin >> t;
    while(t--){long long n, k, m; cin >> n >> k >> m; long long a[n + 1], subs[k + 1], dp[k + 1];
        for (long long i = 1; i <= n; i++){cin >> a[i]; a[i] %= m;}
        for(long long i = 1; i <= k; i++){subs[i] = i % m;}
        for(long long i = 1; i <= k; i++){dp[i] = 0;} dp[0] = 0;
        for(long long i = 1; i <= n; i++){long long start = subs[k] - a[i]; if (start < 0){start += m;}
            for (long long j = k - start; j >= 1; j-=m){dp[j] += dp[j - 1];if (j == 1){dp[j]++;}dp[j] %= MOD;}}
        cout << dp[k] << endl;}}