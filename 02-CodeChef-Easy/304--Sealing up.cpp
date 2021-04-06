#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAXN = 100000 + 5;
const int MAX_SIDE = 2500000;
const long long INF = 1000000000000000000LL;

int x[MAXN], y[MAXN];
long long dp[MAX_SIDE + 10];
int n, tn, m, l1, l2, c1, c2;

int main(int argc, const char * argv[]) {
    cin >> tn;
    
    assert(1 <= tn && tn <= 10);
    
    while (tn--) {
        cin >> n;
        
        assert(1 <= n && n <= 2000);
        
        for(int i = 1; i <= n; i++) {
            cin >> x[i] >> y[i];
            assert(0 <= x[i] && x[i] <= 1000000);
            assert(0 <= y[i] && y[i] <= 1000000);
        }
        for(int i = 0; i <= MAX_SIDE; i++) {
            dp[i] = INF;
        }
        
        dp[0] = 0;
        
        cin >> m;
        assert(m <= 10);
        for(int i = 1; i <= m; i++) {
            int ci, li;
            cin >> li >> ci;
            assert(1 <= li && li <= 1000000);
            assert(1 <= ci && ci <= 1000000);
            
            for(int j = li; j <= MAX_SIDE; j++) {
                dp[j] = min(dp[j], dp[j - li] + ci);
            }
            
        }
        for(int j = MAX_SIDE-1; j >= 0; j--) {
            dp[j] = min(dp[j], dp[j + 1]);
        }
        
        x[0] = x[n];
        y[0] = y[n];
        
        long long ret = 0;
        
        for(int i = 1; i <= n; i++) {
            long long sqLength = (x[i] - x[i - 1]) * 1LL * (x[i] - x[i - 1]) + (y[i] - y[i - 1]) * 1LL * (y[i] - y[i - 1]);
            long long l = 0, r = MAX_SIDE;
            while (l < r) {
                long long mid = (l + r) / 2;
                if (mid * mid < sqLength) {
                    l = mid + 1;
                } else {
                    r = mid;
                }
            }
            ret += dp[l];
        }
        
        cout << ret << endl;
    }
    return 0;
}