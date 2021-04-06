/**
 ____ ____ ____ ____ ____
||a |||t |||o |||d |||o ||
||__|||__|||__|||__|||__||
|/__\|/__\|/__\|/__\|/__\|

**/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N_MAX = 17;

const int MASK_MAX = 32770;

int t;

int n;

int a[N_MAX];

int m;

bool discount[MASK_MAX];

int dp[MASK_MAX];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--)
    {
        cin >> n;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a + 1, a + n + 1);
        reverse(a + 1, a + n + 1);
        for(int mask = 0; mask < (1 << n); mask++)
            discount[mask] = false;
        cin >> m;
        for(int i = 1; i <= m; i++)
        {
            int cnt;
            cin >> cnt;
            int mask = 0;
            for(int j = 1; j <= cnt; j++)
            {
                int x;
                cin >> x;
                mask ^= (1 << (x - 1));
            }
            discount[mask] = true;
        }
        for(int mask = 1; mask < (1 << n); mask++)
        {
            dp[mask] = INT_MIN;
            int cnt = __builtin_popcount(mask);
            for(int mask1 = mask; mask1 > 0; mask1 = ((mask1 - 1) & mask))
                if(discount[mask1] == true)
                    dp[mask] = max(dp[mask], dp[mask ^ mask1] + a[cnt]);
                else
                    dp[mask] = max(dp[mask], dp[mask ^ mask1]);
        }
        int ans = 0;
        for(int i = 1; i <= n; i++)
            ans += a[i];
        ans -= dp[(1 << n) - 1];
        cout << ans << "\n";
    }
    return 0;
}
