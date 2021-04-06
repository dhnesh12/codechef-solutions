#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int n, fac[20], a[20], dp[1<<19], lim;
void qmo(int &x){x += x >> 31 & mod;}
int sum(int S){
    int res = 0;
    for(int i = 0;i < n;++ i)
        if(S >> i & 1) res += a[i];
    return res % 239;
}
int main(){
    scanf("%d", &n); fac[0] = 1;
    for(int i = 0;i < n-1;++ i) fac[i+1] = (239ll - i) * fac[i] % mod;
    for(int i = 0;i < n;++ i) scanf("%d", a + i);
    dp[0] = sum((1<<n)-1) ? 1 : 239; lim = 1 << n-1;
    for(int S = 1;S < lim;++ S)
        if(sum((1<<n)-1-S)){
            dp[S] = fac[__builtin_popcount(S)];
            for(int i = 0;i < n-1;++ i)
                if(S >> i & 1) qmo(dp[S] -= dp[S ^ (1<<i)]);
        } else dp[S] = (239ll - __builtin_popcount(S)) * dp[S ^ (S & -S)] % mod;
    printf("%d\n", dp[lim-1]);
}