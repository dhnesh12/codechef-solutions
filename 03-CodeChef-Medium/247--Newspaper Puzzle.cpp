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

    int AddEdge(int s, int t, UType u) {
        Edge e1 = {t, u}, e2 = {s, 0};
        Edges.push_back(e1);
        Edges.push_back(e2);
        Out[s].push_back(Edges.size() - 2);
        Out[t].push_back(Edges.size() - 1);
        return Edges.size() - 2;
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

struct Requirement {
    int T, E;
    bool Negative;
};

struct Solution {
    int C, V;
    Graph G;
    vector<Requirement> R;

    void Solve() {
        scanf("%d%d", &C, &V);
        G.Out.resize(C + V + 2);
        G.Source = C + V;
        G.Target = C + V + 1;
        for (int i = 0; i < C; ++i) G.AddEdge(G.Source, i, 1);
        for (int i = 0; i < V; ++i) G.AddEdge(C + i, G.Target, 1);
        for (int i = 0; i < C; ++i) {
            for (int j = 0; j < 3; ++j) {
                Requirement r;
                scanf("%d", &r.T);
                r.Negative = r.T < 0;
                if (r.Negative) r.T = -r.T;
                r.E = G.AddEdge(i, C + (--r.T), 1);
                R.push_back(r);
            }
        }
        G.MaxFlow();
        string answer(V, 'F');
        for (int i = 0; i < R.size(); ++i) {
            if (G.Edges[R[i].E].U == 0) {
                answer[R[i].T] = R[i].Negative ? 'F' : 'T';
            }
        }
        printf("%s\n", answer.c_str());
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
