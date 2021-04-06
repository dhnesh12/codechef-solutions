#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ull unsigned long long
#define f(i, s, e) for (int i = s; i < e; ++i)

ll gcd(ll a, ll b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}

main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t, n;
    cin >> t;
    while (t--)
    {
        ll temp, g = 0;
        cin>>n;
        while(n--) {
            cin>>temp;
            g = gcd(temp, g);
        }
        cout<<g<<'\n';
    }
}