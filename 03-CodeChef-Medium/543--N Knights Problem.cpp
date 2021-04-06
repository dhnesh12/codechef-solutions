#include <cstdio>
#include <limits>
#include <queue>
#include <string>
#include <vector>
using namespace std;

typedef int UType;

struct Edge {
    int Target;
    UType U;
};

struct Graph {
    vector<Edge> Edges;
    vector<vector<int> > Out;
    int Source, Target;
    vector<int> H, Begin;

    void AddEdge(int s, int t, UType u) {
        Edge e1 = {t, u}, e2 = {s, 0};
        Edges.push_back(e1);
        Edges.push_back(e2);
        Out[s].push_back(Edges.size() - 2);
        Out[t].push_back(Edges.size() - 1);
    }

    UType Augment(int no, UType flow) {
        if (no == Target) return flow;
        UType left = flow;
        for (int i = Begin[no]; i < Out[no].size(); ++i) {
            int ei = Out[no][i], target = Edges[ei].Target;
            if (Edges[ei].U == 0 || H[target] + 1 != H[no]) continue;
            UType delta = Augment(target, min(left, Edges[ei].U));
            Edges[ei].U -= delta;
            Edges[ei ^ 1].U += delta;
            left -= delta;
            if (left == 0) return flow;
            Begin[no] = i + 1;
        }
        return flow - left;
    }

    bool Relabel() {
        for (int i = 0; i < H.size(); ++i) H[i] = Out.size();
        queue<int> q;
        H[Target] = 0;
        q.push(Target);
        while (!q.empty()) {
            int front = q.front();
            q.pop();
            for (int i = 0; i < Out[front].size(); ++i) {
                int ei = Out[front][i], target = Edges[ei].Target;
                if (Edges[ei ^ 1].U == 0 || H[target] != Out.size()) continue;
                H[target] = H[front] + 1;
                q.push(target);
            }
        }
        for (int i = 0; i < Begin.size(); ++i) Begin[i] = 0;
        return H[Source] < Out.size();
    }

    UType MaxFlow() {
        H.resize(Out.size());
        Begin.resize(Out.size());
        UType flow = 0;
        while (Relabel()) {
            flow += Augment(Source, numeric_limits<UType>::max());
        }
        return flow;
    }
};

const int DX[8] = {+2, +1, -1, -2, -2, -1, +1, +2};
const int DY[8] = {+1, +2, +2, +1, -1, -2, -2, -1};

char Buffer[31];

struct Solution {
    int M, N;
    vector<string> S;
    Graph G;

    bool Black(int x, int y) { return (x + y) % 2 == 0; }

    void Solve() {
        scanf("%d%d", &M, &N);
        S.resize(M);
        for (int i = 0; i < M; ++i) {
            scanf("%s", Buffer);
            S[i] = Buffer;
        }
        G.Out.resize(N * M + 2);
        G.Source = N * M;
        G.Target = N * M + 1;
        int count = 0;
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (S[i][j] == '#') continue;
                ++count;
                int source = i * N + j;
                if (Black(i, j)) {
                    G.AddEdge(G.Source, source, 1);
                } else {
                    G.AddEdge(source, G.Target, 1);
                }
                for (int k = 0; k < 8; ++k) {
                    int iT = i + DX[k];
                    int jT = j + DY[k];
                    if (iT < 0 || M <= iT) continue;
                    if (jT < 0 || N <= jT) continue;
                    if (S[iT][jT] == '#') continue;
                    int target = iT * N + jT;
                    if (Black(i, j)) {
                        G.AddEdge(source, target, 1);
                    } else {
                        G.AddEdge(target, source, 1);
                    }
                }
            }
        }
        printf("%d\n", count - G.MaxFlow());
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}