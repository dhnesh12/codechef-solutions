#include <algorithm>
#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

struct Node {
    int Depth, Current;
};

struct Solution {
    int N, MinP, MaxP;
    vector<int> P;

    void Solve() {
        scanf("%d", &N);
        vector<int> a, b;
        a.resize(N);
        b.resize(N);
        for (int i = 0; i < N; ++i) scanf("%d%d", &a[i], &b[i]);
        int aNeed, bNeed;
        scanf("%d%d", &aNeed, &bNeed);
        P.resize(N);
        for (int i = 0; i < N; ++i) P[i] = b[i] * aNeed - a[i] * bNeed;
        MinP = *min_element(P.begin(), P.end());
        MaxP = *max_element(P.begin(), P.end());
        if (MaxP < 0 || 0 < MinP) {
            printf("-1\n");
        } else {
            vector<bool> visited(MaxP - MinP + 1);
            queue<Node> q;
            Node node = {0, 0};
            q.push(node);
            while (!q.empty()) {
                int depth = q.front().Depth;
                int current = q.front().Current;
                q.pop();
                for (int i = 0; i < N; ++i) {
                    if (current + P[i] == 0) {
                        printf("%d\n", depth + 1);
                        return;
                    }
                    int next = current + P[i];
                    if (MinP <= next && next <= MaxP && !visited[next - MinP]) {
                        visited[next - MinP] = true;
                        Node node = {depth + 1, next};
                        q.push(node);
                    }
                }
            }
        }
    }
};

int main() {
    Solution().Solve();
    return 0;
}