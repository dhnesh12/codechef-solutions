#include <cstdio>
using namespace std;

typedef unsigned long long uint64;

uint64 Power(uint64 x, uint64 e) {
    uint64 answer = 1;
    while (e != 0) {
        if (e % 2 != 0) answer *= x;
        x *= x;
        e /= 2;
    }
    return answer;
}

struct MP2 {
    uint64 M;
    int P2;

    explicit MP2(uint64 x) : M(x), P2(0) {
        while (M % 2 == 0) {
            M /= 2;
            ++P2;
        }
    }

    void operator*=(const MP2& that) {
        M *= that.M;
        P2 += that.P2;
    }

    void operator/=(const MP2& that) {
        M *= Power(that.M, (1ULL << 63) - 1);
        P2 -= that.P2;
    }
};

struct Solution {
    uint64 N, K;

    uint64 Choose() {
        if (N - K < K) K = N - K;
        MP2 answer1(1), answer2(1);
        for (int i = 1; i <= K; ++i) {
            answer1 *= MP2(N + 1 - i);
            answer2 *= MP2(i);
        }
        answer1 /= answer2;
        return answer1.M << answer1.P2;
    }

    void Solve() {
        scanf("%llu%llu", &N, &K);
        if (N < K) {
            printf("0\n");
        } else {
            printf("%llu\n", Choose());
        }
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
