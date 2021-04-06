#include<bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<ll, ll> pll;
#define pb push_back
typedef long double ld;
#define fi first
#define se second
#define PI 3.14159265358979323846264338327950288419716939937510
#define mp make_pair
#define vvl vector<vector<ll>>
#define vll vector<ll>
#define vpll vector<pll>
#define vvpll vector<vpll>
/*
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
*/

ll inf = 1e18;
ll mod = 1e9 + 7;
ld eps = 1e-9;
ll power(ll x, ll y, ll p)
{
    ll res = 1;
    x = x % p;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) % p;
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}
ll pwr(ll x, ll y)
{
    ll res = 1;
    x = x ;
    while (y > 0)
    {
        if (y & 1)
            res = (res * x) ;
        y = y >> 1;
        x = (x * x) ;
    }
    return res;
}
ll modInverse(ll n, ll p)
{
    return power(n, p - 2, p);
}
ll gcd(ll a, ll b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);

}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll i, y, x, z, g, key,   h, n, m, a, b, c, j, k, q;
    ll t2, t3, t4, t1, t5, t6;
    string s, s2, s1, t;
    ll l, r;
    ll tc;
    //cin >> tc;
    tc = 1;
    while (tc--)
    {
        cin >> n >> m;
        map<ll, set<ll>>ma;
        for (i = 1; i <= n; i++)
        {
            cin >> x >> y;
            ma[x * y].insert(i);
        }
        ll ans = 0;
        for (i = 1; i <= m; i++)
        {
            cin >> x >> y;
            if (ma[x * y].size())
            {
                ans++;
                ma[x * y].erase(ma[x * y].begin());
            }
        }
        cout << ans;




    }
    return 0;
}