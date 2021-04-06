#include <cstdio>
#include <vector>
using namespace std;

const int M = 50;
vector<double> F, D;

void Prepare() {
    F.push_back(1);
    F.push_back(1);
    D.push_back(1);
    D.push_back(0);
    for (int i = 2; i <= M; ++i) {
        F.push_back(F[i - 1] * i);
        D.push_back((D[i - 1] + D[i - 2]) * (i - 1));
    }
}

struct Solution {
    int N, R;

    void Solve() {
        scanf("%d%d", &N, &R);
        double answer = 0.0;
        for (int i = 2; i <= N; ++i) {
            if (R % i == 0) answer += F[N - 1] / F[N - i] * D[N - i];
        }
        printf("%.5lf\n", answer / D[N] * N);
    }
};

int main() {
    Prepare();
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}