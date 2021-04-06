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
ll mod = 998244353;
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
ll gethr(string s)
{
    ll num = (s[0] - '0') * 10 + (s[1] - '0');
    return num;
}
ll getm(string s)
{
    ll num = (s[3] - '0') * 10 + (s[4] - '0');
    return num;
}
string make_time(ll start, ll end)
{
    string res;
    char a;
    ll t1;
    t1 = start / 60;
    a = t1 / 10 + '0';
    res.pb(a);
    a = t1 % 10 + '0';
    res.pb(a);
    res.pb(':');
    t1 = start % 60;
    a = t1 / 10 + '0';
    res.pb(a);
    a = t1 % 10 + '0';
    res.pb(a);
    res.pb(' ');

    if (end != 1440)
    {
        start = end;
        t1 = start / 60;
        a = t1 / 10 + '0';
        res.pb(a);
        a = t1 % 10 + '0';
        res.pb(a);
        res.pb(':');
        t1 = start % 60;
        a = t1 / 10 + '0';
        res.pb(a);
        a = t1 % 10 + '0';
        res.pb(a);
        return res;
    }
    else
    {
        ll i;
        for (i = 0; i < 2; i++)
            res.pb('0');
        res.pb(':');
        for (i = 0; i < 2; i++)
            res.pb('0');
        return res;

    }


}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll i, y, x, z, g, key,   h,  m, a, b, n, c, j, k, q;
    ll t2, t3, t4, t1, t5, t6;
    string s, s2, s1, t;
    ll l, r;
    ll tc;
    //cin >> tc;
    tc = 1;
    while (tc--)
    {
        ll time;
        cin >> time;
        ll val[7][1441];
        memset(val, 0, sizeof(val));

        for (i = 0; i < 7; i++)
        {
            cin >> k;
            ll prev = i - 1;
            if (prev < 0)
                prev = 6;
            while (k--)
            {
                cin >> s;
                ll sh = gethr(s);
                ll sm = getm(s);
                ll sd = i;
                sh -= time;
                if (sh < 0)
                {
                    sh = 24 + sh;
                    sd = prev;

                }
                cin >> s;
                ll eh = gethr(s);
                ll em = getm(s);
                if (eh == 0 && em == 0)
                    eh = 24;
                ll ed = i;
                eh -= time;

                if (eh < 0)
                {
                    eh = 24 + eh;
                    ed = prev;

                }
                //cout << eh << " " << em << "\n";
                ll start = sh * 60 + sm;
                ll end = eh * 60 + em;
                //cout << end << "\n";
                if (sd != ed)
                {
                    for (j = start; j <= 1440; j++)
                        val[sd][j] = 1;
                    for (j = 0; j < end; j++)
                        val[ed][j] = 1;
                }
                else
                {
                    for (j = start; j < end; j++)
                        val[sd][j] = 1;
                }

            }

        }
        vector<vector<string>>ans(7);
        ll start;
        for (i = 0; i < 7; i++)
        {
            ll flag = 0;
            for (j = 0; j <= 1440; j++)
            {
                if (val[i][j] == 1)
                {
                    if (j == 0 || val[i][j - 1] == 0)
                        start = j;
                }
                if (val[i][j] == 0)
                {
                    if (j > 0 && val[i][j - 1] == 1)
                    {

                        ans[i].pb(make_time(start, j ));
                    }
                }
            }
            if (val[i][j - 1] == 1)
            {

                ans[i].pb(make_time(start, j - 1 ));

            }
        }
        for (i = 0; i < 7; i++)
        {
            cout << ans[i].size() << '\n';
            for (auto u : ans[i])
                cout << u << "\n";
        }




    }
    return 0;
}