#include <iostream>
using namespace std;

typedef long long ll;

const ll mod = 1000000007;
ll M, R;

ll add(ll a, ll b) {
    return (a + b) % mod;
}

ll sub(ll a, ll b) {
    return add(a, mod - b);
}

ll mult(ll a, ll b) {
    a %= mod; b %= mod;
    return a * b % mod;
}

ll expo(ll a, ll p) {
    a %= mod;
    ll ret = 1;
    for(; p; p /= 2) {
        if(p & 1) ret = mult(ret, a);
        a = mult(a, a);
    }

    return ret;
}

ll inv(ll a) {
    return expo(a, mod - 2);
}

ll divide(ll a, ll b) {
    a %= mod; b %= mod;
    return mult(a, inv(b));
}

int main() {
    int t;
    cin >> t;
    while(t--) {
        cin >> M >> R;

        //See editorials for more details. The answer is 
        //(M^R - 1) / (M - 1) - R
        ll ans = sub(expo(M, R), 1);
        ans = divide(ans, sub(M, 1));
        ans = (ans+(mod-R))%mod;

        cout << ans << endl;
    }
    
	return 0;
}