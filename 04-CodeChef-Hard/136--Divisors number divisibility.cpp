#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <set>
#include <vector>
using namespace std;

typedef long long int64;

const int kWitness[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};

int64 AddMod(int64 a, int64 b, int64 m) {
    int64 answer = a + b;
    m &= (m - answer) >> 63;
    return answer - m;
}

int64 MulMod(int64 a, int64 b, int64 m) {
    int64 answer = 0;
    while (b) {
        if (b & 1) answer = AddMod(answer, a, m);
        a = AddMod(a, a, m);
        b >>= 1;
    }
    return answer;
}

int64 PowMod(int64 a, int64 b, int64 m) {
    int64 answer = 1;
    while (b) {
        if (b & 1) answer = MulMod(answer, a, m);
        a = MulMod(a, a, m);
        b >>= 1;
    }
    return answer;
}

struct Prime {
    int64 N, D, R;

    bool Witness(int64 a) {
        if (N - 2 <= a) return false;
        int64 x = PowMod(a, D, N);
        if (x == 1 || x == N - 1) return false;
        for (int j = 1; j < R; ++j) {
            x = MulMod(x, x, N);
            if (x == N - 1) return false;
        }
        return true;
    }

    bool Get(int64 n) {
        if (n <= 1) return false;
        if (n == 2) return true;
        if (n % 2 == 0) return false;
        N = n;
        D = n - 1;
        R = 0;
        while (D % 2 == 0) {
            D /= 2;
            ++R;
        }
        for (int i = 0; i < 12; ++i) {
            if (Witness(kWitness[i])) return false;
        }
        return true;
    }
};

bool PerfectSquare(int64 n) {
    int64 x = round(sqrt((long double)n));
    return x * x == n;
}

vector<int> Primes;

vector<int> Sieve(int m) {
    vector<bool> composite(m + 1);
    vector<int> answer;
    for (int i = 2; i <= m; ++i) {
        if (composite[i]) continue;
        answer.push_back(i);
        for (int64 j = int64(i) * i; j <= m; j += i) composite[j] = true;
    }
    return answer;
}

void Prepare() { Primes = Sieve(1100000); }

struct Solution {
    int64 N;

    vector<int64> TryFactorize(int64 n) {
        vector<int64> answer;
        for (int64 i = 0; Primes[i] <= n / Primes[i] / Primes[i]; ++i) {
            while (n % Primes[i] == 0) {
                answer.push_back(Primes[i]);
                n /= Primes[i];
            }
        }
        if (1 < n) {
            answer.push_back(n);
            if (PerfectSquare(n)) answer.push_back(n);
            if (!Prime().Get(n)) answer.push_back(0);
        }
        return answer;
    }

    void Solve() {
        scanf("%lld", &N);
        if (N == 1 || N == 4) {
            printf("1\n");
        } else {
            vector<int64> factors = TryFactorize(N);
            int d = set<int64>(factors.begin(), factors.end()).size();
            if (d != factors.size()) {
                printf("-1\n");
            } else {
                int64 answer = 1;
                for (int i = 2; i <= d; ++i) answer *= i;
                printf("%lld\n", answer);
            }
        }
    }
};

int main() {
    Prepare();
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
