#include<bits/stdc++.h>
using namespace std;
#define mod 1000000007
#define ll long long int
ll t, n;
long long int a1[10];

ll dp[33][(1 << 6)][(1 << 6)];
ll solve(ll pos, ll xortight, ll btight) {
    if (pos == 31) {
        return 1;
    }

    if (dp[pos][xortight][btight] != -1) {
        return dp[pos][xortight][btight];
    }

    ll res = 0, a = 0;

    for (ll i = 0; i < n; i++) {
        if ((a1[i]) & (1 << (30 - pos))) {
            a |= (1 << i);
        }
    }

    for (ll xo = 0; xo < (1 << n); xo++) {
        ll b = (xo ^ a);
        bool flag = 1;

        ll nextbit = 0, thisbit = 0, xnthbit = 0, bnthbit = 0;

        for (ll i = n - 1; i >= 0; i--) {
            thisbit = ((b & (1 << i)) ? 1 : 0);

            if (btight & (1 << i)) {
                if (nextbit < thisbit) {
                    flag = 0;
                }
                if (nextbit == thisbit) {
                    bnthbit |= (1 << i);
                }
            }
            nextbit = thisbit;
        }


        for (ll i = n - 1; i >= 0; i--) {
            thisbit = ((xo & (1 << i)) ? 1 : 0);

            if (xortight & (1 << i)) {
                if (nextbit < thisbit) {
                    flag = 0;
                }
                else if (nextbit == thisbit) {
                    xnthbit |= (1 << i);
                }
            }
            nextbit = thisbit;


        }

        if (flag) {
            res = ((res + solve(pos + 1, xnthbit, bnthbit)) ) % mod;
        }


    }

    return dp[pos][xortight][btight] = res;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    cin >> t;

    while (t--) {
        cin >> n;

        for (ll i = 0; i < n; i++) {
            cin >> a1[i];
        }

        memset(dp, -1, sizeof dp);
        ll ans = (solve(0, ((1 << (n - 1)) - 1), ((1 << (n - 1)) - 1)) % mod);

        cout << ans << '\n';

    }
    return 0;
}