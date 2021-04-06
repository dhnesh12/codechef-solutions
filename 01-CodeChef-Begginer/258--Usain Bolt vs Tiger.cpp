//#define _GLIBCXX_DEB // Iterator safety; out-of-bounds access for Containers, etc.
//#pragma GCC optimize "trapv" // abort() on (signed) integer overflow.
#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>

#define ll long long int
#define mod 1000000007
#define deb(x) cout << #x << "=" << x << "\n"
#define deb2(x, y) cout << #x << "=" << x << "," << #y << "=" << y << "\n"
#define prec(n) fixed << setprecision(n)
#define maxpq priority_queue<int>
#define minpq priority_queue<int, vector<int>, greater<int>>
#define PI 3.1415926535897932384626
#define INF 1000000000
#define no_of_digits(n) floor(log10(n)) + 1
#define bits(n) __builtin_popcount(n)
#define lsb(n) __builtin_clz(n) // count leading zeroes before 1
#define rsb(n) __builtin_ctz(n) // count trailing zeroes before 1

ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    else
        return gcd(b, a % b);
}
ll lcm(ll a, ll b)
{
    ll g = gcd(a, b);
    return a / g * b;
}
int sum_of_digits(int a)
{
    int s = 0;
    while (a > 0)
    {
        s += a % 10;
        a /= 10;
    }
    return s;
}
string toBinary(int n)
{
    string r;
    while (n != 0)
    {
        r = (n % 2 == 0 ? "0" : "1") + r;
        n /= 2;
    }
    return r;
}
int binaryToDecimal(string n)
{
    string num = n;
    int dec_value = 0;
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--)
    {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }

    return dec_value;
}
ll add(ll a, ll b, ll m = mod)
{
    if (a >= m)
        a %= m;
    if (b >= m)
        b %= m;
    if (a < 0)
        a += m;
    if (b < 0)
        b += m;
    ll res = a + b;
    if (res >= m or res <= -m)
        res %= m;
    if (res < 0)
        res += m;
    return res;
}

ll mul(ll a, ll b, ll m = mod)
{
    if (a >= m)
        a %= m;
    if (b >= m)
        b %= m;
    if (a < 0)
        a += m;
    if (b < 0)
        b += m;
    ll res = a * b;
    if (res >= m or res <= -m)
        res %= m;
    if (res < 0)
        res += m;
    return res;
}

ll pow_mod(ll a, ll b, ll m = mod)
{
    ll res = 1LL;
    a = a % m;
    while (b)
    {
        if (b & 1)
            res = mul(res, a, m);
        b >>= 1;
        a = mul(a, a, m);
    }
    return res;
}

ll fastexp(ll a, ll b)
{
    ll res = 1LL;
    while (b)
    {
        if (b & 1)
            res = res * a;
        b >>= 1;
        a *= a;
    }
    return res;
}
ll ncr(ll n, ll r)
{
    ll p = 1, k = 1;
    if (n - r < r)
        r = n - r;

    if (r != 0)
    {
        while (r)
        {
            p = mul(p, n);
            k = mul(k, r);
            ll m = __gcd(p, k);
            p /= m;
            k /= m;

            n--;
            r--;
        }
    }
    else
        p = 1;
    return p;
}
ll nextPowerOf2(ll n)
{
    ll p = 1;
    if (n && !(n & (n - 1)))
        return n;

    while (p < n)
        p <<= 1;

    return p;
}

int countSetBits(ll n)
{
    ll count = 0;
    while (n)
    {
        n &= (n - 1);
        count++;
    }
    return count;
}

void solve()
{
    double finish,dist_b,tiger_a,bolt_speed;
    cin>>finish>>dist_b>>tiger_a>>bolt_speed;
    double tiger_time=sqrt((2*(dist_b+finish)/tiger_a));
    double bolt_time=finish/bolt_speed;
    if(bolt_time>=tiger_time)
    cout<<"Tiger\n";
    else
    cout<<"Bolt\n";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    // for getting input from input.txt
    freopen("input1.txt", "r", stdin);
    // for writing output to output.txt
    freopen("output1.txt", "w", stdout);
#endif
    int t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}