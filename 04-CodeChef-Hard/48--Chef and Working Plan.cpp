#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define P 1000000007
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
ll N, M, p, q, F[44], S[44][44], Rv[67], OO[67], QwQ[67], Lim;
ll A[3100010], B[3100010], SA[2][3100010], SB[2][3100010];
double rev[3100010];
void add(ll &x, ll y)
{
    x = (x + y) % P;
}
ll powmod(ll x, ll y = P - 2, ll p = P)
{
    ll ans = 1;
    while(y)
    {
        if(y & 1)
        ans = ans * x % p;
        x = x * x % p;
        y >>= 1;
    }
    return ans;
}
ll getsm(ll x)
{
    x %= P;
    ll ans = 0, tmp = 1;
    for(int j = 0; j <= q; j++)
    {
        tmp = tmp * (x + 1 - j) % P;
        ans = (ans + tmp * Rv[j + 1] % P * QwQ[j]) % P;
    }
    return ans;
}
ll calc(ll x)
{
    x %= P;
    ll ans = 0;
    for(int i = p; i <= p; i++)
    {
        ll tmp = 1;
        for(int j = 0; j <= i; j++)
        {
            tmp = tmp * (x + 1 - j) % P;
            ans = (ans + S[i][j] * tmp % P * Rv[j + 1] % P * 1) % P;
        }
    }
    return ans - 1 - (p == 0);
}
signed main()
{
    scanf("%lld%lld%lld%lld", &N, &M, &p, &q), Lim = sqrt(N);
    for(int i = 1; i <= 3000000; i++)
    rev[i] = 1. / i;
    for(int i = 1; i <= 50; i++) OO[i] = (powmod(i + 1, M) + powmod(i - 1, M) - 2 * powmod(i, M)) % P;
    for(int i = q + p; i >= p; i--)
    scanf("%lld", &F[i]);
    q += p;
    for(int i = 1; i <= 55; i++)
    Rv[i] = powmod(i);
    for(int i = 0; i <= q; i++)
    for(int j = 0; j <= i; j++)
    S[i][j] = !i ? !j : (S[i - 1][j - 1] + S[i - 1][j] * j) % P;
    for(int j = 0; j <= q; j++)
    for(int i = j; i <= q; i++)
    add(QwQ[j], F[i] * S[i][j]);
    for(int i = 1; i <= Lim; i++)
    A[i] = calc(N / i) * OO[1] % P, B[i] = calc(i) * OO[1] % P;
    for(int i = 2; i <= Lim; i++)
    if((B[i] - B[i - 1]) % P)
    {
        ll l = B[i - 1], oo = N / i, pm = powmod(i, p);
        int j = 1;
        for(; j * i <= Lim; j++) add(A[j], -(A[i * j] - l) * pm);
        if(!(oo >> 32))
        {
            unsigned o = oo;
            for(int s = min(Lim, N / i / i); j <= s; j++) add(A[j], -(B[(int) (o * rev[j] + 1e-8)] - l) * pm);
        }
        else
        {
            ll o = oo;
            for(int s = min(Lim, N / i / i); j <= s; j++) add(A[j], -(B[(int) (o * rev[j] + 1e-8)] - l) * pm);
        }
        for(int j = Lim / i + 1; j >= i; j--)
        for(int k = min(j * i + i - 1, (int) Lim); k >= j * i; k--)
        add(B[k], -(B[j] - l) * pm);
    }
    memcpy(SA[0], A, sizeof A);
    memcpy(SB[0], B, sizeof B);
    memcpy(SA[1], A, sizeof A);
    memcpy(SB[1], B, sizeof B);
    int a = 0, b = 1;
    for(int i = Lim; i >= 2; i--)
    if((B[i] - B[i - 1]) % P)
    {
        ll *AA = SA[a], *AB = SA[b], *BA = SB[a], *BB = SB[b];
        for(int j = 1; j <= min(N / i / i, Lim); j++)
        AB[j] = AA[j];
        for(int j = Lim; j >= (ll) i * i; j--)
        BB[j] = BA[j];
        ll pm = powmod(i, p);
        for(ll f = i, ff = pm, t = 1, ss = N / i; f <= ss; f *= i, ff = ff * pm % P, t++)
        {
            ll v = OO[t] * ff % P, vv = OO[t + 1] * ff % P * pm % P, oo = N / f, l = BA[i];
            int j = 1;
            for(; j * f <= Lim; j++)
            add(AB[j], (AA[j * f] - l) * v + vv);
            if(!(oo >> 32))
            {
                unsigned o = oo;
                for(int s = min(Lim, N / f / i); j <= s; j++)
                add(AB[j], (BA[(int) (o * rev[j] + 1e-8)] - l) * v + vv);
            }
            else
            {
                ll o = oo;
                for(int s = min(Lim, N / f / i); j <= s; j++)
                add(AB[j], (BA[(int) (o * rev[j] + 1e-8)] - l) * v + vv);
            }
            for(int j = Lim / f + 1; j >= i; j--)
            for(int k = min(j * f + f - 1, Lim); k >= j * f; k--)
            add(BB[k], (BA[j] - l) * v + vv);
        }
        swap(a, b);
    }
    ll ans = 0;
    for(ll i = 1, nx, lst = getsm(0); i <= N; i = nx + 1)
    {
        nx = N / (N / i);
        ll tmp = (i <= Lim ? SA[a][i] : SB[a][N / i]) + 1;
        ll o = getsm(nx);
        add(ans, tmp * (o - lst) % P);
        lst = o;
    }
    printf("%lld\n", (ans % P + P) % P);
    return 0;
}