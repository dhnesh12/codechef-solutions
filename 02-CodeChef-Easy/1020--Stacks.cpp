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
void solve()
{
    int n, num, i;
    vi ans;
    cin >> n;
    for (i = 0; i < n; i++)
    {
        cin >> num;
        auto it = upper_bound(all(ans), num);
        if (it == ans.end())
            ans.pb(num);
        else
            *it = num;
    }
    cout << ans.size() << " ";
    for (auto x : ans)
        cout << x << " ";
    cout << nl;
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