#include <iostream>
using namespace std;

const long long MOD = 1000000007;

long long
add(long long x, long long y)
{
    long long res = x + y;

    return res >= MOD ? res - MOD : res;
}

long long
mul(long long x, long long y)
{
    long long res = x * y;

    return res >= MOD ? res % MOD : res;
}

long long
sub(long long x, long long y)
{
    long long res = x - y;

    return res < 0 ? res + MOD : res;
}

long long
power(long long x, long long y)
{
    long long res = 1;
    x %= MOD;

    while (y) {
        if (y & 1)
            res = mul(res, x);

        y >>= 1;
        x = mul(x, x);
    }

    return res;
}

long long mod_inv(long long x)
{
    return power(x, MOD - 2);
}

long long
ChefWalkFast(const long long n, const long long k)
{
    if (n == 0) {
        return mul(k, sub(k, 1));
    } else if (k % 2 == 0) {
        const long long kover2m1 = k / 2 - 1;
        const long long result = mul(add(n, kover2m1), add(n, kover2m1) + 1);
        return add(result, n);
    }
    else {
        const long long km1over2 = (k - 1) / 2;
        const long long result = mul(add(n, km1over2), add(n, km1over2) + 1);
        return sub(result, n);
    }
}

int
main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    /*
    for (int n = 0; n < 20; n++) {
        for (int k = 1; k <= 10; k += 1) {
            cout << "n = " << n << " k = " << k << endl;
            const long long slowResult = ChefWalkSlow(n, k);
            const long long fastResult = ChefWalkFast(n, k);
            if (slowResult != fastResult)
                assert(0);
        }
    }
    */

    int t;
    cin >> t;
    while (t-- > 0) {
        long long n, k;
        cin >> n >> k;

        const long long result = ChefWalkFast(n, k);
        cout << result << '\n';
    }

    return 0;
}