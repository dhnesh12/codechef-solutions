#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int MX = 1e5 + 10;

ll a[MX], psum[MX];

int main()
{
    int t;
    cin >> t;
    while(t--)
    {
        int n, q;
        cin >> n >> q;
        for(int i = 1; i <= n; i++)
            cin >> a[i];
        sort(a+1, a + n + 1);
        for(int i = 1; i <= n; i++)
            psum[i] = a[i] + psum[i-1];
        while(q--)
        {
            ll k;
            cin >> k;
            ll lb = lower_bound(a+1, a+n+1, k) - a - 1;
            ll l = 1, r = lb, idx = lb+1;
            while(l <= r)
            {
                ll m = (l + r) /2;
                ll need = (lb - m + 1) * k - (psum[lb] - psum[m-1]);
                if(need <= m-1) {
                    r = m-1;
                    idx = m;
                    //cout << "X" << endl;
                }
                else
                    l = m + 1;
            }
            cout << n - idx + 1 << endl;
        }
        for(int i = 1; i <= n; i++)
            psum[i] = 0;
    }
}
