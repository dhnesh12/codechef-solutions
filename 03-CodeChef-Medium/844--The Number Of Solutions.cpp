#include <bits/stdc++.h>
using namespace std;

int du (int a, int b, int n)
{
    if (b == 0) return 1;
    if (b % 2 == 0)
        return du ((a % n) * (a % n), b / 2, n) % n;
    else return (du ((a % n) * (a % n), b / 2, n) * (a % n)) %n;
}

int t, u, d, n, m;
const long long mod = 1000000007;
int i, x, y, z;

int main()
{
    //freopen ("cntsols.inp", "r", stdin);
    //freopen ("cntsols.out", "w", stdout);
    //cout << du (5, 8, 7);
    cin >> t;
    for (i = 1; i <= t; i++)
    {
        cin >> u >> d >> m >> n;
        long long kq = 0;
        for (x = 0; x < n; x++)
            for (y = 0; y < n; y++)
                for (z = 0; z < n; z++)
                {
                    long long sodu = (du (x, d, n) + du (y, d, n) + du (z, d, n)) % n;
                    if (sodu == m)
                    {
                        int sox = 0, soy = 0, soz = 0;
                        sox = soy = soz = u / n;
                        if (x <= u % n) sox++;
                        if (y <= u % n) soy++;
                        if (z <= u % n) soz++;
                        kq = (kq + (((sox % mod) * (soy % mod)) % mod * (soz % mod)) % mod) % mod;
                        //kq = kq + sox * soy * soz;
                    }
                }
        cout << kq % mod << '\n';
    }
    return 0;
}
