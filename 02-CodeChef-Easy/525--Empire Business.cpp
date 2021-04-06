#include<bits/stdc++.h>

using namespace std;

#define endl "\n"


#define mod 1000000007
#define num 1000007

#define ll long long


int main()
{

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t;
    cin >> t;

    while (t--)
    {

        ll n;
        cin >> n;

        ll i;

        ll arr[n + 1];
        arr[0] = 0;

        for (i = 1; i <= n; i++)
            cin >> arr[i];

        ll ldp[n + 1], rdp[n + 1];

        ldp[1] = arr[1], rdp[n] = arr[n];

        for (i = 2; i <= n; i++)
            ldp[i] = min(ldp[i - 1] + 1, arr[i]);

        for (i = n - 1; i >= 1; i--)
            rdp[i] = min(rdp[i + 1] + 1, arr[i]);

        for (i = 1; i <= n; i++)
            cout << min(ldp[i], rdp[i]) << " ";

        cout << endl;

    }

}
