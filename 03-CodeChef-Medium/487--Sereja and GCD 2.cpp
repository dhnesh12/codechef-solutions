#include<bits/stdc++.h>
using namespace std;
typedef vector< int >VI;
const int MOD = 1e9+7;

int sum(int a, int b) {
    return a + b >= MOD ? a + b - MOD : a + b;
}
int sub(int a, int b) {
    return a - b < 0 ? a - b + MOD : a - b;
}
int mul(int a, int b) {
    return (1LL*a*b)%MOD;
}
int pw(int a, int b) {
	if (!b) return 1;
	int r = pw(a, b/2);
	r = mul(r, r);
	if (b%2) r = mul(r, a);
	return r;
}

int factors[109];
vector< int >primes;

const int MAXN = 200007;
int fact[MAXN], ifact[MAXN];

void pre() {
    for (int p = 2; p <= 100; p++) {
        bool ok = true;
        for (int i = 2; i*i <= p; i++) {
            if (p%i==0) {
                ok = false;
                break;
            }
        }
        if (ok) primes.push_back(p);
    }
    for (int p = 2; p <= 100; p++) {
        for (int i = 0; i < primes.size(); i++) {
            if (p%primes[i]==0) {
                factors[p] |= 1<<i;
            }
        }
    }

    fact[0] = 1;
    for (int i = 1; i < MAXN; i++) fact[i] = mul(i, fact[i-1]);

    ifact[MAXN-1] = pw(fact[MAXN-1], MOD-2);
    for (int i = MAXN-2; i >= 0; i--) ifact[i] = mul(i+1, ifact[i+1]);
}

ostream &operator<<(ostream &out, const VI &v) {
    for (int x : v) out << " " << x;
    return out;
}

map< int , VI >dp[103];

VI solve(int m, int forbidden) {
    for (int i = primes.size()-1; i >= 0 && primes[i] > m; i--) {
        if (forbidden&(1<<i)) forbidden ^= 1<<i;
    }

    auto it = dp[m].find(forbidden);
    if (it != dp[m].end()) return it->second;

    VI rt(m+1, 0);
    if (m==1) {
        rt[0] = 1;
        return rt;
    }

    VI tmp = solve(m-1, forbidden);
    for (int i = 0; i < m; i++) rt[i] = sum(rt[i], tmp[i]);

    if ((forbidden&factors[m]) == 0) {
        tmp = solve(m-1, forbidden|factors[m]);
        for (int i = 0; i < m; i++) rt[i+1] = sum(rt[i+1], tmp[i]);
    }

//    cout << "dp[" << m << "][" << bitset<4>(forbidden) << "] =" << rt << endl;
    return dp[m][forbidden] = rt;
}


int main() {
    pre();

    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        VI ways = solve(m, 0);
//        for (int i = 0; i <= m; i++) {
//            cout << "ways[" << i << "] = " << ways[i] << endl;
//        }

        int ans = 0;
        for (int sz = 0; sz <= m && sz <= n; sz++) {
            ans = sum(ans, mul(ways[sz], mul(fact[n], ifact[n-sz])));
        }

        cout << ans << endl;
    }



    return 0;
}
