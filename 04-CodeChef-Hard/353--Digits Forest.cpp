#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

#define MAXN 100
#define MAXSTATE 64
#define MOD 420
#define oo 1000000000

struct Vertex
{
    int i, digmsk, mod;
};

bool check(int dig, int mod)
{
    for (int i = 0; i < 6; i++)
    {
        if ((dig & (1 << i)) && (mod % (i + 2)))
            return false;
    }

    return true;
}

int n, c[MAXN], a[MAXN][MAXN], d[MAXN][MAXSTATE][MOD], res;
bool inq[MAXN][MAXSTATE][MOD];
queue<Vertex> q;

int main()
{
    ios::sync_with_stdio(false);

    while (1)
    {
        cin >> n;
        if (!n)
            break;

        for (int i = 0; i < n; i++)
        {
            cin >> c[i];
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cin >> a[i][j];
            }
        }

        Vertex s;
        s.i = 0;
        s.digmsk = 0;
        if (c[0] > 1)
            s.digmsk = 1 << (c[0] - 2);
        s.mod = c[0] % MOD;

        q.push(s);

        memset(d, 127, sizeof(d));

        d[s.i][s.digmsk][s.mod] = c[0];
        inq[s.i][s.digmsk][s.mod] = true;

        res = oo;

        while (!q.empty())
        {
            Vertex u = q.front();
            q.pop();
            inq[u.i][u.digmsk][u.mod] = false;

            for (int i = 0; i < n; i++)
            {
                if (a[u.i][i])
                {
                    Vertex v;
                    v.i = i;
                    v.digmsk = u.digmsk;
                    if (c[i] > 1)
                        v.digmsk |= (1 << (c[i] - 2));
                    v.mod = (u.mod * 10 + c[i]) % MOD;

                    if (d[v.i][v.digmsk][v.mod] > d[u.i][u.digmsk][u.mod] + c[i])
                    {
                        d[v.i][v.digmsk][v.mod] = d[u.i][u.digmsk][u.mod] + c[i];
                        if (!inq[v.i][v.digmsk][v.mod])
                        {
                            q.push(v);
                            inq[v.i][v.digmsk][v.mod] = true;

                            if (v.i == n - 1 && check(v.digmsk, v.mod))
                            {
                                res = min(res, d[v.i][v.digmsk][v.mod]);
                            }
                        }
                    }
                }
            }
        }

        if (res == oo)
            cout << -1 << endl;
        else
            cout << res << endl;
    }

    return 0;
}
