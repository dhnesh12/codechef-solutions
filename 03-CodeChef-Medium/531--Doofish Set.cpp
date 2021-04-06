#include<bits/stdc++.h>
using namespace std;
const int N = 100005, LG = 11;
int n, m, k, cp, C[N], M[N];
vector < int > Adj[N], V[N];
char S[LG][N];
void Solve(int l, int r, int h)
{
    int md = (l + r) >> 1;
    if (l == r)
        return ;
    k = max(k, h);
    for (int i = l; i <= md; i ++)
        for (int j : V[i])
            S[h][j] = 1;
    Solve(l, md, h + 1);
    Solve(md + 1, r, h + 1);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i ++)
    {
        int v, u;
        scanf("%d%d", &v, &u);
        Adj[v].push_back(u);
        Adj[u].push_back(v);
    }
    long long mp = 1LL * n * (n - 1) / 2;
    for (int i = 1; i <= n; i ++)
        if (!C[i])
        {
            cp ++;
            int cnt = 0;
            memset(M, 0, sizeof(M));
            for (int j : Adj[i])
                M[j] = 1;
            for (int j = 1; j <= n; j ++)
                if (!M[j] && C[j])
                    return !printf("-1\n");
            for (int j = 1; j <= n; j ++)
                if (!M[j]) C[j] = cp, cnt ++;
            mp -= 1LL * cnt * (cnt - 1) / 2;
        }
    for (int i = 1; i <= n; i ++)
        for (int j : Adj[i])
            if (C[i] == C[j])
                return !printf("-1\n");
    if (mp != m)
        return !printf("-1\n");
    for (int i = 1; i <= n; i ++)
        V[C[i]].push_back(i);
    Solve(1, cp, 1);
    for (int i = 1; i <= k; i ++)
        for (int j = 1; j <= n; j ++)
            S[i][j] += '0';
    printf("%d\n", k);
    for (int i = 1; i <= k; i ++)
        printf("%s\n", &S[i][1]);
    return 0;
}