#include <algorithm>
#include <iostream>
#include <cstdio>
#include <vector>

using namespace std;

const int MAXN = 5005;
const int MAXK = 33;
const int MOD = 1000000007;

struct Vertex {
    int tin, fup;
    int cycle_id;
    int dp[MAXK];
};

struct Edge {
    int u, v;

    bool is_bridge;

    Edge(int u = -1, int v = -1) : u(u), v(v), is_bridge(false) {}

    int get_xor() {
        return u ^ v;
    }
};

struct Cycle {
    vector<int> vertices;

    int dp[MAXK];

    void rotate(int v) {
        auto element = find(vertices.begin(), vertices.end(), v);
        ::rotate(vertices.begin(), element, vertices.end() );
    }
};

struct Graph {
    int n;

    Vertex vertices[MAXN];
    vector<int> graph[MAXN];

    vector<Cycle> cycles;
    vector<Edge> edges;

    int dp_buffer[MAXK];
    int dp_buffer2[MAXK];

    void clear() {
        cycles.clear();
        edges.clear();

        for (int v = 0; v < n; v++) {
            graph[v].clear();
        } 
    }

    void add_edge(int u, int v) {
        graph[u].push_back(edges.size() );
        graph[v].push_back(edges.size() );

        edges.push_back(Edge(u, v) );
    }

    void compress_cycles_dfs(int v, int prev, int &timer) {
        vertices[v].tin = vertices[v].fup = ++timer;

        for (int edge_id : graph[v] ) {
            int u = v ^ edges[edge_id].get_xor();

            if (u == prev) {
                continue;
            }

            if (vertices[u].tin != -1) {
                vertices[v].fup = min(vertices[v].fup, vertices[u].tin);
                continue;
            }

            compress_cycles_dfs(u, v, timer);
            vertices[v].fup = min(vertices[v].fup, vertices[u].fup);

            if (vertices[v].tin < vertices[u].fup) {
                edges[edge_id].is_bridge = true;
            }
        }
    }

    void add_cycle_dfs(int v, int prev) {
        cycles.back().vertices.push_back(v);
        vertices[v].cycle_id = cycles.size() - 1;
        for (int edge_id : graph[v] ) {
            int u = v ^ edges[edge_id].get_xor();

            if (vertices[u].cycle_id > -1 || edges[edge_id].is_bridge) {
                continue;
            }

            add_cycle_dfs(u, v);
        }
    }

    void compress_cycles() {
        int timer = 0;
        for (int i = 0; i < n; i++) {
            vertices[i].tin = vertices[i].fup = -1;
            vertices[i].cycle_id = -1;
        }

        compress_cycles_dfs(0, -1, timer);

        for (int v = 0; v < n; v++) {
            if (vertices[v].cycle_id > -1) {
                continue;
            }

            cycles.push_back(Cycle() );
            add_cycle_dfs(v, -1);
        }
    }

    void fill(int* begin, int* end, int value) {
        while (begin != end) {
            *begin = value;
            begin += 1;
        }
    }

    void copy(int* begin1, int* end1, int* begin2, int* end2) {
        while (begin1 != end1) {
            *begin1 = *begin2;

            begin1 += 1;
            begin2 += 1;
        }
    }

    void plus(int* begin1, int* end1, int* begin2, int* end2) {
        while (begin1 != end1) {
            *begin1 += *begin2;

            if (*begin1 >= MOD) {
                *begin1 -= MOD;
            }

            begin1 += 1;
            begin2 += 1;
        }
    }

    int multiply(int a, int b) {
        return (int)( (a * 1ll * b) % MOD);
    }

    int next(int index, int size) {
        return (index + 1) % size;
    }

    void compute_dp_dfs(int cycle_id, int root, int prev, int k, int answer[] ) {
        Cycle& cycle = cycles[cycle_id];
        cycle.rotate(root);

        for (int v : cycle.vertices) {
            fill(vertices[v].dp, vertices[v].dp + k + 1, 0);

            vertices[v].dp[1] = 1;
            for (int edge_id : graph[v] ) {
                int u = v ^ edges[edge_id].get_xor();
                if (u == prev || !edges[edge_id].is_bridge) {
                    continue;
                }

                compute_dp_dfs(vertices[u].cycle_id, u, v, k, answer);
                fill(dp_buffer, dp_buffer + k + 1, 0);
                for (int i = 0; i <= k; i++) {
                    for (int j = 0; i + j <= k; j++) {
                        dp_buffer[i + j] += multiply(
                            vertices[v].dp[i], 
                            cycles[vertices[u].cycle_id].dp[j]
                        );

                        if (dp_buffer[i + j] >= MOD) {
                            dp_buffer[i + j] -= MOD;
                        }
                    }
                }
                copy( 
                    vertices[v].dp, 
                    vertices[v].dp + k + 1,
                    dp_buffer, 
                    dp_buffer + k + 1
                );
            }
        }
        
        fill(cycle.dp, cycle.dp + k + 1, 0);
        cycle.dp[0] = 1;

        for (int start = 0; start < cycle.vertices.size(); start++) {
            int v = cycle.vertices[start];
            int current = next(start, cycle.vertices.size() );

            copy(
                dp_buffer,
                dp_buffer + k + 1,
                vertices[v].dp,
                vertices[v].dp + k + 1
            );

            plus(answer, answer + k + 1, dp_buffer, dp_buffer + k + 1);
            if (!start) {
                plus(cycle.dp, cycle.dp + k + 1, dp_buffer, dp_buffer + k + 1);
            }

            while (true) {
                if (start && next(current, cycle.vertices.size() ) == start) {
                    break;
                }
                if (!start && !current) {
                    break;
                }

                int u = cycle.vertices[current];
                fill(dp_buffer2, dp_buffer2 + k + 1, 0);
                for (int i = 0; i <= k; i++) {
                    for (int j = 0; i + j <= k; j++) {
                        dp_buffer2[i + j] += multiply(
                            vertices[u].dp[i], 
                            dp_buffer[j]
                        );

                        if (dp_buffer2[i + j] >= MOD) {
                            dp_buffer2[i + j] -= MOD;
                        }
                    }
                }
                copy(
                    dp_buffer, 
                    dp_buffer + k + 1,
                    dp_buffer2, 
                    dp_buffer2 + k + 1
                );

                plus(answer, answer + k + 1, dp_buffer, dp_buffer + k + 1);

                if (!start || current < start) {
                    plus(cycle.dp, cycle.dp + k + 1, dp_buffer, dp_buffer + k + 1);
                }

                current = next(current, cycle.vertices.size() );
            }
        }
    }

    int compute_dp(int k) {
        int answer[MAXK];
        fill(answer, answer + k + 1, 0);

        compute_dp_dfs(0, 0, -1, k, answer);

        int result = 0;
        for (int i = 0; i <= k; i++) {
            (result += answer[i] ) %= MOD;
        }

        return result;
    }
};

int n, m, k;
Graph graph;

void solve_one_case() {
    scanf("%d%d%d", &n, &m, &k);
    graph.n = n;
    graph.clear();

    for (int i = 0; i < m; i++) {
        int u, v; scanf("%d%d", &u, &v);
        u -= 1;
        v -= 1;

        graph.add_edge(u, v);
    }

    graph.compress_cycles();
    int answer = graph.compute_dp(k);

    printf("%d\n", answer);
}

int main() {
    int cases; scanf("%d", &cases);
    for (int i = 0; i < cases; i++) {
        solve_one_case();
    }
}