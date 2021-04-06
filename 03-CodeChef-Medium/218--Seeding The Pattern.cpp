#include <cstdio>
#include <vector>
using namespace std;

vector<vector<int> > Multiply(const vector<vector<int> >& m1,
                              const vector<vector<int> >& m2) {
    vector<vector<int> > answer(m1.size());
    for (int i = 0; i < m1.size(); ++i) {
        answer[i].resize(m2[0].size());
        for (int j = 0; j < m1[0].size(); ++j) {
            for (int k = 0; k < m2[0].size(); ++k) {
                answer[i][k] ^= m1[i][j] & m2[j][k];
            }
        }
    }
    return answer;
}

vector<vector<int> > Power(vector<vector<int> > m, int e) {
    vector<vector<int> > answer(m.size());
    for (int i = 0; i < m.size(); ++i) {
        answer[i].resize(m.size());
        answer[i][i] = 1;
    }
    while (e != 0) {
        if (e % 2 != 0) answer = Multiply(answer, m);
        m = Multiply(m, m);
        e /= 2;
    }
    return answer;
}

struct Gauss {
    vector<vector<int> > A;
    vector<int> X;
    bool NoSolution;
    bool MultipleSolutions;

    int PivotIndex(int k) {
        for (int i = 0; i < int(A[k].size()) - 1; ++i) {
            if (A[k][i] != 0) return i;
        }
        return -1;
    }

    void Solve() {
        NoSolution = false;
        MultipleSolutions = false;
        for (int i = 0; i < X.size(); ++i) X[i] = -1;
        for (int i = 0; i < A.size(); ++i) {
            int index = PivotIndex(i);
            if (index == -1) {
                if (A[i].back() == 0) continue;
                NoSolution = true;
                return;
            }
            for (int j = 0; j < A.size(); ++j) {
                if (j == i || !A[j][index]) continue;
                for (int k = 0; k < A[j].size(); ++k) {
                    A[j][k] ^= A[i][k];
                }
            }
            X[index] = i;
        }
        for (int i = 0; i < X.size(); ++i) {
            if (X[i] == -1) {
                MultipleSolutions = true;
                return;
            }
        }
        for (int i = 0; i < X.size(); ++i) X[i] = A[X[i]].back();
    }
};

struct Solution {
    int D, K;
    vector<int> A;
    vector<vector<int> > M;

    void Solve() {
        scanf("%d%d", &D, &K);
        A.resize(D);
        for (int i = 0; i < D; ++i) scanf("%d", &A[i]);
        M.resize(D);
        for (int i = 0; i < D; ++i) {
            M[i].resize(D);
            if (i != D - 1) {
                M[i][i + 1] = 1;
            } else {
                for (int j = 0; j < D; ++j) M[i][j] = A[j];
            }
        }
        Gauss g;
        for (int i = 0; i < K; ++i) {
            int index, x;
            scanf("%d%d", &index, &x);
            g.A.push_back(Power(M, index)[0]);
            g.A.back().push_back(x);
        }
        g.X.resize(D);
        g.Solve();
        if (g.NoSolution) {
            printf("no solution\n");
        } else if (g.MultipleSolutions) {
            printf("multiple solutions\n");
        } else {
            bool head = true;
            for (int i = 0; i < D; ++i) {
                if (!head) printf(" ");
                head = false;
                printf("%d", g.X[i]);
            }
            printf("\n");
        }
    }
};

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 0; i < t; ++i) Solution().Solve();
    return 0;
}
