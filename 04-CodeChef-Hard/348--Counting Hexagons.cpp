#include <iostream>
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1000000007;

const int IN_LEN = 500100, OUT_LEN = 2000000;
char ibuf[IN_LEN], obuf[OUT_LEN], *ih = ibuf, *oh = obuf;

inline void read(int &x) { for (x = 0; !isdigit(*ih); ih++); while (isdigit(*ih)) x = (x << 1) + (x << 3) + ((*ih++) ^ '0'); }
inline void write(int x) {
    static int buf[30], cnt;
    if (!x) *oh++ = 48;
    else {
        for (cnt = 0; x; x /= 10) buf[++cnt] = x % 10 + 48;
        while (cnt) *oh++ = buf[cnt--];
    }
}


inline int pow(int x, int y) {
    int rt = 1;
    while (y) {
        if (y & 1) rt = rt * (ll)x % mod;
        x = x * (ll)x % mod; y >>= 1;
    }
    return rt;
}

inline int calculate(ll n, int k) {
    if (n < 0) return 0;
    switch (k) {
    case 0:
        return (ll)(n + 1) * (n + 2) % mod * (n + 3) % mod * (n + 4) % mod * (n + 5) % mod * pow(120, mod - 2) % mod;
    case 1: {
        int t = n / 2, rt = (ll)(n + 3) * (n + 2) % mod * (n + 1) % mod * (t + 1) % mod;
        rt = (rt - (ll)t * (t + 1) / 2 % mod * (((ll)n * n % mod * 3 + n * 12ll + 11) % mod) % mod * 2) % mod;
        rt = (rt + (ll)t * (t + 1) % mod * (t * 2ll + 1) % mod * pow(6, mod - 2) % mod * (n * 3ll + 6) % mod * 4) % mod;
        rt = (rt - (ll)t * (t + 1) / 2 % mod * ((ll)t * (t + 1) / 2 % mod) % mod * 8) % mod;
        return (ll)rt * pow(6, mod - 2) % mod;
    }
    case 2: {
        int t = n / 2, rt = (ll)(n + 1) * (t + 1) % mod;
        rt = (rt + (ll)t * (t + 1) / 2 % mod * (n - 1)) % mod;
        rt = (rt - (ll)t * (t + 1) % mod * (t * 2ll + 1) % mod * pow(6, mod - 2) % mod * 2) % mod;
        return rt;
    }
    case 3: {
        int t = n / 3, rt = (ll)(n + 2) * (n + 1) % mod * (t + 1) % mod;
        rt = (rt - (ll)t * (t + 1) / 2 % mod * ((n * 2ll + 3) % mod) % mod * 3) % mod;
        rt = (rt + (ll)t * (t + 1) % mod * (t * 2ll + 1) % mod * pow(6, mod - 2) % mod * 9) % mod;
        return (ll)rt * pow(2, mod - 2) % mod;
    }
    case 4: {
        int t = n / 3, rt = ((ll)(t + 1) * n % mod * pow(2, mod - 2) - (ll)t * (t + 1) % mod * pow(4, mod - 2) % mod * 3) % mod;
        if (n & 1) return (rt - (ll)(t / 2 + 1) * pow(2, mod - 2) + t + 1) % mod;
        return (rt - (ll)(t - t / 2) * pow(2, mod - 2) + t + 1) % mod;
    }
    case 5: {
        return (ll)(n / 4 + 1) * (n + 1 - n / 4 * 2ll) % mod;
    }
    case 6: {
        return (n / 5 + 1) % mod;
    }
    }
}

inline int calculateInvalid(int n, int m, int k) {
    static const int c[][6] = {
        {1, -5, 10, -10, 5, -1},
        {1, -3, 2, 2, -3, 1},
        {1, -1, -2, 2, 1, -1},
        {1, -2, 1, -1, 2, -1},
        {1, 0, -1, -1, 0, 1},
        {1, -1, 0, 0, -1, 1},
        {1, 0, 0, 0, 0, -1}
    };
    int rt = 0;
    if ((n -= 5) < 0) return 0;
    for (int i = 0; i < 6; ++i)
        rt = (rt + c[k][i] * (ll)calculate(n - m * (ll)i, k)) % mod;
    return rt;
}

inline int solve(int n, int m, int k) {
    static const int tp[] = {5, 4, 3, 3, 2, 2, 1};
    static const int rep[] = {1, 2, 2, 3, 3, 4, 5};
    static const int fac[] = {120, 6, 2, 2, 1, 1, 1};
    static const int exc[][7] = {
        {0, 60, 30, 20, 10, 5, 1},
        {0, 0, 6, 6, 4, 3, 1},
        {0, 0, 0, 0, 2, 1, 1},
        {0, 0, 0, 0, 1, 2, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0}
    };
    int rt = 0, f[7];
    for (register int i = 6; ~i; --i) {
        f[i] = (pow(m, tp[i]) - calculateInvalid(n, m, i)) % mod;
        for (register int j = i + 1; j < 7; ++j)
            f[i] = (f[i] - exc[i][j] * (ll)f[j]) % mod;
        f[i] = f[i] * (ll)pow(fac[i], mod - 2) % mod;
        if (rep[i] <= k) rt = (rt + f[i]) % mod;
    }
    return rt;
}

int main() {
    int n, l, r, k;
    scanf("%d%d%d%d", &n, &r, &l, &k);
    int ans = 0;
    for (int i = r; i <= n; ++i)
        ans = (ans + solve(i, l, k)) % mod;
    printf("%d\n", (ans + mod) % mod);
    return 0;
}