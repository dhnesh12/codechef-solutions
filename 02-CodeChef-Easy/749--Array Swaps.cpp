#include "bits/stdc++.h"
using namespace std;
#define ll long long

int main()
{
    ll n, m;
    cin >> n >> m;
    ll a[n + 1];
    ll b[m + 1];

    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < m; i++)
        cin >> b[i];

    sort(a, a + n);
    ll cnt = 0;
    for (int i = 0; i < m; i++)
    {
        if (b[i] < a[0])
        {
            cnt = cnt + n;
        }
    }

    cout << cnt << "\n";
}
