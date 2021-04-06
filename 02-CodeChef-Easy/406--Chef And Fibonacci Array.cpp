#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define endl "\n"

#define mod 1000000007

const ll MX = 111, shift = 51;

ll dp[MX][MX][MX];

ll n, arr[MX], t;

ll calc(ll pos, ll dpos, ll dnxt)
{

    if (pos == 101)
        return 1;

    if (dpos + arr[pos] < 0 || dnxt + arr[pos + 1] < 0)
        return 0;

    ll &ret = dp[pos][dpos + shift][dnxt + shift];

    if (ret != -1)
        return ret;

    ret = 0;

    for (ll app = 0; app <= min(dpos + arr[pos], dnxt + arr[pos + 1]); app++)
    {

        ret += calc(pos + 1, dnxt - app, app);

        ret %= mod;

    }

    return ret;

}

int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> t;

    while (t--)
    {

        memset(dp, -1, sizeof(dp));

        cin >> n;

        for (ll j = 1; j <= 100; j++)
            arr[j] = 0;

        for (ll j = 1; j <= n; j++)
            cin >> arr[j];

        cout << calc(1, 0, 0) << endl;

    }

}


