#include <bits/stdc++.h>

using namespace std;

using ll = long long;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    vector<ll> a(n+1);
    for(int i = n; i >= 0; i--)
    {
        cin>>a[i];
    }
    int q;
    cin>>q;
    while(q--)
    {
        ll x;
        cin>>x;
        ll r = 0;
        for(auto &i : a)
        {
            r *= x;
            r += i;
            r %= 786433;
        }
        cout<<r<<'\n';
    }
    return 0;
}
