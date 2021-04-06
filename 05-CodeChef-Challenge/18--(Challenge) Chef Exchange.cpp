#include<bits/stdc++.h>
using namespace std;

//#define LIHAO

typedef long long ll;

#define N 110
#define M 100010

int dp[M*2], prv[M*2], nxt[M*2], lft[M*2], rht[M*2], who[M*2], r[N], qu[M*2];
int haha, n, m, Q, R[N], W[N][N];
ll B[N];
double S, P;
int wahaha;

void init()
{
    memset(B, 0, sizeof B);
    memset(W, 0, sizeof W);
    memset(prv, -1, sizeof prv);
    for(int i = 0; i < 2*M; i ++) dp[i] = 2*M;
    for(int i = 1; i <= n; i ++) W[i][1] = 1e9;
    for(int i = 1; i <= m; i ++) R[i] = 1;
    S = P = 0;
    if(m == 1) haha = 1, wahaha = 5;
    else if(m == 20) haha = 2, wahaha = 5;
    else if(n == 20) haha = 3, wahaha = 15;
    else haha = 4, wahaha = 15;

}

int hihi, qa, qb, qk;

void in()
{
    scanf("%d", &hihi);
    if(hihi == 0)
    {
        scanf("%d%d%d", &qa, &qb, &qk);
B[qa] -= qk, B[qb] += qk;
    }
    else
    {
        scanf("%d%d", &qa, &qk);
        R[qa] = qk;
    }
    if(haha == 4 && qk > 100) haha = 5, wahaha = 15;
}

struct hao
{
    int type, a, b, c, k;
    hao(int type=0,int a=0,int b=0,int c=0,int k=0):type(type),a(a),b(b),c(c),k(k) {}
    void print()
    {
        if(type == 0)
        {
            assert(W[a][c] >= k);
            W[a][c] -= k, W[b][c] += k;
            B[a] += 1ll * k * R[c], B[b] -= 1ll * k * R[c];
            S += k;
        }
        if(type == 1)
        {
            assert(c > 1);
            assert(W[a][1] >= 1ll * k * R[c]);
            W[a][1] -= k * R[c];
            W[a][c] += k;
        }
#ifndef LIHAO
        if(type == 0)
        {
            printf("SEND %d %d %d %d\n", a, b, c, k);
            fflush(stdout);
        }
        else
        {
            printf("XCHG %d %d %d\n", a, c, k);
fflush(stdout);
        }
#endif
    }
};

void out(vector <hao> &v)
{
#ifndef LIHAO
    printf("%d\n", v.size());
    fflush(stdout);
#endif
    for(int i = 0; i < v.size(); i ++) v[i].print();
}

bool cmpR(int i, int j)
{
    return R[i] < R[j];
}

int val(int i, int sgn)
{
    return wahaha * dp[i] + i * sgn;
}

int pn, nn, po[M], ne[M];
void process_init()
{
    memset(prv, -1, sizeof prv);
    for(int i = 0; i < 2*M; i ++) dp[i] = 2*M;
    for(int i = 1; i <= m; i ++) r[i] = i;
    sort(r + 1, r + m + 1, cmpR);
    for(int i = 1; i <= m; i ++) if(R[r[i]] > 1)
        {
            int x = R[r[i]] + M;
            for(int j = i; j <= m; j ++)
            {
                int y = x + R[r[j]];
                if(y >= 2 * M) break;
                dp[y] = 2, prv[y] = x, who[y] = r[j];
            }
for(int j = i; j <= m; j ++)
            {
                int y = x - R[r[j]];
                if(y < 0) break;
                dp[y] = 2, prv[y] = x, who[y] = -r[j];
            }
            x = -R[r[i]] + M;
            for(int j = i; j <= m; j ++)
            {
                int y = x + R[r[j]];
                if(y >= 2 * M) break;
                dp[y] = 2, prv[y] = x, who[y] = r[j];
            }
            for(int j = i; j <= m; j ++)
            {
                int y = x - R[r[j]];
                if(y < 0) break;
                dp[y] = 2, prv[y] = x, who[y] = -r[j];
            }
        }
    for(int i = 1; i <= m; i ++) if(R[i] > 1)
        {
            dp[R[i]+M] = 1, prv[R[i]+M] = M, who[R[i]+M] = i;
            dp[-R[i]+M] = 1, prv[-R[i]+M] = M, who[-R[i]+M] = -i;
        }
    dp[M] = 0, prv[M] = M;
    pn = nn = 0;
    for(int i = M; i < 2 * M; i ++) if(prv[i] != -1) po[pn ++] = i-M;
    for(int i = M-1; i >= 0; i --) if(prv[i] != -1) ne[nn ++] = M-i;
    lft[0] = 0;
    for(int i = 0, mn = 1e9, pos = 0; i < 2*M; i ++)
    {
        if(prv[i] != -1 && val(i, -1) < mn)
        {
            mn = val(i, -1);
            pos = i;
        }
        lft[i] = pos;
    }
    for(int i = 2*M-1, mn = 1e9, pos = 2*M-1; i >= 0; i --)
    {
        if(prv[i] != -1 && val(i, 1) < mn)
        {
            mn = val(i, 1);
            pos = i;
        }
        nxt[i] = lft[i];
        if(pos != -1 && val(pos, 1) - i < val(lft[i], -1) + i) nxt[i] = pos;
    }
}

void process(vector <hao> &v, hao d)
{
    assert(d.type == 0);
    int ge = R[d.c] * d.k + M;
    if(ge >= 2 * M || prv[ge] == -1)
    {
        v.push_back(d);
        return;
    }
    while(ge != M)
    {
        if(abs(who[ge]) != 1)
        {
            if(who[ge] > 0) v.push_back(hao(1, d.a, 0, who[ge], 1));
            else v.push_back(hao(1, d.b, 0, -who[ge], 1));
        }
        if(who[ge] > 0) v.push_back(hao(0, d.a, d.b, who[ge], 1));
        else v.push_back(hao(0, d.b, d.a, -who[ge], 1));
        ge = prv[ge];
    }
}

int x[N], y[N];
ll b[N];

void last_oper()
{
    for(int i = 1; i <= m; i ++) r[i] = i;
    sort(r + 1, r + m + 1, cmpR);
    memset(prv, -1, sizeof prv);
    for(int i = 0; i < 2*M; i ++) dp[i] = 2*M;
dp[M] = 0, prv[M] = M;
    int st = 0, ed = 1;
    qu[0] = M;
    while(st < ed)
    {
        int x = qu[st ++];
        for(int i = 1; i <= m; i ++)
        {
            int y = x - R[r[i]];
            if(y < 0) break;
            if(prv[y] == -1)
            {
                dp[y] = dp[x] + 1, prv[y] = x;
                who[y] = -r[i];
                qu[ed ++] = y;
            }
        }
        for(int i = 1; i <= m; i ++)
        {
            int y = x + R[r[i]];
            if(y > 2*M) break;
            if(prv[y] == -1)
            {
                dp[y] = dp[x] + 1, prv[y] = x;
                who[y] = r[i];
                qu[ed ++] = y;
            }
        }
    }
    vector <hao> ans;
    for(int i = 1; i <= n; i ++) b[i] = B[i];
    while(1)
    {
        int x = min_element(b + 1, b + n + 1) - b;
        int y = max_element(b + 1, b + n + 1) - b;
        int Bx = b[x], By = b[y];
        if(Bx == 0) break;
        int ge = min(-Bx, By), c = 1;
        process(ans, hao(0, x, y, 1, ge));
        b[x] += ge, b[y] -= ge;
    }
out(ans);
}

void gao()
{
    if(Q == 0)
    {
        last_oper();
        return;
    }
    if(hihi == 1)
    {
        process_init();
    }
    vector <hao> ans;
    for(int i = 1; i <= n; i ++) b[i] = B[i];
    while(1)
    {
        int x = min_element(b + 1, b + n + 1) - b;
        int y = max_element(b + 1, b + n + 1) - b;
        int Bx = b[x], By = b[y];
        if(Bx == 0) break;
        int ge = min(-Bx, By);
        if(ge < M)
        {
            int dist = 1e9, mid = ge;
            for(int i = 0; i < pn; i ++)
            {
                int h = ge-po[i]+M;
                int cur = wahaha * dp[nxt[h]] + abs(h-nxt[h]) + wahaha * dp[po[i]+M];
                if(cur < dist)
                {
                    dist = cur;
                    mid = ge-po[i];
                }
            }
            for(int i = 0; i < nn; i ++)
            {
                if(ge + ne[i] >= M) break;
                int h = ge+ne[i]+M;
int cur = wahaha * dp[nxt[h]] + abs(h-nxt[h]) + wahaha * dp[M-ne[i]];
                if(cur < dist)
                {
                    dist = cur;
                    mid = ge+ne[i];
                }
            }
            if(dist < 50000 && 0 != nxt[M+mid]-M)
            {
                process(ans, hao(0, x, y, 1, ge-mid));
                process(ans, hao(0, x, y, 1, nxt[M+mid]-M));
                b[x] += ge-mid+nxt[M+mid]-M, b[y] -= ge-mid+nxt[M+mid]-M;
                continue;
            }
        }
        int mn = 1e9, c = 1;
        for(int i = 2; i <= m; i ++) if(R[i] <= ge)
            {
                int p = ge % R[i], q = ge / R[i];
                int cur = wahaha * dp[nxt[p+M]] + abs(p-nxt[p+M]+M) + q;
                if(cur == mn && R[i] > R[c]) c = i;
                if(cur < mn) mn = cur, c = i;
            }
        if(R[c] <= 1) break;
        int cnt = ge / R[c];
        ans.push_back(hao(1, x, 0, c, cnt));
        ans.push_back(hao(0, x, y, c, cnt));
        b[x] += R[c] * cnt;
        b[y] -= R[c] * cnt;
    }
    out(ans);
}

int main()
{
#ifdef LIHAO
    freopen("0.in", "r", stdin);
//    freopen("1.out", "w", stdout);
    double tot_score = 0;
    int T = 0;
#endif
    while(~scanf("%d%d%d", &n, &m, &Q))
    {
        init();
        while(Q --)
        {
            in();
            gao();
            int x;
            scanf("%d", &x);
            for(int i = 1; i <= n; i ++) P += abs(B[i]);
        }
        for(int i = 1; i <= n; i ++) assert(B[i] == 0);
#ifdef LIHAO
        T ++;
        double score = S + P * 0.001;
        printf("\n%2dth score is     %lf \n", T, score);
        printf("                  %lf\n", S);
        printf("                  %lf\n", P);
        tot_score += score;
#else
        return 0;
#endif
    }
#ifdef LIHAO
    printf("\n\ntotal score is     %lf\n", tot_score / T * 4);
#endif
}
