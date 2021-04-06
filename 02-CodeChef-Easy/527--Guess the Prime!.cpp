// Sky's the limit :)
#include <bits/stdc++.h>
using namespace std;
#define int long long

/*
    Chinese Remainder Theorem (CRT)
    - https://www.youtube.com/watch?v=H_Utja61nT4 by zeus_orz
    - modInv(x, y) = Modular inverse of x wrt y
      Modular inverse can be found only if GCD(x, y) = 1. 
    
    Given a system of equations:
    x % p(1) = k(1)
    x % p(2) = k(2)
    ...
    x % p(n) = k(n)

    CRT says then if p(1), p(2), .. p(n) are all relatively prime with each other, 
    then we'll have only one solution modulo LCM(p(1), p(2), ..., p(n)) for the given system of equations. 
    
    Proof and solution creation: Garner's Algorithm
    Let's represent x as,
        x = x1 + x2 * p(1) + x3 * p(1) * p(2) + ... + xn * p(1) * p(2) * ... * p(n - 1)

    Now,
        x % p(1) = x(1) = k(1)
        x % p(2) = x(1) + x(2) * p(1) = k(2) => x(2) = (k(2) - k(1)) * modInv(p(1), p(2))
        x % p(3) = x(1) + x(2) * p(1) + x(3) * p(1) * p(2) = k(3) => x(3) = (k(3) - x(1) - x(2) * p(1)) * modInv(p(1), p(3)) * modInv(p(2), p(3))
    
    How to calculate each x(i)?
    x % p(i) = k(i)
    x(1) + x(2) * p(1) + x(3) * p(1) * p(2) + ... + x(i) * p(1) * p(2) * ... * p(i - 1) + 0 + 0 + ... + 0 = k(i) mod p(i)
    res + x(i) * p(1) * p(2) * ... * p(i - 1) = k(i) mod p(i)
    x(i) = (k(i) - res) * modInv(p(1), p(i)) * modInv(p(2), p(i)) * ... * modInv(p(i - 1), p(i))

    Time complexity: n * n * log2(p(max))
*/  

int extended_euclidean(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = extended_euclidean(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int modInv(int a, int m) {
    int x, y;
    int g = extended_euclidean(a, m, x, y);
    if (g != 1) {
        return -1;
    } else {
        x = (x % m + m) % m;
        return x;
    }
}

int CRT(vector<pair<int, int>> v) { 
    int n = v.size();
    int m = 1; // m = p1 * p2 * ... * pn
    for (int i = 0; i < n; i++) {
        m *= v[i].first;
    }   

    int res = 0;
    for (int i = 0; i < n; i++) {
        int t = 1;
        for (int j = 0; j < i; j++) {
            t = t * v[j].first * modInv(v[j].first, v[i].first) % m;
        }
        res = (res + (t * (v[i].second + m - res))) % m;
    }
    return res;
}

int find(vector<int> &pfac) {
    for (int i = 1; ; i++) {
        set<int> st;
        for (auto &p : pfac) {
            st.insert(i * i % p);
        }

        if (st.size() == pfac.size()) {
            return i;
        }
    }
}

void run_case() {
    int x = 32000;
    /*
        x * x % p = k
        k = 0 => p = 2.
        (x * x - k) % p = 0
        p is a prime factor of (x * x - k). Atmax 10 choices
    */

    cout << "1 " << x << endl;
    int k;
    cin >> k;

    // We only care about the prime factors of (x * x - k)
    vector<int> pfac;
    int num = x * x - k, use = 1;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            use *= i;
            pfac.push_back(i);
            while (num % i == 0) {
                num /= i;
            }
        }
    }
    if (num > 1) {
        use *= num;
        pfac.push_back(num);
    }

    // Now how to find a number y such that all y * y % prime factors of use is distinct
    int y = find(pfac);
    cout << "1 " << y << endl;
    cin >> k;

    for (auto &p : pfac) {
        if (y * y % p == k) {
            cout << "2 " << p << endl;
            string s;
            cin >> s;
            return;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    
    int T = 1;
    cin >> T;
    for (int t = 1; t <= T; t++) {
        // cout << "Case #" << t << ": ";
        run_case();
    }
    
    return 0;
}