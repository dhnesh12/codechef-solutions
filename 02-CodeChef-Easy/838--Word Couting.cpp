#include <iostream>
#include <vector>
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
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int t;
    cin >> t;
    while (t-- > 0) {
        string s;
        cin >> s;

        // count the occurrences of each distinct character
        vector<int> occurrences(128, 0);
        for (size_t i = 0; i < s.length(); i++) {
            occurrences[s[i]]++;
        }

        // work out the factorial of string length
        long long result = 1;
        for (int i = 2; i <= int(s.length()); i++) {
            result = mul(result, (long long)i);
        }

        // divide by any the factorial of any multiple occurrences
        for (size_t i = 0; i < occurrences.size(); i++) {
            if (occurrences[i] > 1) {
                long long of = 1;
                for (int j = 2; j <= occurrences[i]; j++) {
                    of = mul(of, (long long)j);
                }

                result = mul(result, mod_inv(of));
            }
        }

        cout << result << '\n';
    }
    return 0;
}
