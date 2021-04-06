//keep trying :)
#include <bits/stdc++.h>
#define int long long
#define float long double
#define ll long long
#define PB push_back
#define MP make_pair
#define ss second
#define ff first
#define PI 3.1415926535897932384
#define inf 1e18
#define fastrack ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;
const int M = 3e5 + 7, K = (1 << 10) + 7, mod = 1000000007;
 
int power(int x, int y){
    int res = 1;
    x = x % mod;
    if (x == 0) return 0;
    while (y > 0){
        if (y & 1)
            res = (res*x) % mod;
        y = y>>1;
        x = (x*x) % mod;
    }
    return res;
}

int ad(int a, int b){
    return((a % mod + b % mod) % mod);
}
int sub(int a, int b){
    return((a % mod - b % mod + mod) % mod);
}
int mul(int a, int b){
    return(((a % mod) * (b % mod)) % mod);
}
int divi(int a, int b){
    return(mul(a, power(b, mod - 2)) % mod);
}

int ncr(int n, int r){
    int ans1 = 1, ans2 = 1;
    while(n != 0 and r != 0){
        ans1 = (ans1 * n)%mod;
        ans2 = (ans2 * r)%mod;
        n--; r--;
    } 
    return divi(ans1, ans2);
}


signed main(){
    fastrack;
    int tt; cin >> tt; while(tt--)
    {
        int n, m;
        cin >> n >> m;
        int a[n + 5] = {};
        for(int i = 1; i < n; i++){
            cin >> a[i];
        }
        sort(a + 1, a + n);
        int cnt = 0, ok = 1;
        std::vector<int> v, v1;
        for(int i = 1; i < n; i++){
           if(a[i] != a[i + 1]){
                cnt++;
                v1.PB(a[i]);
                v.PB(cnt);
                cnt = 0;
            }
            else
                cnt++;
        }
        for(int i = 1; i < v1.size(); i++){
            if(v1[i] != v1[i - 1] + 1)
                ok = 0;
        }
        if(v1[0] != 1){
            ok = 0;
        }
        if(!ok){
            cout << 0 << "\n";
            continue;
        }
        int ans = 1;
        m -= v[0];
        for(int i = 1; i < v.size(); i++){
            ans = (ans * power(v[i - 1], v[i]))%mod;
            m -= v[i];
        }
        if(m < 0){
            cout << 0 << "\n";
            continue;
        }
        if(m == 0){
            cout << ans << "\n";
            continue;
        }
        int edge = 0;
        for(auto u : v){
            edge += (u * (u - 1))/2;
        }
        if(edge < m){
            cout << 0 << "\n";
            continue;
        }
        cout << (ans * ncr(edge, m))%mod << "\n";
    }
    return 0;
}