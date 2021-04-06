#include <memory.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cctype>
#include <cstring>
#include <climits>
#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <numeric>
#include <limits>
#include <functional>
#include <tuple>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>

using namespace std;

#define PROFILE_START(i)    clock_t start##i = clock()
#define PROFILE_STOP(i)     fprintf(stderr, "elapsed time (" #i ") = %f\n", double(clock() - start##i) / CLOCKS_PER_SEC)

typedef long long           ll;
typedef unsigned long long  ull;

int gK;

#if 0
ll solve2(ll N, ll M) {
    ll cnt = N / gK + 1;

    if (N == 1)
        return M;
    else if (N == 2)
        return -1;
    else if (N == 3)
        return M;
    else if (N == 4)
        return M - 2;

    if (M == 2) {
        if (N == 5)
            return M - 2;

        ll x = (N - 4) + 1;
        if ((x & (x - 1)) == 0)
            return 0;
        else
            return -1ll;
    } else if (M == 3) {
        if (N == 5)
            return M - 3;
        else if (N == 6)
            return -1ll;
        else if (N == 7)
            return 0;

        ll x = (N - 6) + 1;
        if ((x & (x - 1)) == 0)
            return 0;
        else
            return -1ll;
    } else if (M == 4) {
        if (N == 5)
            return M - 3;
        else if (N == 6)
            return -1ll;
        else if (N == 7)
            return M - 3;
        else if (N == 8)
            return -1ll;
        else if (N < 10)
            return M - 3;

        ll x = (N - 8) + 1;
        if ((x & (x - 1)) == 0)
            return 0;
        else
            return -1ll;
    } else if (M == 5 || M == 6) {
        if (N == 5)
            return M - 3;
        else if (N == 6)
            return -1ll;
        else if (N == 7)
            return M - 3;
        else if (N == 8)
            return M - 4;
        else if (N == 9)
            return M - 5;
        else if (N < 13)
            return -1;

        ll x = (N - 10) + 1;
        if ((x & (x - 1)) == 0)
            return M - 5;
        else
            return -1ll;
    } else {
        if (N == 5)
            return M - 3;
        else if (N == 6)
            return -1ll;
        else if (N == 7)
            return M - 3;
        else if (N == 8)
            return M - 4;

        ll base = gK * M;

        if (N <= base - 2)
            return M - cnt;
        else if (N < base)
            return M - cnt + 1;
        else if (N == base)
            return -1ll;
        else if (N == base + 1)
            return M - cnt + 2;

        ll x = (N - base) + 1;
        if ((x & (x - 1)) == 0)
            return 0;
        else
            return -1ll;
    }
}
#else
ll solve2(ll N, ll M) {
    if (N == 1)
        return M;
    else if (N == 2)
        return -1ll;
    else if (N == 3)
        return M;
    else if (N == 4)
        return M - 2;

    vector<ll> dp[2];
    int from = 0, to = 1;

    dp[0].resize(2);
    dp[0][0] = 1;
    dp[0][1] = 2;
    ll last = M - 2;
    ll failN = 0;

    for (ll i = 5; i <= N; i++) {
        dp[to].clear();
        dp[to].resize(dp[from].size() + 1);

        ll leftM = M;
        ll leftN = i / gK - failN;

        if (left <= 0) {
            ++dp[to][0];
            for (int j = 0; j < int(dp[from].size()); j++)
                dp[to][0] += dp[from][j];
            dp[to][0] += failN;

            while (!dp[to].back())
                dp[to].pop_back();

            last = leftM;
            failN = 0;

            swap(from, to);

            continue;
        }

        int j = 0;
        for (; j < gK && j < int(dp[from].size()) && leftN > 0 /*&& leftM > 0*/; j++) {
            auto cntM = leftM / (j + 1);
            if (cntM <= 0)
                break;

            auto t = dp[from][j] + (last == j);
            if (t <= 0)
                continue;

            ll n = min(leftN, min(t, cntM));
            if (n <= 0) {
                //leftM = -1;
                break;
            }
            dp[to][j + 1] += t;
            leftN -= n;
            leftM -= n * (j + 1);
        }

        if (leftN > 0 || leftM < 0) {
            failN++;
        } else {
            if (last >= j)
                ++dp[to][0];
            for (; j < int(dp[from].size()); j++)
                dp[to][0] += dp[from][j];
            dp[to][0] += failN;

            while (!dp[to].back())
                dp[to].pop_back();

            last = leftM;
            failN = 0;

            swap(from, to);
        }
    }

    return failN > 0 ? -1ll : last;
}
#endif

ll solve(ll N, ll M) {
    if (gK == 2)
        return solve2(N, M);

    if (N < gK)
        return M;
    else
        return M - N / gK;
}

namespace FastIO {
    char gInBuff[1 << 25];
    const char* gInPtr;

    void init() {
        gInPtr = gInBuff;
        auto size = fread(gInBuff, 1, sizeof(gInBuff) - 1, stdin);
        gInBuff[size] = 0;
    }

    int readInt() {
        int u = 0;

        while (*gInPtr && *gInPtr <= 32)
            ++gInPtr;

        while (*gInPtr >= '0' && *gInPtr <= '9')
            u = (u << 3) + (u << 1) + (*gInPtr++ - '0');

        return u;
    }

    ll readLL() {
        ll u = 0;

        while (*gInPtr && *gInPtr <= 32)
            ++gInPtr;

        while (*gInPtr >= '0' && *gInPtr <= '9')
            u = (u << 3) + (u << 1) + (*gInPtr++ - '0');

        return u;
    }
}

#if 0
int main(void) {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);

    FastIO::init();

    int Q;
    gK = FastIO::readInt();
    Q = FastIO::readInt();

    while (Q-- > 0) {
        ll N = FastIO::readLL();
        ll M = FastIO::readLL();

        auto ans = solve(N, M);
        if (ans < 0)
            printf("Thrown off the roof.\n");
        else
            printf("%lld\n", ans);
    }    

    return 0;
}
#else

#define MAXN    1e18

ll gF[3000005];

ll calc(ll x, int K){
    if(x <= MAXN / K)
        return x * K / (K - 1) + 1;

    ll TT = ll(1e9);
    ll a = x % TT;
    ll b = x / TT;

    a *= K;
    b *= K;
    b += a / TT;
    a %= TT;

    return b / (K-1) * TT + (a + b % (K-1) * TT) / (K - 1) + 1;
}

void buildTable(int K) {
    gF[1] = K + 1;
    for (gF[0] = 1; gF[gF[0]] <= MAXN; gF[0]++) {
        gF[gF[0] + 1] = calc(gF[gF[0]], K);
    }
}

int main(void) {
    //ios_base::sync_with_stdio(false);
    //cin.tie(nullptr);

    FastIO::init();

    int Q;
    gK = FastIO::readInt();
    Q = FastIO::readInt();

    buildTable(gK);

    while (Q-- > 0) {
        ll N = FastIO::readLL();
        ll M = FastIO::readLL();

        if (N / gK > M) {
            if (*lower_bound(gF + 1, gF + 1 + gF[0], N - M * gK) == N - M * gK)
                printf("0\n");
            else
                printf("Thrown off the roof.\n");
        } else if (gK == 2) {
            if (N <= 3) {
                if (N == 2)
                    printf("Thrown off the roof.\n");
                else
                    printf("%lld\n", M);
            } else {
                printf("%lld\n", M - (N + 1) / gK);
            }
        } else {
            printf("%lld\n", M - N / gK);
        }
    }    

    return 0;
}
#endif