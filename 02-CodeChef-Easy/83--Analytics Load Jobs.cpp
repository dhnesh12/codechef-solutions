#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = a; i <= b; i++)
#define bep(i, a, b) for(int i = a; i >= b; i--)
#define ll long long
#define lowbit(x) (x & (-x))

using namespace std;

const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int mod = 1e9 + 7;
const double eps = 1e-8;
const int N = 1e5 + 10;

int num[N][3];
int arr[N], tail;
int vis[N];

bool judge(int x, int k, int j) {
    int sum1 = 0, sum2 = 0;
    rep(i, 1, tail) {
        sum1 = 0;
        int id = arr[i];
        int use1 = 0;
        int num1 = num[id][1];
        int num2 = num[id][2];
        if(x == 1 && num2) return false;
        while(num2 > 0 && x >= 2) {
            int t = min(num2, x / 2);
            num1 -= x - t*2;
            num2 -= t;
            sum1++;
            if(sum1 >= k) {
                sum2++;
                sum1 = 0;
            }
        }
        while(num1 > 0) {
            num1 -= x;
            sum1++;
            if(sum1 >= k) {
                sum2++;
                sum1 = 0;
            }
        }
        if(sum1) sum2++, sum1 = 0;
    }
    // cout << x << ' ' << (sum2 > j) << endl;
    if(sum2 > j) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    int T;
    cin >> T;
    while(T--) {
        int n, k, j;
        cin >> n >> k >> j;
        rep(i, 1, n) {
            int pos, w;
            cin >> pos >> w;
            num[pos][w]++;
            if(!vis[pos]) {
                vis[pos] = 1;
                arr[++tail] = pos;
            }
        }
        int l = 1, r = 1e7;
        int res;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(judge(mid, k, j)) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        cout << res << endl;
        
        rep(i, 1, tail) {
            num[arr[i]][1] = num[arr[i]][2] = vis[arr[i]] = 0;
        }
        tail = 0;
    }
    return 0;
}