#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void solve ()
{
    int n;
    cin >> n;

    ll cur = 0;

    ll ans = 0;

    for ( int i=0; i<n; i++ )
    {
        int x;
        cin >> x;

        cur += !( x & 1 );

        ans += ( x & 1 ) * cur;
    }

    cout << ans << '\n';
}

int main ()
{
    ios_base::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);

    int t;
    cin >> t;

    while ( t-- )
    {
        solve();
    }

    return 0;
}
