#include <bits/stdc++.h>

using pii = std::pair<int, int>;
#define mkp(a, b) std::make_pair(a, b);

const int N = 1e5 + 10, M = 1e7 + 1;
const int Mod = 1e9 + 7, inv2 = (Mod + 1) / 2, inv6 = (Mod + 1) / 6;

template<typename T = int> inline T read()
{
    T x = 0, f = 0; char ch = getchar();
    while (!isdigit(ch)) f |= ch == '-', ch = getchar();
    while ( isdigit(ch)) x = x * 10 + ch - '0', ch = getchar();
    return f ? -x : x;
}

inline int C2(int n) {return 1LL * n * (n - 1) / 2 % Mod;}
inline int C3(int n) {return 1LL * n * (n - 1) * (n - 2) / 6 % Mod;}
inline int C4(int n) {return 1LL * C2(n) * C2(n - 2) % Mod * inv6 % Mod;}

struct BIT
{
    int f[N];
    #define lowbit(x) ((x) & (-x))

    inline void Add(int x, int dat)
    {
        for (; x < N; x += lowbit(x)) f[x] += dat;
    }

    inline int Ask(int x)
    {
        int res = 0;
        for (; x; x -= lowbit(x)) res += f[x];
        return res;
    }
}T;

int c[N], f[N], pre[N], b[N], A[N], B[N], w[N], s[N], lst[N];
std::vector<int> vec[N]; pii a[M];

int main()
{
    // freopen("arc.in", "r", stdin);
    // freopen("arc.out", "w", stdout);
    int n = read(), S = n / sqrt(n * log2(n)), cnt = 0;
    S = 100;
    for (int i = 1; i <= n; ++i)
        vec[c[i] = read()].push_back(i);
    for (int i = 1; i <= n; ++i) if (vec[i].size() <= S)
        for (auto u: vec[i]) for (auto v: vec[i]) if (u < v) a[++cnt] = mkp(u, v);
    std::sort(a + 1, a + cnt + 1, std::greater<pii>());
    int ans = 0, Ans = 0, All = 0, res = 0, Res = 0;
    for (int i = 1, l = 1; i <= cnt; ++i)
    {
        if (a[i].first != a[i - 1].first)
        {
            for (int j = l; j <= i - 1; ++j)
                T.Add(a[j].second, 1);
            l = i;
        }
        (ans += T.Ask(a[i].second - 1)) %= Mod;
    }
    for (int i = 1; i <= n; ++i)
    {
        pre[i] = pre[i - 1] + f[c[i]]++;
        if (pre[i] >= Mod) pre[i] -= Mod;
    }
    memset(f, 0, sizeof(f)), cnt = 0;
    for (int i = n; i >= 1; --i) (Ans += 1LL * pre[i - 1] * (f[c[i]]++) % Mod) %= Mod;
    for (int i = 1; i <= n; ++i) for (int j = 1; j < vec[i].size(); ++j) lst[vec[i][j]] = vec[i][j - 1];
    for (int i = 1; i <= n; ++i) if (vec[i].size() > S)
    {
        int w = 0;
        for (int l = *vec[i].begin(), r = vec[i].back(); l <= r; ++l)
        {
            (res += 1LL * b[c[l]] * (vec[i].size() - w - (c[l] == i)) % Mod) %= Mod;
            (b[c[l]] += w) %= Mod, w += c[l] == i;
        }
        for (int j = 1; j <= n; ++j) b[j] = 0;
    }
    for (int i = 1; i <= n; ++i)
    {
        (All += C2(vec[i].size())) %= Mod;
        (cnt += C4(vec[i].size())) %= Mod;
    }
    // std::cout << "C(0, 2) = " << C2(0) << std::endl;
    // std::cout << "C(0, 4) = " << C4(0) << std::endl;
    All = C2(All);
    for (int i = 1; i <= n; ++i) 
        (All += Mod - 3LL * C3(vec[i].size()) % Mod) %= Mod;
    for (int i = 1; i <= n; ++i) if (vec[i].size() > S)
    {
        for (int l = 1; l <= n; ++l)
        {
            s[l] = s[l - 1] + (c[l] == i);
            int c = ::c[l], v = s[l] - s[lst[l]];
            (A[c] += (2LL * B[c] * v + 1LL * w[c] * v % Mod * (v - 1) % Mod) % Mod) %= Mod;
            (B[c] += 1LL * w[c] * v % Mod) %= Mod;
            if (vec[c].size() <= S) (Res += 1LL * A[c] * inv2 % Mod) %= Mod;
            w[c]++;
        }
        for (int i = 1; i <= n; ++i) A[i] = B[i] = w[i] = 0;
    }
    // ans ABBA (A, B <= S)
    // Ans AABB
    // res ABBA (A  > S)
    // Res ABBA (A <= S, B > S)
    // std::cout << S << std::endl;
    // std::cout << "All = " << All << std::endl;
    // std::cout << "cnt = " << cnt << std::endl;
    // std::cout << "ans = " << ans << std::endl;
    // std::cout << "Ans = " << Ans << std::endl;
    // std::cout << "res = " << res << std::endl;
    // std::cout << "Res = " << Res << std::endl;
    // std::cout << All << ' ' << cnt << ' ' << ans << ' ' << Ans << ' ' << res << ' ' << Res << std::endl;
    (All += Mod - cnt) %= Mod;
    (All += Mod - ans) %= Mod, (All += Mod - Ans) %= Mod;
    (All += Mod - res) %= Mod, (All += Mod - Res) %= Mod;
    std::cout << All << std::endl;
    return 0;
}

/*
12
1 2 3 3 2 1 2 3 2 1 2 1
Answer: 44

7
1 2 2 1 2 1 1

*/
