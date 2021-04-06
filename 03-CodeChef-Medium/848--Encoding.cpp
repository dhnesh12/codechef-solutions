#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")

#include<bits/stdc++.h>
#define ll              long long int
#define ld              long double
#define ff              first
#define ss              second
#define mod             1000000007
#define ull             unsigned long long
#define vll             vector<ll>
#define uom             unordered_map
#define uos             unordered_set
#define pll             pair<ll, ll>
#define INF             9223372036854775807
#define w(t)            ll tests;    cin>>tests;        while(tests--)
#define endl            "\n"
#define pb(x)           push_back(x)
#define all(x)          x.begin(), x.end()
#define mp(a, b)        make_pair(a, b)
#define setp(x, y)      fixed << setprecision(x) << y
#define f(i, a, b)      for(ll i = a ; i < b ; i++)
#define fo(j, a, b)     for(ll j = a ; j >= b ; j--)
#define fill(a, n, x)   f(i, 0, n)     a[i]=x;
using namespace std;

ll v[100005];
ll dp[100005][10][2], cntdp[100005][2];

void clc()
{
    f(i, 0, 100005)
    f(j, 0, 10)
    f(k, 0, 2)
    dp[i][j][k] = -1;
}

ll cnt(string s, ll n, bool tight)
{
    if (!tight)
        return v[n];

    if (n == 0)
        return 1;

    if (cntdp[n][tight] != -1)
        return cntdp[n][tight];

    ll ub = s[s.length() - n] - '0', ans = 0;
    f(i, 0, ub + 1)
    ans = (ans + cnt(s, n - 1, i == ub)) % mod;

    return cntdp[n][tight] = ans;
}

ll solve(string s, ll n, ll last, bool tight)
{
    if (n == 0)
        return 0;

    if (dp[n][last][tight] != -1)
        return dp[n][last][tight];

    ll ub = (tight ? (s[s.length() - n] - '0') : 9), ans = 0;
    f(i, 0, ub + 1)
    {
        if (i != last)
            ans += (i * v[n - 1] * cnt(s, n - 1, (tight & (i == ub)))) % mod;

        ans = (ans + solve(s, n - 1, i, (tight & (i == ub)))) % mod;
    }

    return dp[n][last][tight] = ans;
}

ll bruteForce(string& L)
{
    ll prev_dig = 10;
    ll res = 0;

    for (ll i = 0; i < L.length(); i++)
    {
        if ((L[i] - '0') != prev_dig)
            res = (res + (L[i] - '0') * v[L.length() - i - 1]) % mod;

        prev_dig = (L[i] - '0');
    }

    return res % mod;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    v[0] = 1;
    f(i, 1, 100005)
    v[i] = (v[i - 1] * 10LL) % mod;

    w(t)
    {
        ll a, b;
        string l, r;
        cin >> a >> l >> b >> r;

        clc();
        memset(cntdp, -1, sizeof(cntdp));
        ll ans1 = solve(l, a, -1, 1);

        clc();
        memset(cntdp, -1, sizeof(cntdp));
        ll ans2 = solve(r, b, -1, 1);

        ll ans3 = bruteForce(l);

        cout << (ans2 - ans1 + ans3 + mod) % mod << endl;
    }

    return 0;
}