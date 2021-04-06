#include <iostream>
using namespace std;

// from Binary GCD algorithm in Wikipedia
unsigned int gcd(unsigned int u, unsigned int v)
{
    // simple cases (termination)
    if (u == v)
        return u;

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    // look for factors of 2
    if (~u & 1) // u is even
        if (v & 1) // v is odd
            return gcd(u >> 1, v);
        else // both u and v are even
            return gcd(u >> 1, v >> 1) << 1;

    if (~v & 1) // u is odd, v is even
        return gcd(u, v >> 1);

    // reduce larger argument
    if (u > v)
        return gcd(u - v, v);

    return gcd(v - u, u);
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
        long long n;
        cin >> n;

        // figure out the GCD of the whole array
        unsigned int arrayGCD = 0;
        for (long long i = 0; i < n; i++) {
            unsigned int ai;
            cin >> ai;
            if (i == 0)
                arrayGCD = ai;
            else
                arrayGCD = gcd(arrayGCD, ai);
        }

        long long result = n * (long long)arrayGCD;

        cout << result << '\n';
    }
    return 0;
}