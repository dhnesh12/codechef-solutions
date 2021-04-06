 #include <bits/stdc++.h>

using namespace std;

using ll = long long;
using vll = vector<ll>;
using vii = vector<int>;
using pii = pair<int, int>;
template <typename T = vii>
using vec = vector<T>;

const ll INF = 1e18, MOD = 1e9 + 9;

const int MAX = 1e6;

struct S {
    static const ll  A = 1e9 + 7, B = 1e9 + 9;
    static const ll PA = 31, PIA = 129032259;
    static const ll PB = 37, PIB = 297297300;
    
    int n;
    string s;
    vll hA;
    vll ppA, piA;

    vll hB;
    vll ppB, piB;
    S(string const& s) : n(s.size()), s(s), hA(n + 1), ppA(n + 1), piA(n + 1), hB(n + 1), ppB(n + 1), piB(n + 1) {
        ppA[0] = piA[0] = 1;
        ppB[0] = piB[0] = 1;
        for (int i = 0; i < n; i++) {
            ppA[i + 1] = (ppA[i] * PA) % A;
            piA[i + 1] = (piA[i] * PIA) % A;
            hA[i + 1] = (hA[i] + (s[i] - 'a' + 1) * ppA[i]) % A;
            
            ppB[i + 1] = (ppB[i] * PB) % B;
            piB[i + 1] = (piB[i] * PIB) % B;
            hB[i + 1] = (hB[i] + (s[i] - 'a' + 1) * ppB[i]) % B;
        }
    }
 
    pair<ll, ll> get_dhash(const int i, const int len) {
        const ll resa = (hA[i + len] + A - hA[i]) % A;
        const ll resb = (hB[i + len] + B - hB[i]) % B;
        return {(resa * piA[i]) % A, (resb * piB[i]) % B};
    }

    ll get_hash(const int i, const int len) {
        return get_dhash(i, len).first;
    }
};



int main() {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    int test;
    cin >> test;
    while (test--) {
        int n, m, k;
        cin >> n >> m >> k;
        string a, b;
        cin >> a >> b;
        S sa(a), sb(b);
        map<pair<ll, ll>, int> cnta, cntb;
        for (int i = 0; i + k <= n; i++) {
            cnta[sa.get_dhash(i, k)]++;
        }
        for (int i = 0; i + k <= m; i++) {
            cntb[sb.get_dhash(i, k)]++;
        }
        int cnt = 0;
        for (auto& p : cnta) {
            p.second = min(p.second, cntb[p.first]);
            cnt = max(cnt, p.second);
        }
        if (cnt == 0) {
            cout << "-1\n";
            continue;
        }
        int res = -1;
        for (int i = 0; i + k <= n; i++) {
            const auto h = sa.get_dhash(i, k);
            if (cnta[h] != cnt) continue;
            if (res != -1) {
                if (sa.get_dhash(res, k) == h) continue;
                int lo = 0, hi = k + 1;
                while (lo + 1 < hi) {
                    const int mid = (lo + hi) / 2;
                    if (sa.get_dhash(res, mid) == sa.get_dhash(i, mid)) lo = mid;
                    else hi = mid;
                }
                if (lo < k and a[i + lo] < a[res + lo]) res = i;
            }
            else res = i;
        }
        cout << a.substr(res, k) << '\n';
    }
}