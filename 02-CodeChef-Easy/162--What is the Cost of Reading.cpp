/*One touch and i IGNITE*/
#include<bits/stdc++.h>
using namespace std;
#define cloud_007 ios_base::sync_with_stdio(false),cin.tie(0)
#define ll long long
#define F first
#define S second
#define endl "\n"
#define Endl "\n"

const int sz = 2e5 + 5;
ll n, m, x;

int main() {
#ifdef cloud007
    freopen("in.txt", "r", stdin);
#endif // cloud007
    cloud_007;
    while(cin >> n >> m >> x && (n + m + x)) {
        ll Ans = 0;
        for(int i = 1; i <= n; i++) {
            ll now = (i - 1) * m;
            now += x;
            now /= n;
            Ans += now;
        }
        cout << Ans << endl;
    }


    return 0;
}
