#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> ii;
typedef long long ll;

const int Maxm = 1 << 22;
const int mod1 = 1000000007;
const int mod2 = 1000000009;
const int arg1 = 37;
const int arg2 = 1000007;

int pw1[Maxm], pw2[Maxm];
int bits[Maxm];
ii H[Maxm];
int t;
int n;
int vals[Maxm];
int res[Maxm];

ii Add(const ii &h, int val)
{
    return ii((ll(h.first) * arg1 + ll(val + 1)) % mod1,
              (ll(h.second) * arg2 + ll(val + 1)) % mod2);
}

ii getHash(int l, int r)
{
    ii res = H[r];
    l--;
    if (l >= 0) {
        res.first = (ll(res.first) - ll(pw1[r - l]) * H[l].first % mod1 + mod1) % mod1;
        res.second = (ll(res.second) - ll(pw2[r - l]) * H[l].second % mod2 + mod2) % mod2;
    }
    return res;
}

int main()
{
    ii cur = ii(0, 0);
    for (int i = 0; i < Maxm; i++) {
        bits[i] = __builtin_popcount(i) % 2;
        cur = Add(cur, bits[i]);
        H[i] = cur;
    }
    pw1[0] = pw2[0] = 1;
    for (int i = 1; i < Maxm; i++) {
        pw1[i] = ll(pw1[i - 1]) * arg1 % mod1;
        pw2[i] = ll(pw2[i - 1]) * arg2 % mod2;
    }
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int pnt = -1;
        ii h = ii(0, 0);
        for (int i = 0; i < n; i++) {
            scanf("%d", &vals[i]);
            h = Add(h, vals[i]);
            pnt++;
            while (pnt < Maxm && getHash(pnt - i, pnt) != h) pnt++;
            printf("%d%c", pnt < Maxm? pnt - i: -1, i + 1 < n? ' ': '\n');
        }
    }
    return 0;
}
