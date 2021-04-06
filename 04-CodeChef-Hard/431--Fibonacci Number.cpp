#include <bits/stdc++.h>
#include <sys/time.h>

#define int signed

inline int read()
{
    int x = 0, f = 0; char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while ( isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return f ? -x : x;
}

int n, mod, I, sqrt5, p, rt, x1, x2, n1, n2, res;

int64_t getCurrentTime()
{    
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
} 

std::mt19937 rng(getCurrentTime());

inline int power(int a, int b)
{
    int res = 1;
    for (; b; b >>= 1, a = 1ULL * a * a % mod)
        if (b & 1) res = 1ULL * res * a % mod;
    return res;
}

struct complex
{
    int a, b;
    inline complex(int _a = 0, int _b = 0) { a = _a, b = _b; }
    inline friend complex operator * (complex a, complex b)
    {
        return complex((1ULL * a.a * b.a % mod + 1ULL * a.b * b.b % mod * I % mod) % mod,
                       (1ULL * a.a * b.b % mod + 1ULL * a.b * b.a % mod) % mod);
    }
};

inline complex power(complex a, int b)
{
    complex res = complex(1, 0);
    for (; b; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}

inline int solve(int n)
{
    if (!n) return 0;
    if (power(n, mod - 1 >> 1) == mod - 1) return -1;
    int a = rng() % mod;
    while (!a || power(I = (1ULL * a * a % mod - n + mod) % mod, mod - 1 >> 1) == 1) a = rng() % mod;
    return power(complex(a, 1), mod + 1 >> 1).a;
}

inline int solve(int a, int b, int t) // a ^ x = b
{
    if (t) b = 1ULL * b * power(a, mod - 2) % mod;
    a = 1ULL * a * a % mod;
    int m = sqrt(mod) + 1;
    std::unordered_map<int, int> map;
    for (int x = b, i = 0; i < m; ++i)
        map[x] = i, x = 1ULL * x * a % mod;
    int w = power(a, m - 1);
    for (int x = 1, i = 1; i < m; ++i)
    {
        x = 1ULL * x * w % mod;
        if (map.find(x) != map.end())
        {
            int s = i * (m - 1) - map[x];
            return s * 2 + t;
        }
    }
    return -1;
}

int main()
{
    for (int T = read(); T; --T)
    {
        n = read(), mod = read();
        res = mod + 1, sqrt5 = solve(5);
        // sqrt5 = 9;
        // printf("sqrt(5) = %d\n", sqrt5);
        n = 1ULL * n * sqrt5 % mod;
        p = 1ULL * (sqrt5 + 1) * (mod + 1 >> 1) % mod;
        // n is even
        rt = solve((1ULL * n * n + 4) % mod);
        if (rt != -1)
        {
            x1 = 1ULL * (n - rt + mod) * (mod + 1 >> 1) % mod;
            x2 = 1ULL * (n + rt) * (mod + 1 >> 1) % mod;
            // printf("x1 = %d, x2 = %d\n", x1, x2);
            n1 = solve(p, x1, 0);
            if (n1 != -1) res = std::min(res, n1);
            n2 = solve(p, x2, 0);
            if (n2 != -1) res = std::min(res, n2);
        }
        rt = solve((1ULL * n * n - 4 + mod) % mod);
        if (rt != -1)
        {
            x1 = 1ULL * (n - rt + mod) * (mod + 1 >> 1) % mod;
            x2 = 1ULL * (n + rt) * (mod + 1 >> 1) % mod;
            n1 = solve(p, x1, 1);
            if (n1 != -1) res = std::min(res, n1);
            n2 = solve(p, x2, 1);
            if (n2 != -1) res = std::min(res, n2);
        }
        printf("%d\n", res == mod + 1 ? -1 : res);
    }
    return 0;
}