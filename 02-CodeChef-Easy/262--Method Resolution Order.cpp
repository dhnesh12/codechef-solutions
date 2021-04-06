#include <bits/stdc++.h>

using namespace std;

const int MOD = (int)1e9 + 7;

inline int add(int x, int y){
    int res = x + y;
    if (res >= MOD) res -= MOD;
    return res;
}
inline int sub(int x, int y){
    return add(x - y, MOD);
}
inline int mul(int x, int y){
    return (x * 1LL * y) % MOD;
}

const int MAX_N = (int)1e5 + 5;

int dp[MAX_N];

int main()
{
    dp[1]  = 1;
    int pw = 1;
    for (int i = 2; i < MAX_N; i++){
        pw = mul(pw, 2);
        dp[i] = mul(sub(pw, 1), dp[i - 1]);
    }

    int TC; scanf("%d", &TC);
    while(TC--){
        int n; scanf("%d", &n);
        printf("%d\n", dp[n]);
    }
    return 0;
}
