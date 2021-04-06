#include <bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define pmod 1000000006
typedef long long ll;
ll p(ll a, ll b)
{
    if (b == 0)
        return 1;
    ll temp = (p(a, b / 2) * p(a, b / 2)) % mod;
    if (b % 2 == 0)
        return temp;
    else
        return (temp * a) % mod;
}
ll tab[6000][6000];
int main()
{
    ll t;
    cin >> t;
    memset(tab, 0, sizeof(tab));
    for (ll i = 0; i <= 5500; i++)
    {
        tab[i][0] = 1;
    }
    tab[1][1] = 1;
    for (ll i = 2; i <= 5500; i++)
    {
        for (ll j = 1; j <= 5500; j++)
        {
            tab[i][j] = (tab[i - 1][j - 1] + tab[i - 1][j]) % pmod;
        }
    }
    while (t--)
    {
        ll n, k;
        cin >> n >> k;
        ll arr[n];
        for (ll i = 0; i < n; i++)
        {
            cin >> arr[i];
        }
        ll ans = 1;
        sort(arr, arr + n);
        for (ll i = 0; i < n; i++)
        {
            ll temp = (tab[n - 1][k - 1] - tab[i][k - 1] - tab[n - i - 1][k - 1] + pmod + pmod) % pmod;
            ans = (ans * p(arr[i], temp)) % mod;
        }
        cout << ans << endl;
    }
}