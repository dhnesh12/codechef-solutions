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
int a[1000][1000], color[1000][1000];
void solve()
{
    int n, m, i, j;
    cin >> n >> m;
    string s;
    for (i = 0; i < n; i++)
    {
        cin >> s;
        for (j = 0; j < m; j++)
        {
            color[i][j] = 0;
            a[i][j] = 0;
            if (s[j] == '#')
                a[i][j] = 1;
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (i + 1 < n && j + 1 < m)
                if (a[i][j] != 1 && a[i][j + 1] != 1 && a[i + 1][j] != 1 && a[i + 1][j + 1] != 1)
                    color[i][j] = color[i][j + 1] = color[i + 1][j] = color[i + 1][j + 1] = 1;
        }
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (color[i][j] == 0 && a[i][j] != 1)
            {
                cout << "NO" << nl;
                return;
            }
        }
    }
    cout << "YES" << nl;
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