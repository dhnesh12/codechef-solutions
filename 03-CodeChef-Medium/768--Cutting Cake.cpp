#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <assert.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <numeric>
#include <chrono>
#include <functional>
#include <tuple>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <array>
#include <bitset>
#include <unordered_map>

#define foru(i, a, b) for(int i = a, _b = (b)+1; i < _b; ++i)
#define ford(i, a, b) for(int i = a, _b = (b)-1; i > _b; --i)
#define all(a) a.begin(), a.end()
#define rall(a) a.rbegin(), a.rend()
#define fr freopen
#define eb emplace_back
#define ep emplace

using namespace std;

template <class X>
bool mini(X& a, const X& b)
{
    if (a > b) { a = b; return true; } return false;
}

template <class X>
bool maxi(X& a, const X& b)
{
    if (a < b) { a = b; return true; } return false;
}

typedef const int& ci;
typedef long long ll;
typedef pair <int, int> pii;

const int N = 1501;

int n,m;
bitset <N> a[N];

void enter()
{
    cin >> m >> n;
    char c;
    foru(i, 1, m)
        foru(j, 1, n)
        {
            cin >> c;
            if (c == '1') a[i].set(j);
        }
}

void solve()
{
    foru(i, 1, m)
        foru(j, 1, n)
            a[i][j] = a[i][j] ^ a[i][j-1] ^ a[i-1][j] ^ a[i-1][j-1];
    ll res = 0;
    foru(i, 1, m)
        foru(j, i, m)
        {
            int ones = (a[j] ^ a[i-1]).count();
            int zeros = n - ones + 1;
            res += (ones*(ones - 1) + zeros*(zeros - 1)) >> 1;
        }
    cout << res;
}

int main()
{
    #define haid ""

    ios_base :: sync_with_stdio(false); cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    fr(haid".inp", "r", stdin);

#endif
    enter();
    solve();
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms";
}
