#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int Maxn = 100005;
const int Maxm = 19;
const int Maxd = 3;

struct pos {
    ll ways[Maxd][2][2];
    bool black;
    pos() {
        fill((ll*)ways, (ll*)ways + Maxd * 2 * 2, 0ll);
        black = false;
    }
    pos operator+(const pos &B) const {
        pos C;
        for (int i = 0; i < Maxd; i++)
            for (int j = 0; i + j + 1 < Maxd; j++)
                for (int b1 = 0; b1 < 2; b1++)
                    for (int b2 = 0; b2 < 2; b2++) if (b1 || b2)
                        for (int a = 0; a < 2; a++)
                            for (int c = 0; c < 2; c++)
                                C.ways[i + j + 1][a][c] += ways[i][a][b1] * B.ways[j][b2][c];
        for (int i = 0; i < Maxd; i++)
            for (int a = 0; a < 2; a++)
                for (int b = 0; b < 2; b++) {
                    C.ways[i][a][b | B.black] += ways[i][a][b];
                    C.ways[i][a | black][b] += B.ways[i][a][b];
                }
        C.black = black || B.black;
        return C;
    }
};

int T;
int n;
int a[Maxn];
vector <int> neigh[Maxn];
pos me[Maxn][Maxm];
int L[Maxn], P[Maxn][Maxm];

void Traverse(int v)
{
    for (int i = 0; i < neigh[v].size(); i++) {
        int u = neigh[v][i];
        if (u == P[v][0]) continue;
        P[u][0] = v; L[u] = L[v] + 1;
        Traverse(u);
    }
}

ll getFinal(pos &A, pos &B)
{
    for (int i = 0; i < Maxd; i++)
        swap(B.ways[i][0][1], B.ways[i][1][0]);
    A = (A + B);
    ll res = 0;
    for (int a = 0; a < 2; a++)
        for (int b = 0; b < 2; b++)
            res += A.ways[Maxd - 1][a][b];
    return res;
}

ll Solve(int a, int b)
{
    if (L[a] < L[b]) swap(a, b);
    pos A, B;
    for (int i = Maxm - 1; i >= 0; i--)
        if (L[a] - (1 << i) >= L[b]) {
            A = (A + me[a][i]);
            a = P[a][i];
        }
    if (a == b) {
        A = (A + me[a][0]);
        return getFinal(A, B);
    }
    for (int i = Maxm - 1; i >= 0; i--)
        if (P[a][i] != P[b][i]) {
            A = (A + me[a][i]);
            B = (B + me[b][i]);
            a = P[a][i]; b = P[b][i];
        }
    A = (A + me[a][1]);
    B = (B + me[b][0]);
    return getFinal(A, B);
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", &a[i]);
            neigh[i].clear();
            me[i][0] = pos();
            me[i][0].ways[0][a[i]][a[i]] = 1;
            me[i][0].black = a[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int x, y; scanf("%d %d", &x, &y);
            neigh[x].push_back(y);
            neigh[y].push_back(x);
        }
        Traverse(1);
        for (int j = 1; j < Maxm; j++)
            for (int i = 1; i <= n; i++) {
                int par = P[i][j - 1];
                P[i][j] = P[par][j - 1];
                me[i][j] = (me[i][j - 1] + me[par][j - 1]);
            }
        int q; scanf("%d", &q);
        while (q--) {
            int l, r; scanf("%d %d", &l, &r);
            printf("%lld\n", Solve(l, r));
        }
    }
    return 0;
}
