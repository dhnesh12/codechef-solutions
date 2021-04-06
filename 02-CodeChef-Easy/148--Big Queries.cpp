// @Author : Demoralized

#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <climits>
#include <cstring>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <initializer_list>
#include <string.h>
#include <string>
#include <deque>
#include <stack>
#include <queue>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
#define int long long int
#define double long double
#define FAST                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);
#define mod 1000000007
#define M 998244353
const int inf = (1LL << 60) - 1;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

int powerMod(int x, unsigned int y, int p)
{
    int res = 1;
    x = x;
    if (x == 0)
        return 0;
    while (y > 0)
    {
        if (y & 1)
        {
            res *= x;
            res %= p;
        }
        y = y >> 1;
        x = (x * x);
        x %= p;
        res %= p;
    }
    return res;
}

int modInverse(int n, int p)
{
    return powerMod(n, p - 2, p);
}

int ncrModP(int n, int r, int p)
{
    if (r == 0)
    {
        return 1;
    }
    else if (n < r)
    {
        return 0;
    }
    else
    {
        int fac[n + 1];
        fac[0] = 1;
        for (int i = 1; i <= n; i++)
        {
            fac[i] = (fac[i - 1] * i) % p;
        }
        return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
    }
}

bool isPrime(int n)
{
    if (n == 1)
        return false;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int power(int x, unsigned int y)
{
    int res = 1;

    while (y > 0)
    {
        if (y & 1)
            res = res * x;

        y = y >> 1;
        x = x * x;
    }
    return res;
}

const int N = 1000001;
vector<int> graph[N];
vector<bool> visited(N);
int arr[N], pref[N];
int dp[N];
int n, m, k, p, x, y, q, z;
// string s, t;

struct Segtree
{
    int n_t;
    int n_f;
};
struct lazy
{
    int n_t;
    int n_f;
    int update;
    int p;
};
Segtree t[N], lazy1[N];
lazy lazy2[N];
int prefix_2[N];
int prefix_5[N];

int two(int num)
{
    int cnt = 0;
    while (num % 2 == 0 && num)
    {
        num /= 2;
        cnt++;
    }
    return cnt;
}

int five(int num)
{
    int cnt = 0;
    while (num % 5 == 0 && num)
    {
        num /= 5;
        cnt++;
    }
    return cnt;
}

struct SegmentTree
{
    void build(int node, int start, int end)
    {
        if (start == end)
        {
            lazy1[node].n_t = 0;
            lazy1[node].n_f = 0;
            lazy2[node].n_t = 0;
            lazy2[node].n_t = 0;
            lazy2[node].update = 0;
            lazy2[node].p = 0;
            t[node].n_t = two(arr[start]);
            t[node].n_f = five(arr[start]);
        }
        else
        {
            int mid = (start + end) / 2;
            build(2 * node, start, mid);
            build(2 * node + 1, mid + 1, end);

            t[node].n_t = t[2 * node].n_t + t[2 * node + 1].n_t;
            t[node].n_f = t[2 * node].n_f + t[2 * node + 1].n_f;
            lazy1[node].n_t = 0;
            lazy1[node].n_f = 0;
            lazy2[node].n_t = 0;
            lazy2[node].n_f = 0;
            lazy2[node].update = 0;
            lazy2[node].p = 0;
        }
    }

    Segtree queryLazy(int node, int start, int end, int l, int r)
    {
        if (start > end || start > r || end < l)
            return {0, 0};

        if (lazy2[node].update)
        {
            int L = lazy2[node].p;
            int twos = prefix_2[end - L + 1] - prefix_2[start - L];
            int fives = prefix_5[end - L + 1] - prefix_5[start - L];
            t[node].n_t = (end - start + 1) * lazy2[node].n_t + twos;
            t[node].n_f = (end - start + 1) * lazy2[node].n_f + fives;
            if (start != end)
            {
                lazy1[node * 2].n_t = lazy1[node * 2 + 1].n_t = 0;
                lazy1[node * 2].n_f = lazy1[node * 2 + 1].n_f = 0;
                lazy2[node * 2].n_t = lazy2[node * 2 + 1].n_t = lazy2[node].n_t;
                lazy2[node * 2].n_f = lazy2[node * 2 + 1].n_f = lazy2[node].n_f;
                lazy2[node * 2].p = lazy2[node * 2 + 1].p = L;
                lazy2[node * 2].update = lazy2[node * 2 + 1].update = 1;
            }
            lazy2[node].n_t = lazy2[node].n_f = lazy2[node].p = lazy2[node].update = 0;
        }

        if (lazy1[node].n_t != 0 || lazy1[node].n_f != 0)
        {
            t[node].n_t += (end - start + 1) * lazy1[node].n_t;
            t[node].n_f += (end - start + 1) * lazy1[node].n_f;
            if (start != end)
            {
                lazy1[node * 2].n_t += lazy1[node].n_t;
                lazy1[node * 2].n_f += lazy1[node].n_f;
                lazy1[node * 2 + 1].n_t += lazy1[node].n_t;
                lazy1[node * 2 + 1].n_f += lazy1[node].n_f;
            }
            lazy1[node].n_t = lazy1[node].n_f = 0;
        }

        if (start >= l && end <= r)
            return t[node];

        int mid = (start + end) / 2;

        Segtree left = queryLazy(node * 2, start, mid, l, r);
        Segtree right = queryLazy(node * 2 + 1, mid + 1, end, l, r);
        Segtree temp;
        temp.n_t = left.n_t + right.n_t;
        temp.n_f = left.n_f + right.n_f;
        return temp;
    }

    void updateLazyRange(int node, int start, int end, int l, int r, int val1, int val2, int type)
    {
        if (lazy2[node].update)
        {
            int L = lazy2[node].p;
            int twos = prefix_2[end - L + 1] - prefix_2[start - L];
            int fives = prefix_5[end - L + 1] - prefix_5[start - L];
            t[node].n_t = (end - start + 1) * lazy2[node].n_t + twos;
            t[node].n_f = (end - start + 1) * lazy2[node].n_f + fives;
            if (start != end)
            {
                lazy1[node * 2].n_t = lazy1[node * 2 + 1].n_t = 0;
                lazy1[node * 2].n_f = lazy1[node * 2 + 1].n_f = 0;
                lazy2[node * 2].n_t = lazy2[node * 2 + 1].n_t = lazy2[node].n_t;
                lazy2[node * 2].n_f = lazy2[node * 2 + 1].n_f = lazy2[node].n_f;
                lazy2[node * 2].p = lazy2[node * 2 + 1].p = L;
                lazy2[node * 2].update = lazy2[node * 2 + 1].update = 1;
            }
            lazy2[node].n_t = lazy2[node].n_f = lazy2[node].p = lazy2[node].update = 0;
        }

        if (lazy1[node].n_t != 0 || lazy1[node].n_f != 0)
        {
            t[node].n_t += (end - start + 1) * lazy1[node].n_t;
            t[node].n_f += (end - start + 1) * lazy1[node].n_f;
            if (start != end)
            {
                lazy1[node * 2].n_t += lazy1[node].n_t;
                lazy1[node * 2].n_f += lazy1[node].n_f;
                lazy1[node * 2 + 1].n_t += lazy1[node].n_t;
                lazy1[node * 2 + 1].n_f += lazy1[node].n_f;
            }
            lazy1[node].n_t = lazy1[node].n_f = 0;
        }

        if (start > end || start > r || end < l)
            return;

        if (start >= l && end <= r)
        {
            if (type == 1)
            {
                t[node].n_t += (end - start + 1) * val1;
                t[node].n_f += (end - start + 1) * val2;
                if (start != end)
                {
                    lazy1[node * 2].n_t += val1;
                    lazy1[node * 2].n_f += val2;
                    lazy1[node * 2 + 1].n_t += val1;
                    lazy1[node * 2 + 1].n_f += val2;
                }
            }
            else
            {
                int twos = prefix_2[end - l + 1] - prefix_2[start - l];
                int fives = prefix_5[end - l + 1] - prefix_5[start - l];
                t[node].n_t = (end - start + 1) * val1 + twos;
                t[node].n_f = (end - start + 1) * val2 + fives;
                if (start != end)
                {
                    lazy1[node * 2].n_t = lazy1[node * 2 + 1].n_t = 0;
                    lazy1[node * 2].n_f = lazy1[node * 2 + 1].n_f = 0;
                    lazy2[node * 2].n_t = lazy2[node * 2 + 1].n_t = val1;
                    lazy2[node * 2].n_f = lazy2[node * 2 + 1].n_f = val2;
                    lazy2[node * 2].p = lazy2[node * 2 + 1].p = l;
                    lazy2[node * 2].update = lazy2[node * 2 + 1].update = 1;
                }
            }
            return;
        }

        int mid = (start + end) / 2;

        updateLazyRange(node * 2, start, mid, l, r, val1, val2, type);
        updateLazyRange(node * 2 + 1, mid + 1, end, l, r, val1, val2, type);

        t[node].n_t = t[node * 2].n_t + t[node * 2 + 1].n_t;
        t[node].n_f = t[node * 2].n_f + t[node * 2 + 1].n_f;
    }
} SegmentTree;

void solve()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> arr[i];

    SegmentTree.build(1, 1, n);

    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        int t;
        cin >> t;
        int Ans = 0;
        if (t == 1)
        {
            int l, r;
            cin >> l >> r >> x;
            int twos = two(x);
            int fives = five(x);
            SegmentTree.updateLazyRange(1, 1, n, l, r, twos, fives, 1);
        }
        else if (t == 2)
        {
            int l, r;
            cin >> l >> r >> x;
            int twos = two(x);
            int fives = five(x);
            SegmentTree.updateLazyRange(1, 1, n, l, r, twos, fives, 2);
        }
        else
        {
            int l, r;
            cin >> l >> r;

            Segtree temp;
            temp = SegmentTree.queryLazy(1, 1, n, l, r);
            Ans = min(temp.n_t, temp.n_f);
        }
        ans += Ans;
    }

    cout << ans << endl;
}

signed main()
{
    FAST int T;
    cin >> T;

    for (int i = 1; i <= 1000000; i++)
    {
        int t = two(i);
        int f = five(i);
        prefix_2[i] = prefix_2[i - 1] + t;
        prefix_5[i] = prefix_5[i - 1] + f;
    }

    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    while (T--)
    {
        solve();
    }
}