#include<iostream>
#include<ctime>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<climits>
#include<cstring>
#include<iomanip>
#include<string>
#include<bitset>
#include<unordered_map>
#include<unordered_set>
#include<set>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<deque>
#include<algorithm>
#include<functional>
#include<random>
#include<sstream>

#define y0 asdahsdlkahsdad
#define y1 aasdfasdfasdf
#define yn askfhwqriuperikldjk
#define j1 assdgsdgasghsf
#define taskname "COOLCHEF"

typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;

using namespace std;

template<typename T> inline void Cin(T &x)
{
    register char c;
    for (c = getchar(); c < '0' || c > '9'; c = getchar());
    for (x = 0; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
}
template<typename T, typename... Ts> inline void Cin(T& x, Ts&... xs) { Cin(x); Cin(xs...); }
template<typename T> inline void Cout(const T x) { if (x > 9) Cout(x / 10); putchar(x % 10 + '0'); }

const int N = 3e5;
const int len = sqrt(N);
const int BL = (N + len - 1) / len;
const int Mod = 1e9 + 7;

static int n, q, bl, i, j, k, t, ans, nId, l, r;
static int s[N], fac[N], cnt[N], a[BL][N], f[BL][BL];
unordered_map<int, int> m;

void Prepare()
{
    Cin(n, q);
    bl = (n + len - 1) / len;
    for (i = fac[0] = 1; i < n; ++i) fac[i] = fac[i - 1] * ll(i + 1) % Mod;
    for (i = 0; i < n; ++i)
    {
        Cin(k);
        auto t = m.find(k);
        if (t == m.end()) m.emplace(k, s[i] = nId++);
        else s[i] = t->second;
        //cout << s[i] << ' ';
    }
    //cout << '\n';
//    for (i = 0; i < bl; ++i)
//    {
//        for (j = i * len, k = min(j + len, n); j < k; ++j) ++cnt[s[j]];
//        for (j = 0; j < nId; ++j) a[i][j] = cnt[j];
//    }
    for (i = 0; i < bl; ++i)
    {
        ans = 1;
        for (t = i; t >= 0; f[i][t--] = ans)
            for (j = t * len, k = min(j + len, n); j < k; ++j)
                ans = ans * (ll)++cnt[s[j]] % Mod;
        for (j = 0; j < nId; ++j) a[i][j] = cnt[j], cnt[j] = 0;
    }
//    for (i = 0; i < bl; ++i, cout << '\n')
//        for (j = 0; j < nId; ++j) cout << a[i][j] << ' ';
}

inline ll InvMod(ll a, int b = Mod - 2)
{
    ll res = 1;
    for (; b > 0; b >>= 1)
    {
        if (b & 1) res = res * a % Mod;
        a = a * a % Mod;
    }
    return res;
}

inline void Update(int l, const int r)
{
    for (; l <= r; ++l)
    {
        j = s[l];
        k = ++cnt[j];
        if (i <= t)
        {
            k += a[t][j];
            if (i) k -= a[i - 1][j];
        }
        ans = ans * (ll)k % Mod;
    }
}

inline void Reset(int l, const int r) { for (; l <= r; ++l) cnt[s[l]] = 0; }

void Solve()
{
    ans = 0;
    while (--q >= 0)
    {
        Cin(i, j, k, t);
        l = ((ll)i * ans + j) % n;
        r = ((ll)k * ans + t) % n;
        if (l > r) swap(l, r);
        //cout << l << ' ' << r << '\n';
        i = l / len + 1; t = r / len - 1;
        ans = (i <= t ? f[t][i] : 1);
        //cout << ans << ' ';
        if (i == t + 2) Update(l, r), Reset(l, r);
        else Update(l, i * len - 1), Update((t + 1) * len, r),
             Reset(l, i * len - 1), Reset((t + 1) * len, r);
        //cout << ans << ' ';
        ans = fac[r - l] * InvMod(ans) % Mod;
        cout << ans << '\n';
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //freopen(taskname".inp", "r", stdin);
    //freopen(taskname".out", "w", stdout);

    Prepare();
    Solve();

    return 0;
}
