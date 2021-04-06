#include <cstdio>
#include <vector>
using namespace std;

const int M = 1000;

struct Dish {
    int ByOtherCook, ByChef;
};

struct Solution {
    int N;
    vector<Dish> D;

    bool Valid(int time) {
        vector<bool> v(M + 1);
        v[0] = true;
        int total = 0;
        for (int i = 0; i < N; ++i) {
            if (D[i].ByOtherCook <= time) continue;
            total += D[i].ByChef;
            for (int j = M; j >= D[i].ByChef; --j) {
                if (v[j - D[i].ByChef]) v[j] = true;
            }
        }
        for (int i = time; i >= 0; --i) {
            if (time < total - i) break;
            if (v[i]) return true;
        }
        return false;
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

    void Solve() {
        scanf("%d", &N);
        D.resize(N);
        for (int i = 0; i < N; ++i) {
            scanf("%d%d", &D[i].ByOtherCook, &D[i].ByChef);
        }
        printf("%d\n", BSearch(0, M));
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}