#include <bits/stdc++.h>
#define ls(x) (x << 1)
#define rs(x) (ls(x) | 1)
using namespace std;

struct edge
{
    int s, t, c, n;
} e[1000000];
int n, a[10010], b[10010], c[10010], d[10010];
int t1[40010], t2[40010];
int S, T, cnt, tot = 1, h[100000], tim, vis[100000], lab[100000], tra[100000], maxflow;

void addedge(int s, int t, int c)
{
    e[++tot] = (edge){s, t, c, h[s]}, h[s] = tot;
    e[++tot] = (edge){t, s, 0, h[t]}, h[t] = tot;
}

int BFS()
{
    queue<int> Q;
    int x, y, i;
    for (int i = 1; i <= cnt; i++)
        tra[i] = h[i];
    Q.push(T), vis[T] = ++tim, lab[T] = 0;
    while (!Q.empty())
        for (i = h[x = Q.front()], Q.pop(); y = e[i].t, i; i = e[i].n)
            if ((e[i ^ 1].c) && (vis[y] != tim))
            {
                vis[y] = tim, lab[y] = lab[x] + 1, Q.push(y);
                if (y == S)
                    return 1;
            }
    return 0;
}

int DFS(int x, int a)
{
    int flow = 0, t, y;
    if (x == T)
        return a;
    for (int &i = tra[x]; y = e[i].t, i; i = e[i].n)
        if ((e[i].c) && (vis[y] == tim) && (lab[y] + 1 == lab[x]))
            if ((t = DFS(y, min(a, e[i].c))))
                if (e[i].c -= t, e[i ^ 1].c += t, flow += t, (a -= t) == 0)
                    return flow;
    return flow;
}

void build(int *t, int base, int x, int l, int r)
{
    if (l == r)
        t[x] = base + l;
    else
    {
        int mid = (l + r) >> 1;
        t[x] = ++cnt;
        build(t, base, ls(x), l, mid);
        build(t, base, rs(x), mid + 1, r);
        addedge(t[x], t[ls(x)], n), addedge(t[x], t[rs(x)], n);
    }
}

void addedge(int *t, int *h, int s, int x, int l, int r, int L, int R, int H)
{
    if ((L <= l) && (r <= R))
    {
        if (min(h[l], h[r]) >= H)
            addedge(s, t[x], 1);
        else if (max(h[l], h[r]) >= H)
        {
            int mid = (l + r) >> 1;
            addedge(t, h, s, ls(x), l, mid, L, R, H);
            addedge(t, h, s, rs(x), mid + 1, r, L, R, H);
        }
    }
    else
    {
        int mid = (l + r) >> 1;
        if (L <= mid)
            addedge(t, h, s, ls(x), l, mid, L, R, H);
        if (mid < R)
            addedge(t, h, s, rs(x), mid + 1, r, L, R, H);
    }
}

void work()
{
    scanf("%d", &n), S = 4 * n + 1, T = 4 * n + 2, cnt = 4 * n + 2;
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), addedge(S, i, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &b[i]), addedge(S, i + n, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &d[i]), addedge(i + 2 * n, T, 1);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]), addedge(i + 3 * n, T, 1);
    build(t1, 2 * n, 1, 1, n);
    build(t2, 3 * n, 1, 1, n);
    for (int i = 1; i <= n; i++)
    {
        if (a[i])
        {
            addedge(t1, c, i, 1, 1, n, 1, a[i], i);
            addedge(t2, d, i, 1, 1, n, 1, a[i], n - i + 1);
        }
        if (b[i])
        {
            addedge(t1, c, i + n, 1, 1, n, n - b[i] + 1, n, i);
            addedge(t2, d, i + n, 1, 1, n, n - b[i] + 1, n, n - i + 1);
        }
    }
    while (BFS())
        maxflow += DFS(S, 2 * n);
    printf("%d", maxflow);
}

void clear()
{
    tot = 1, maxflow = 0;
    for (int i = 1; i <= cnt; i++)
        h[i] = 0;
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
        work(), clear(), puts("");
    return 0;
}