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

int
main()
{
    int t;
    cin >> t;
    while (t-- > 0) {
        long long n;
        cin >> n;

        const bool nodd = n % 2 != 0;
        if (nodd)
            n--;
        n /= 2;

        // calculate the sum of the geometric series
        long long numerator = power(26, n + 1);
        numerator = sub(numerator, 1);
        numerator = mul(numerator, 2);

        long long denominatorInverse = mod_inv(25);
        long long result = mul(numerator, denominatorInverse);
        result = sub(result, 2);

        if (nodd) {
            long long lastTerm = power(26, n + 1);
            result = add(result, lastTerm);
        }

        cout << result << '\n';
    }
}