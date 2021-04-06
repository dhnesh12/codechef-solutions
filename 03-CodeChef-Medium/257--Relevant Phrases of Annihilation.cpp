#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int N = 100500;
const int M = 10010;
const int INF = 0x3f3f3f3f;

int wa[N], wb[N], wv[N], wss[N];
int rak[N], height[N], cal[N], sa[N];
int n, T, len, belong[N];
int f[12], imin[12], imax[12];

bool cmp(int *r, int a, int b, int l)
{
    return r[a] == r[b] && r[a + l] == r[b + l];
}

void da(int *r, int *sa, int n, int m)
{
    int i, j, p, *x = wa, *y = wb;
    for (i = 0; i < m; i++) wss[i] = 0;
    for (i = 0; i < n; i++) wss[x[i] = r[i]]++;
    for (i = 1; i < m; i++) wss[i] += wss[i - 1];
    for (i = n - 1; i >= 0; i--) sa[--wss[x[i]]] = i;
    for (j = 1, p = 1; p < n; j *= 2, m = p) {
        for (p = 0, i = n - j; i < n; i++) y[p++] = i;
        for (i = 0; i < n; i++)
            if (sa[i] >= j) y[p++] = sa[i] - j;
        for (i = 0; i < n; i++) wv[i] = x[y[i]];
        for (i = 0; i < m; i++) wss[i] = 0;
        for (i = 0; i < n; i++) wss[wv[i]]++;
        for (i = 1; i < m; i++) wss[i] += wss[i - 1];
        for (i = n - 1; i >= 0; i--) sa[--wss[wv[i]]] = y[i];
        for (swap(x, y), p = 1, x[sa[0]] = 0, i = 1; i < n; i++) {
            if (cmp(y, sa[i - 1], sa[i], j)) x[sa[i]] = p - 1;
            else x[sa[i]] = p++;
        }
    }
}

void calc(int *r, int *sa, int n)
{
    int i, j, k = 0;
    for (i = 1; i <= n; i++) rak[sa[i]] = i;
    for (i = 0; i < n; height[rak[i++]] = k)
        for (k ? k-- : 0, j = sa[rak[i] - 1]; r[i + k] == r[j + k]; k++);
    for (i = n; i; i--) {
        rak[i] = rak[i - 1];
        sa[i]++;
    }
}

bool check(int k)
{
    memset(f, 0, sizeof(f));
    memset(imin, INF, sizeof(imin));
    memset(imax, 0, sizeof(imax));
    int cnt = 0;
    for (int i = 1; i <= len; i++) {
        if (height[i] >= k) {
            if (0 != belong[sa[i]] && 0 == f[belong[sa[i]]]) cnt++;
            f[belong[sa[i]]]++;
            imin[belong[sa[i]]] = min(imin[belong[sa[i]]], sa[i]);
            imax[belong[sa[i]]] = max(imax[belong[sa[i]]], sa[i]);
        }
        else {
            memset(f, 0, sizeof(f));
            memset(imin, INF, sizeof(imin));
            memset(imax, 0, sizeof(imax));
            if (0 != belong[sa[i]]) {
                cnt = 1;
                f[belong[sa[i]]]++;
                imin[belong[sa[i]]] = min(imin[belong[sa[i]]], sa[i]);
                imax[belong[sa[i]]] = max(imax[belong[sa[i]]], sa[i]);
            }
            else cnt = 0;
        }
        if (cnt == n) {
            bool flag = true;
            for (int i = 1; i <= n; i++) {
                if (f[belong[sa[i]]] < 2) flag = false;
                if (imax[i] - imin[i] < k) flag = false;
            }
            if (flag) return true;
        }
    }
    return false;
}

int main()
{
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        len = 0;
        int b = 125;
        for (int i = 1; i <= n; i++) {
            char s[M];
            scanf("%s", s + 1);
            for (int k = 1; k <= strlen(s + 1); k++) {
                cal[++len] = s[k];
                belong[len] = i;
            }
            if (i != n) cal[++len] = ++b;
        }
        cal[len + 1] = 0;
        da(cal + 1, sa, len + 1, 150);
        calc(cal + 1, sa, len);
        int l = 0, r = len;
        while (l < r) {
            int mid = (l + r + 1) / 2;
            if (check(mid)) l = mid;
            else r = mid - 1;
        }
        printf("%d\n", l);
    }
    return 0;
}