// Sometimes, the questions are complicated - and the answers are simple. //
#include<iostream>
#include <bits/stdc++.h>
#define ll long long
#define ld  long double
#define IO ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
const int mod = 998244353;
int T;
string N;
int x, m ;
int fp(int b, int p, int mod) {
    if(p == 0)
        return 1;
    int ans = fp(1LL * b * b % mod, p / 2, mod);
    return p % 2 ? 1LL * ans * b % mod : ans;
}
int getphi(int n) {
    int ans = n;
    for(int i = 2; i * i <= n; i++)
        if(n % i == 0) {
            ans -= ans / i;
            while(n % i == 0)
                n /= i;
        }
    if(n > 1)
        ans -= ans / n;
    return ans;
}
int reducepowr(int mod) {
    ll ans = 0;
    int ph = getphi(mod);
    bool add = false;
    for(auto i : N) {
        ans = ans * 10 + i - '0';
        if(ans > mod) {
            add = true;
            ans %= ph;
        }
    }
    if(add) {
        ans = ans % ph + ph;
    }
    return ans ;
}
int solve(int a, int b, int m) {

    int k = 1, g, add = 0;
    while((g = __gcd(a, m)) > 1) {
        if(b == k)
            return add;
        if(b % g)
            return -1;

        b /= g, m /= g;

        k = 1LL * k * a / g % m;
        add++;
    }
    int n = sqrt(m) + 1;
    int an = 1;
    for(int i = 1; i <= n; i++)
        an = 1LL * an * a % m;

    unordered_map<int, int> vals;
    for(int q = 0, cur = b ; q <= n; q++) {
        vals[cur] = q;
        cur = 1LL * cur * a % m;
    }
    for(int p = 1, cur = k ; p <= n; p++) {
        cur = 1LL * cur * an % m;
        if(vals.count(cur)) {
            return p * n - vals[cur] + add;
        }
    }
    return -1;
}
int main() {
    IO
    cin >> T;
    while(T--) {
        cin >> N >> x >> m;
        int a = (fp(2, reducepowr(m), m) - 1 + m ) % m;
        int b = x % m;
        if(m == 1) {
            cout << "0\n";
            continue;
        }
        if(N.size() == 1 && N[0] == '1') {
            if(x == 1)
                cout << "0\n";
            else
                cout << "-1\n";
            continue;
        }
        if(x == 0) {
            cout << "1\n";
            continue;
        }
        int q = solve(a, b, m);
        if(q == -1) {
            cout << "-1\n";
            continue;
        }
        int B = fp(2, reducepowr(mod) - 1, mod);
        B = 1LL * B * (fp(2, q, mod) - 1) % mod;
        cout << (B + mod) % mod << "\n";
    }
}
