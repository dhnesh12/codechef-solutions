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
    int n, m, num, val;
    cin >> n >> m;
    map<int, int> mp;
    vi v;
    while (n--)
    {
        cin >> num >> val;
        mp[num] = max(mp[num], val);
    }
    for (auto x : mp)
        v.pb(x.second);
    sort(all(v), greater<int>());
    cout << v[0] + v[1] << nl;
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