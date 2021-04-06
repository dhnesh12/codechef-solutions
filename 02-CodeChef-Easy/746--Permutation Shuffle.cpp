#include <bits/stdc++.h>
using namespace std;
#define N 100005
#define pb push_back
#define all(f) f.begin(), f.end()
#define nl "\n"
#define debug(g) cout << #g << " : " << g << nl
typedef long long ll;
typedef vector<ll> vi;
typedef pair<int, int> pii;
const ll mod = (1e9) + 7;
const double pi = acos(-1);
ll gcd(ll a, ll b) { return (b == 0) ? a : gcd(b, a % b); }
ll lcm(ll a, ll b) { return (a * b) / gcd(a, b); }
int a[N];
void solve()
{
    int n, m, i, l, r, l1, r1;
    cin >> n >> m;
    for (i = 1; i <= n; i++)
        cin >> a[i];
    vector<pii> v(m);
    for (i = 0; i < m; i++)
    {
        cin >> l >> r;
        v[i] = {l, r};
    }
    sort(all(v));
    l = v[0].first;
    r = v[0].second;
    vector<pii> ranges;
    for (i = 1; i < m; i++)
    {
        l1 = v[i].first;
        r1 = v[i].second;
        if (l1 <= r)
        {
            r = max(r, r1);
        }
        else
        {
            ranges.pb({l, r});
            l = l1;
            r = r1;
        }
    }
    ranges.pb({l, r});
    m = ranges.size();
    for (i = 0; i < m; i++)
    {
        sort(a + ranges[i].first, a + ranges[i].second + 1);
    }
    for (i = 1; i <= n; i++)
    {
        if (a[i] != i)
        {
            cout << "Impossible" << nl;
            return;
        }
    }
    cout << "Possible" << nl;
}
int main()
{
    //fast io
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    ll t = 1;
    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}