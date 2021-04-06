#include <algorithm>
#include <cstdio>
#include <limits>
#include <vector>
using namespace std;

struct Solution {
    int N, M, C1, C2, Bound1, Bound2, Gap;
    vector<int> C;

    bool Valid(int gap) {
        int current = C[Bound1 - 1], answer = 0;
        for (int i = Bound1; i < Bound2; ++i) {
            if (gap < C[i + 1] - current) {
                current = C[i];
                ++answer;
            }
        }
        return answer <= M;
    }

    int BSearch(int lower, int upper) {
        while (lower < upper) {
            int mid = lower + (upper - lower) / 2;
            if (Valid(mid)) {
                upper = mid;
            } else {
                lower = mid + 1;
            }
        }
        return lower;
    }

    int Greedy() {
        int inf = numeric_limits<int>::max();
        int current = (Bound2++) - (Bound1--);
        int answer = Gap;
        while (current < M) {
            int answer1 = 0 < Bound1 ? C[Bound1] - C[Bound1 - 1] : inf;
            int answer2 = Bound2 < N ? C[Bound2] - C[Bound2 - 1] : inf;
            if (answer1 < answer2) {
                --Bound1;
                if (answer < answer1) answer = answer1;
            } else {
                ++Bound2;
                if (answer < answer2) answer = answer2;
            }
            ++current;
        }
        return answer;
    }

    void Solve() {
        scanf("%d%d%d%d", &N, &M, &C1, &C2);
        if (C2 < C1) swap(C1, C2);
        C.resize(N);
        for (int i = 0; i < N; ++i) scanf("%d", &C[i]);
        C.push_back(C1);
        C.push_back(C2);
        N += 2;
        sort(C.begin(), C.end());
        Bound1 = upper_bound(C.begin(), C.end(), C1) - C.begin();
        Bound2 = lower_bound(C.begin(), C.end(), C2) - C.begin();
        for (int i = Bound1; i <= Bound2; ++i) {
            int gap = C[i] - C[i - 1];
            if (Gap < gap) Gap = gap;
        }
        if (M < Bound2 - Bound1) {
            printf("%d\n", BSearch(Gap, C2 - C1));
        } else {
            printf("%d\n", Greedy());
        }
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
