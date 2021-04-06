// In The Name Of The Queen
#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
using namespace std;
const int N = 1005, MXN = 5005, TF = 2000;
int q, n, m, R[N][N];
char S[MXN], A[N][N];
int main()
{
    scanf("%d", &q);
    for (; q; q --)
    {
        scanf("%d%d%s", &m, &n, &S);
        for (int i = 1; i <= n; i ++)
            scanf("%s", &A[i][1]);
        for (int i = 0; i <= n; i ++)
            A[i][0] = A[i][n + 1] = A[0][i] = A[n + 1][i] = '#';
        int cblock = 0;
        for (int i = 0; i <= n + 1; i ++)
            for (int j = 0; j <= n + 1; j ++)
                if (A[i][j] == '#')
                    cblock ++;
        for (int i = 1; i <= n; i ++)
            for (int j = 1; j <= n; j ++)
                R[i][j] = m;
        if (cblock < TF)
        {
            for (int sx = 0; sx <= n + 1; sx ++)
                for (int sy = 0; sy <= n + 1; sy ++)
                    if (A[sx][sy] == '#')
                    {
                        int nwx = sx, nwy = sy;
                        for (int i = 0; i < m; i ++)
                        {
                            nwy -= (S[i] == 'R') - (S[i] == 'L');
                            nwx -= (S[i] == 'D') - (S[i] == 'U');
                            if (nwx > 0 && nwy > 0 && nwx <= n && nwy <= n)
                                R[nwx][nwy] = min(R[nwx][nwy], i);
                        }
                    }
            int res = 0;
            for (int i = 1; i <= n; i ++)
                for (int j = 1; j <= n; j ++)
                    if (A[i][j] == '.')
                        res ^= R[i][j];
            printf("%d\n", res);
            continue;
        }
        else
        {
            int res = 0;
            for (int sx = 1; sx <= n; sx ++)
                for (int sy = 1; sy <= n; sy ++)
                    if (A[sx][sy] == '.')
                    {
                        int nwx = sx, nwy = sy, f = m;
                        for (int i = 0; i < m; i ++)
                        {
                            nwy += (S[i] == 'R') - (S[i] == 'L');
                            nwx += (S[i] == 'D') - (S[i] == 'U');
                            if (!(nwx > 0 && nwy > 0 && nwx <= n && nwy <= n))
                                {f = i; break;}
                        }
                        res ^= f;
                    }
            printf("%d\n", res);
        }
    }
    return 0;
}