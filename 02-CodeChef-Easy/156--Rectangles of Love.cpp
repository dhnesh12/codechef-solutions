#include <bits/stdc++.h>
using namespace std;
#define ll long long int
#define inf 1e18
#define P 1000000007
#define ld long double
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    ll t, i, j;
    cin >> t;
    while (t--)
    {
        ld n, m, k;
        cin >> n >> m >> k;
        vector<pair<ld, ld>> v;
        for (i = 0; i < k; i++)
        {
            ll x, y, z;
            cin >> z;
            y = (z) % (ll)m;
            if (y == 0)
                y = m;
            x = ceil((ld)z / (ld)m);
            v.push_back({x, y});
        }

        ld sum = 0;
        ld poss = ((n * (n + 1)) / 2) * (((m * (m + 1)) / 2));

        for (i = 0; i < k; i++)
        {
            ll x = v[i].first;
            ll y = v[i].second;
            sum = sum + (x * (n + 1 - x)) * (y * (m + 1 - y));
        }
        cout << fixed << setprecision(20) << (sum) / poss << "\n";
    }
    return (0);
}
