#include<bits/stdc++.h>
#define sz(a) (int)(a.size())
using namespace std;
const int MAX = 1005;
int dp[MAX];
int f[MAX];
int cnt[MAX];
int main()
{
    ios_base::sync_with_stdio(0);
    int T;
    cin >> T;
    assert(1 <= T && T <= 100);
    while(T--)
    {
        int n , K;
        cin >> n >> K;
        assert(1 <= n && n <= 1000);
        assert(1 <= K && K <= 1000);
        for(int i = 0; i < n; i++)
        {
            cin >> f[i];
            assert(1 <= f[i] && f[i] <= 100);
        }
        for(int i = 1; i <= n; i++)
                dp[i] = 1e9;
        dp[0] = 0;
        for(int i = 0; i < n; i++)
        {
            memset(cnt , 0 , sizeof cnt);
            for(int j = i; j < n; j++)
            {
                cnt[f[j]]++;
                int g = 0;
                for(int k = 1; k <= 100; k++)
                    g += cnt[k] == 1 ? 0 : cnt[k];
                dp[j + 1] = min(dp[i] + g + K , dp[j + 1]);
            }
        }
        cout << dp[n] << endl;
    }
    return 0;
} 
