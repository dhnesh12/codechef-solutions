#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <algorithm>
#include <cmath>
#include <string>
#include <cstring>
#include <set>
#include <queue>
#include <unordered_set>
#include <complex>
#include <unordered_map>
#include <bitset>
#include <ctime>
#include <cassert>
#include <random>
#include <iomanip>

#ifdef ONPC
    #define deb(a) cerr << "       " << #a << " = " << a << endl;
#else
    #define deb(a)
#endif

using namespace std;

mt19937 rnd(time(0));

typedef long long ll;
typedef long double ld;

ll MOD;

ll binpow(ll a, ll b)
{
	ll res = 1;
	while (b)
		if (b & 1)
		{
            res = (res * a) % MOD;
            b--;
        }
		else
		{
            a = (a * a) % MOD;
            b >>= 1;
        }
	return res;
}
 
ll root()
{
	vector<ll> fact;
	int phi = MOD - 1, n = phi;
	for (int i = 2; i * i <= n; i++)
		if (n % i == 0)
        {
			fact.push_back(i);
			while (n % i == 0)
				n /= i;
		}
	if (n > 1)
		fact.push_back(n); 
	for (int res = 2; res <= MOD; res++)
    {
		bool ok = true;
		for (int i = 0; i < fact.size() && ok; i++)
			ok &= (binpow(res, phi / fact[i]) != 1);
		if (ok)
            return res;
	}
	return -1;
}


vector<int> dp, dp2;

int solve()
{
    ll n;
    if (!(cin >> n))
        return 1;
    ll m, f;
    cin >> m >> f;
    MOD = m;
    vector<ll> a;
    if (f == 0)
    {
        int cnt = 0;
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            if (x == 0)
                cnt++;
        }
        cout << cnt << '\n';
        return 0;
    }
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        if (x > 1)
            a.push_back(x);
    }
    ll g = root();
    vector<int> st(m, -1);
    for (int i = 0, cur = 1; i < m - 1; i++, cur = (cur * g) % MOD)
        st[cur] = i;
    n = a.size();
    for (int i = 0; i < n; i++)
        a[i] = st[a[i]];
    vector<int> pr;
    ll cnt = m - 1;
    for (ll i = 2; i * i <= cnt; i++)
        if (cnt % i == 0)
        {
            pr.push_back(i);
            while (cnt % i == 0)
                cnt /= i;
        }
    f = st[f];
    if (cnt > 1)
        pr.push_back(cnt);
    int t = pr.size(), B = (1 << t);
    dp.assign(B, 0);
    vector<int> al(t, 0);
    for (int i = 0; i < t; i++)
    {
        int x = f;
        while (x % pr[i] == 0)
        {
            x /= pr[i];
            al[i]++;
        }
    }
    vector<int> b(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < t; j++)
        {
            int x = a[i];
            int cnt = 0;
            while (x % pr[j] == 0)
            {
                x /= pr[j];
                cnt++;
            }
            if (cnt <= al[j])
                b[i] |= (1 << j);
        }
    }
    int tmp = 0;
    for (int j = 0; j < t; j++)
    {
        int x = m - 1;
        int cnt = 0;
        while (x % pr[j] == 0)
        {
            x /= pr[j];
            cnt++;
        }
        if (cnt <= al[j])
            tmp |= (1 << j);
    }
    for (int i = 0; i < n; i++)
        b[i] |= tmp;
    for (int i = 0; i < n; i++)
    {
        dp2 = dp;
        for (int j = 0; j < B; j++)
            dp2[j | b[i]] = max(dp2[j | b[i]], dp[j] + 1);
        dp = dp2;
    }
    int ans = 0;
    for (int i = 0; i < B - 1; i++)
        ans = max(ans, dp[i]);
    cout << n - ans << '\n';
    return 0;
}

int32_t main()
{
    #ifdef ONPC
        freopen("in.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    int T = 100;
    cin >> T;
    for (int i = 1; i <= T; i++)
    {
        #ifdef ONPC
            cout << "Test #" << i << ":\n";
        #endif
        if (solve())
            break;
        #ifdef ONPC
            cout << "__________________________\n";
        #endif
    }
    #ifdef ONPC
        cerr << endl << "finished in " << clock() * 1000LL / CLOCKS_PER_SEC << " ms" << endl;
    #endif
    return 0;
}

