#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define endl "\n"

#define mod 1000000007


int main() {

#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    ios::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);

    ll t;
    cin >> t;

    ll i = 1;

    while (t--)
    {

        ll n;

        cin >> n;

        if (n < 33)
        {

            cout << "Case " << i << ": " << (1LL << n) - 1 << endl;

        }
        else
        {

            cout << "Case " << i << ": " << ((1LL << 33)) - 1 << endl;

        }

        i++;

    }

}