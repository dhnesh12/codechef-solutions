#include <cstdio>
#include <string>
#include <vector>
using namespace std;

char Buffer[51];

struct Solution {
    string S;
    vector<string> Answer;

    void Inverse(int n0, int n1) {
        string inv(S.size(), 0);
        inv[0] = '0' + n0;
        inv[1] = '0' + n1;
        for (int i = 2; i < S.size(); ++i) {
            inv[i] = S[i - 1] ^ inv[i - 2] ^ inv[i - 1];
        }
        char inv0 = S[S.size() - 1] ^ inv[S.size() - 2] ^ inv[S.size() - 1];
        if (inv[0] != inv0) return;
        char inv1 = S[0] ^ inv[S.size() - 1] ^ inv0;
        if (inv[1] != inv1) return;
        Answer.push_back(inv);
    }

    void Solve() {
        scanf("%s", Buffer);
        S = Buffer;
        for (int i0 = 0; i0 < 2; ++i0) {
            for (int i1 = 0; i1 < 2; ++i1) Inverse(i0, i1);
        }
        if (Answer.empty()) {
            printf("No solution\n");
        } else if (2 <= Answer.size()) {
            printf("Multiple solutions\n");
        } else {
            printf("%s\n", Answer[0].c_str());
        }
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}