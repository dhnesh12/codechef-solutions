#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <unordered_map>
#include <map>
#include <cstring>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 2 * 1e6 + 5;
const int M = 2 * 1e6 + 5;
const int MAX_SZ = 550;

struct Query {
    int l, r, i;
};

vector<Query> queries[ M / MAX_SZ + 1];
pair<int, int> edges[M];

int p[N];
int r[N];
int aux[N];
int aux_rank[N];
vector<int> changed;
int num_comp;
int res[M];

bool operator<(const Query& q1, const Query& q2) {
    return q1.r < q2.r;
}

int find(int x, bool change) {
    if (x == p[x]) {
        return x;
    }
    if (change) {
        return find(p[x], change);
    }
    return p[x] = find(p[x], change);
}

void union_set(int a, int b, bool change) {
    int pa = find(a, change);
    int pb = find(b, change);
    if (pa != pb) {
        if (r[pa] < r[pb]) {
            swap(pa, pb);
        }
        p[pb] = pa;
        num_comp--;
        if (!change) {
            aux[pb] = pa;
        } else {
            changed.push_back(pb);
        }
        if (r[pa] == r[pb]) {
            r[pa]++;
            if (!change) {
                aux_rank[pa]++;
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, q;
        scanf("%d%d%d", &n, &m, &q);
        
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &edges[i].first, &edges[i].second);
        }

        int num_block = m / MAX_SZ;
        for (int i = 0; i <= MAX_SZ; i++) {
            queries[i].clear();
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            scanf("%d%d", &l, &r);
            l--; r--;
            int block_id = l / MAX_SZ;
            queries[block_id].push_back(Query {l, r, i});
        }
        for (int i = 0; i <= num_block; i++) {
            if (queries[i].empty()) {
                continue;
            }
            sort(queries[i].begin(), queries[i].end());
            int next = (i + 1) * MAX_SZ;
            for (int k = 1; k <= n; k++) {
                p[k] = k;
                aux[k] = k;
                r[k] = 0;
                aux_rank[k] = 0;
            }
            num_comp = n;
            int right = next;
            for (auto& q : queries[i]) {
                while (right <= q.r) {
                    auto e = edges[right];
                    union_set(e.first, e.second, false);
                    right++;
                }
                int stop = min(next - 1, q.r);
                changed.clear();
                for (int j = q.l; j <= stop; j++) {
                    auto e = edges[j];
                    union_set(e.first, e.second, true);
                }
                res[q.i] = num_comp;
                for (auto& c: changed) {
                    p[c] = aux[c];
                    r[c] = aux_rank[c];
                    num_comp++;
                }
            }
        }

        for (int i = 0; i < q; i++) {
            printf("%d\n", res[i]);
        }
    }
    return 0;
}