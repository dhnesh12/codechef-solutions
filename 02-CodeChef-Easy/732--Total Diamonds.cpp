/*                         _
                        _ooOoo_
                       o8888888o
                       88" . "88
                       (| -_- |)
                       O\  =  /O
                    ____/`---'\____
                  .'  \\|     |//  `.
                 /  \\|||  :  |||//  \
                /  _||||| -:- |||||_  \
                |   | \\\  -  /'| |   |
                | \_|  `\`---'//  |_/ |
                \  .-\__ `-. -'__/-.  /
              ___`. .'  /--.--\  `. .'___
           ."" '<  `.___\_<|>_/___.' _> \"".
          | | :  `- \`. ;`. _/; .'/ /  .' ; |
          \  \ `-.   \_\_`. _.'_/_/  -' _.' /
===========`-.`___`-.__\ \___  /__.-'_.'_.-'================
 
                  Please give me AC.
*/

// @Author : Smit Vavliya

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
#include <cstdio>
#include <queue>
#include <stack>
#include <numeric>
#include <complex>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp>     // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>
using namespace std;
using cd = complex<double>;
const double PI = acos(-1);
#define int long long int
#define Int register int
#define double long double
#define fr(i, s, n) for (int i = s; i <= n; ++i)
#define frr(i, s, n) for (int i = s; i >= n; --i)
#define FAST ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define mod 1000000007
#define M 998244353
#define BLOCK 555
const int inf = (1LL << 60) - 1;
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
struct pair_hash { template <class T1, class T2> std::size_t operator()(const std::pair<T1, T2> &p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);

        return h1 ^ h2;
    }
};

bool f(int x, int y) {
    return x > y;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first)
        return a.first > b.first;
    else
        return a.second > b.second;
}

bool isPrime(int n) {
    if (n == 1)
        return false;

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

int lcm(int a, int b) {
    return (a * b) / __gcd(a, b);
}

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

string Binary(int n) {
    string s;
    while (n) {
        s += to_string(n & 1);
        n = n >> 1;
    }
    return s;
}

int index(vector<int> a, int n, int ele) {
    for (int i = 0; i < n; i++) {
        if (ele == a[i])
            return i;
    }

    return -1;
}

int countDigit(int n) {
    int cnt = 0;
    while (n != 0)
    {
        n = n / 10;
        cnt += 1;
    }

    return cnt;
}

bool IsPowerOfTwo(int x) {
    return (x & (x - 1)) == 0;
}

unsigned int factorial(unsigned int n) {
    if (n == 0)
        return 1;
    return n * factorial(n - 1);
}

int fac[1000005];
void fact(int p) {
    fac[0] = 1;
    for (int i = 1; i <= 1000005; i++)
        fac[i] = (fac[i - 1] * i) % p;
}

int modFact(int n, int p) {
    if (n >= p)
        return 0;

    int result = 1;
    for (int i = 1; i <= n; i++)
        result = (result * i) % p;

    return result;
}

int power(int x, unsigned int y) {
    int res = 1;
    while (y > 0){
        if (y & 1)
            res = res * x;

        y = y >> 1;
        x = x * x;
    }
    return res;
}

int powerMod(int a, int b, int MOD){
    int x = 1 % MOD;
    a %= MOD;
    while (b)
    {
        if ((1 & b))
            x = x * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return x;
}

int modInverse(int n, int p) {
    return powerMod(n, p - 2, p);
}

int nprModP(int n, int r, int p) {
    if (r == 0)
        return 1;
    else if (n < r)
        return 0;
    else
        return (fac[n] * modInverse(fac[n - r], p) % p) % p;
}

int ncrModP(int n, int r, int p) {
    if (r == 0)
        return 1;
    else if (n < r)
        return 0;
    else
        return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
}

// no. of cyclic shift needed = (j - pos[j] + N) % N;
// no. of cyclic shift needed = (final_pos[j] - curr_pos[j] + N) % N;
// a + b = (a ^ b) + 2 * (a & b);
// to fill the matrix cyclically = (i + j) % n;

const int N = 2e6 + 2;
vector<int> graph[N];
vector<bool> visited;
int arr[N];
int dp[N];
int n, m, k, p, x, y, q, z, d;
string s, t;

void solve()
{
    cin >> n;
    arr[0] = 0;
    for(int i = 2; i <= 2 * n; i++) {
        int num = i;
        int sume = 0, sumo = 0;
        while(num) {
            int r = num % 10;
            if(r % 2) sumo += r;
            else sume += r;
            num /= 10;
        }
        if(i <= n + 1)
            arr[i] = arr[i - 1] + (i - 1) * abs(sume - sumo);
        else 
            arr[i] = arr[i - 1] + (2 * n - i + 1) * abs(sume - sumo);
    }
    cout << arr[2 * n] << endl;
}
 
int32_t main()
{
    FAST int T;
    cin >> T;
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    while (T--) {
        solve();
    }
}
