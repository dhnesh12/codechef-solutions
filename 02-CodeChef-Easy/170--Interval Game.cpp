#include <bits/stdc++.h>
using namespace std;

const int maxn = 3e5 + 10, maxm = 210;
long long dp[2][maxn], b[maxm], a[maxn], t, n, m, ps[maxn];


void input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) 
        cin >> a[i], ps[i] = ps[i - 1] + a[i];
    for (int i = 1; i <= m; i++)
        cin >> b[i];
}

int main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> t;
    while (t--) {
        input();
        long long ans = -1e17;
        for (int i = m, tmp = 0; i > 0; i--) {
            deque <int> st;
            for (int j = n; j > 0; j--) {
                while (st.size() && st.back() >= j + (i < m? b[i] - b[i + 1]: 0))
                    st.pop_back();
                dp[i % 2][j] = ps[j + b[i] - 1] - ps[j - 1] - ((st.size()? dp[(i + 1) % 2][st.back()]: 0));
                while (st.size() && (dp[(i + 1) % 2][st.front()] <= dp[(i + 1) % 2][j]))
                    st.pop_front();
                st.push_front(j);
            }
        }
        cout << *max_element(dp[1] + 1, dp[1] + n - b[1] + 2) << endl;
        /*
           for (int i = 1; i <= n - b[0] + 1; i++)
           ans = max(ans, dp[1][i]);
           cout << ans << endl;*/
    }
    return 0;
}
