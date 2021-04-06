#include <memory.h>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <cctype>
#include <cstring>
#include <climits>
#include <cmath>
#include <vector>
#include <string>
#include <memory>
#include <numeric>
#include <limits>
#include <functional>
#include <tuple>
#include <random>
#include <chrono>
#include <set>
#include <map>
#include <bitset>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#ifndef __GNUC__
#include <intrin.h>
#endif
#include <immintrin.h>

using namespace std;

#define PROFILE_START(i)    clock_t start##i = clock()
#define PROFILE_STOP(i)     fprintf(stderr, "elapsed time (" #i ") = %f\n", double(clock() - start##i) / CLOCKS_PER_SEC)

typedef long long           ll;
typedef unsigned long long  ull;

const int MAXN = 100;

const int INF = 0x3f3f3f3f;

/*
    1. Systems of Inequalities (system of difference constraints)

       Path p = (v1, v2, ..., vn)

          x[2] - x[1] <= w[1,2]
          x[3] - x[2] <= w[2,3]
          ...
          x[n] - x[n-1] <= w[n-1,n]

      <=>  
                          n
          x[n] - x[1] <= SUM { w[i-1,i] } = w(p)
                         i=2

      ==> 

          x[n] - x[1] <= (the weight of the shortest path from v1 to vn)
*/
// Constraint Graph
struct DifferenceConstraintsSystem {
    const int INF = 0x7f7f7f7f;

    int N;
    vector<vector<pair<int, int>>> edges;   // edges[u] = { (v, w), ... }

    DifferenceConstraintsSystem() {
    }

    explicit DifferenceConstraintsSystem(int n) {
        init(n);
    }

    void init(int n) {
        N = n;
        edges = vector<vector<pair<int, int>>>(n);
    }

    // v - u <= maxW  (u --> v)
    void add(int u, int v, int maxW) {
        edges[u].emplace_back(v, maxW);
    }

    // minW <= v - u <= maxW  (u --> v)
    void add(int u, int v, int minW, int maxW) {
        edges[u].emplace_back(v, maxW);
        edges[v].emplace_back(u, -minW);
    }

    // return distance{ start -> v0, start -> v1, start -> v0, ... }
    //  - if there is no solution, return {}
    vector<int> bellmanFord(int start) {
        vector<int> dist(N, INF);
        dist[start] = 0;

        for (bool updated = true; updated; ) {
            if (dist[start] != 0)
                return {};  // bad case (negative cycle)

            updated = false;
            for (int u = 0; u < N; u++) {
                for (auto it : edges[u]) {
                    int v = it.first;
                    int w = it.second;
                    if (dist[v] > dist[u] + w) {
                        updated = true;
                        dist[v] = dist[u] + w;
                    }
                }
            }
        }

        return dist;
    }
};

struct ConstraintSolver {
    int N;                                  // the number of variables
    vector<int> curValues;                  // current values of variables
    vector<int> maxValues;                  // max values of variables;
    vector<vector<pair<int, int>>> outEdges;// [u] = { (v, minW), ... }
    vector<vector<pair<int, int>>> inEdges; // [v] = { (u, maxW), ... }
    bool fail;

    ConstraintSolver(int n, const vector<int>& variablesMin, const vector<int>& variablesMax)
        : N(n), curValues(variablesMin), maxValues(variablesMax), outEdges(n), inEdges(n), fail(false) {
    }

    // adds a constraint
    // returns false if this constraint led to a contradiction
    bool add(int u, int v, int minW, int maxW) {
        outEdges[u].push_back(make_pair(v, minW));  // u -> v <= minW
        inEdges[v].push_back(make_pair(u, maxW));   // v -> u <= maxW

        if (curValues[u] + minW > curValues[v]) {
            curValues[v] = curValues[u] + minW;
            if (!fix(v))
                return false;
        }

        if (curValues[v] - maxW > curValues[u]) {
            curValues[u] = curValues[v] - maxW;
            if (!fix(u))
                return false;
        }

        return true;
    }

    // returns the solution to the constraint system
    //         or an empty vector if there is none
    vector<int> solve() {
        if (fail)
            return vector<int>();
        return curValues;
    }

private:
    // gets called no more than 10 times for every variable
    bool fix(int variable) {
        if (curValues[variable] > maxValues[variable]) {
            fail = true;
            return false;
        }

        for (auto& it : outEdges[variable]) {
            int v = it.first;
            int minW = it.second;

            if (curValues[variable] + minW > curValues[v]) {
                curValues[v] = curValues[variable] + minW;
                if (!fix(v))
                    return false;
            }
        }

        for (auto& it : inEdges[variable]) {
            int u = it.first;
            int maxW = it.second;

            if (curValues[variable] - maxW > curValues[u]) {
                curValues[u] = curValues[variable] - maxW;
                if (!fix(u))
                    return false;
            }
        }

        return true;
    }
};

// 

// https://www.codechef.com/problems/DGMATRIX

// http://www.euroinformatica.ro/documentation/programming/!!!Algorithms_CORMEN!!!/DDU0151.html
//  - https://walkccc.me/CLRS/Chap24/24.4/
//  - http://www.facweb.iitkgp.ac.in/~sourav/Lecture-15.pdf
// https://www.codechef.com/viewsolution/40562752

#if 1
// https://www.codechef.com/viewsolution/40192531
vector<vector<int>> solve(const vector<vector<int>>& A, int N) {
    for (int o = 0; o < 10; o++) {
        vector<vector<int>> B(N + 1, vector<int>(N + 1));
        B[0][0] = o;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                B[i + 1][j + 1] = A[i][j] - B[i][j] - B[i][j + 1] - B[i + 1][j];
            }
        }

        /*
            B = | 0       x1       x2       x3   ... xn |
                | y1   -y1-x1   +y1-x2   -y1-x3  ... .  |
                | y2   -y2+x1   +y2+x2   -y2+x3  ... .  |
                | y3   -y3-x1   +y3-x2   -y3-x3  ... .  |
                | ...     .        .        .     .  .  |
                | yn      .        .        .     .  .  |

         ==>

                  0         1                  2
                +----+------------------+------------------
              0 | 0  |      x1          |      x2
                +----+------------------+------------------
              1 | y1 |    -y1 - x1      |    +y1 - x2
                |    | => (-Y) - (+X)   | => (-X) - (-Y)       -
                +----+------------------+------------------
              2 | y2 |    -y2 + x1      |    +y2 + x2
                |    | => (+X) - (+Y)   | => (+Y) - (-X)       +

                             +                  -

         ==>

            variables =
                       +    -    +
                |  x   1    2    3  ... N |
              - | N+1                     |
              + | N+2                     |
              - | N+3                     |
                | ...                     |
                | N+N                     |
        */
        vector<int> varMin(N * 2 + 1, 0);
        vector<int> varMax(N * 2 + 1, 0);
        for (int i = 1; i <= N; i++) {
            if (i & 1) {
                varMin[i] = 0;
                varMax[i] = 9;          // X[i]

                varMin[N + i] = -9;
                varMax[N + i] = 0;      // -Y[i]
            } else {
                varMin[i] = -9;
                varMax[i] = 0;          // -X[i]

                varMin[N + i] = 0;
                varMax[N + i] = 9;      // Y[i]
            }
        }

        ConstraintSolver solver(N * 2 + 1, varMin, varMax);

        // add edges between X[i] and Y[j]
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                int lo = 0 - B[i][j];
                int hi = 9 - B[i][j];
                if ((i & 1) == (j & 1)) {
                    solver.add(j, N + i, lo, hi);   // minW <= Y[i] - X[j] <= maxW
                    //solver.add(N + i, j, -hi, -lo);
                } else {
                    solver.add(N + i, j, lo, hi);   // minW <= X[i] - Y[j] <= maxW
                    //solver.add(j, N + i, -hi, -lo);
                }
            }
        }

        auto values = solver.solve();
        if (!values.empty()) {
            vector<vector<int>> ans(N + 1, vector<int>(N + 1));
            ans[0][0] = o;
            for (int i = 1; i <= N; i++) {
                if (i & 1) {
                    ans[0][i] = values[i];
                    ans[i][0] = -values[N + i];
                } else {
                    ans[0][i] = -values[i];
                    ans[i][0] = values[N + i];
                }
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    ans[i + 1][j + 1] = A[i][j] - ans[i][j] - ans[i][j + 1] - ans[i + 1][j];
                }
            }
            return ans;
        }
    }

    return vector<vector<int>>{};
}
#else
// https://discuss.codechef.com/t/dgmatrix-editorial/82435
vector<vector<int>> solve(const vector<vector<int>>& A, int N) {
    for (int o = 0; o < 10; o++) {
        vector<vector<int>> B(N + 1, vector<int>(N + 1));
        B[0][0] = o;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                B[i + 1][j + 1] = A[i][j] - B[i][j] - B[i][j + 1] - B[i + 1][j];
            }
        }

        /*
            B = | 0       x1       x2       x3   ... xn |
                | y1   -y1-x1   +y1-x2   -y1-x3  ... .  |
                | y2   -y2+x1   +y2+x2   -y2+x3  ... .  |
                | y3   -y3-x1   +y3-x2   -y3-x3  ... .  |
                | ...     .        .        .     .  .  |
                | yn      .        .        .     .  .  |

         ==>

                  0         1                  2
                +----+------------------+------------------
              0 | 0  |      x1          |      x2
                +----+------------------+------------------
              1 | y1 |    -y1 - x1      |    +y1 - x2
                |    | => (-Y) - (+X)   | => (-X) - (-Y)       -
                +----+------------------+------------------
              2 | y2 |    -y2 + x1      |    +y2 + x2
                |    | => (+X) - (+Y)   | => (+Y) - (-X)       +

                             +                  -

         ==>

            variables =
                       +    -    +
                |  x   1    2    3  ... N |
              - | N+1                     |
              + | N+2                     |
              - | N+3                     |
                | ...                     |
                | N+N                     |
        */
        DifferenceConstraintsSystem constraintsGraph(N * 2 + 1);
        // step #1 : add edges from/to O
        for (int i = 1; i <= N; i++) {
            if (i & 1) {
                constraintsGraph.add(0, i, 0, 9);       //   0 <=  X[i] <= 9
                constraintsGraph.add(N + i, 0, 0, 9);   //  -9 <= -Y[i] <= 0
            } else {
                constraintsGraph.add(i, 0, 0, 9);       //  -9 <= -X[i] <= 0
                constraintsGraph.add(0, N + i, 0, 9);   //   0 <=  Y[i] <= 9
            }
        }

        // step #2 : add edges between X[i] and Y[j]
        bool bad = false;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                int minW = 0 - B[i][j];
                int maxW = 9 - B[i][j];
                if (minW > maxW) {
                    bad = true;
                    goto lbBadCase;
                }

                if ((i & 1) == (j & 1)) {
                    constraintsGraph.add(j, N + i, minW, maxW); // minW <= Y[i] - X[j] <= maxW
                } else {
                    constraintsGraph.add(N + i, j, minW, maxW); // minW <= X[i] - Y[j] <= maxW
                }
            }
        }
lbBadCase:

        if (!bad) {
            auto dist = constraintsGraph.bellmanFord(0);
            if (!dist.empty()) {
                vector<vector<int>> ans(N + 1, vector<int>(N + 1));
                ans[0][0] = o;
                for (int i = 1; i <= N; i++) {
                    if (i & 1) {
                        ans[0][i] = dist[i];
                        ans[i][0] = -dist[N + i];
                    } else {
                        ans[0][i] = -dist[i];
                        ans[i][0] = dist[N + i];
                    }
                }
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        ans[i + 1][j + 1] = A[i][j] - ans[i][j] - ans[i][j + 1] - ans[i + 1][j];
                    }
                }
                return ans;
            }
        }
    }

    return vector<vector<int>>{};
}
#endif

int main(void) {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cin >> A[i][j];
    }

    auto B = solve(A, N);

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++)
            cout << B[i][j];
        cout << '\n';
    }

    return 0;
}
