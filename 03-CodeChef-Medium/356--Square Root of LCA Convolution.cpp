#include <bits/stdc++.h>
using namespace std;

#define fio                           \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0)

#define endl "\n"
#define setbits(x) __builtin_popcountll(x)
#define PI 3.141592653589793
#define MOD 998244353
#define ff first
#define ss second
typedef long long int ll;
typedef unsigned long long int ull;

/* tonelli-shanks */
ull modpow(ull a, ull b, ull n)
{
	ull x = 1, y = a;
	while (b > 0)
	{
		if (b % 2 == 1)
			x = (x * y) % n; 

		y = (y * y) % n; 
		b /= 2;
	}
	return x % n;
}

class tsobj
{
public:
	ull root1, root2;
	bool exists;

    tsobj(ull root1, ull root2, bool exists): root1(root1), root2(root2), exists(exists) {}
};

tsobj ts(ull n, ull p)
{
	ull q = p - 1;
	ull ss = 0;
	ull z = 2;
	ull c, r, t, m;

	if (modpow(n, (p - 1) / 2, p) != 1)
		return tsobj(0, 0, false);

	while ((q & 1) == 0)
	{
		ss += 1;
		q >>= 1;
	}

	if (ss == 1)
	{
		ull r1 = modpow(n, (p + 1) / 4, p);
		return tsobj(r1, p - r1, true);
	}

	while (modpow(z, (p - 1) / 2, p) != p - 1)
		z++;

	c = modpow(z, q, p);
	r = modpow(n, (q + 1) / 2, p);
	t = modpow(n, q, p);
	m = ss;

	while (true)
	{
		ull i = 0, zz = t;
        ull b = c, e;

		if (t == 1)
			return tsobj(r, p - r, true);

		while (zz != 1 && i < (m - 1))
		{
			zz = zz * zz % p;
			i++;
		}

		e = m - i - 1;
		while (e > 0)
		{
			b = b * b % p;
			e--;
		}

		r = r * b % p;
		c = b * b % p;
		t = t * c % p;
		m = i;
	}
}

ll check(ull n, ull p)
{
	tsobj sol = ts(n, p);
	if (sol.exists)
		return sol.root1;
	return -1;
}

/* ---------- */


int main() {
    fio;

    #ifndef ONLINE_JUDGE 
    freopen("input.txt", "r", stdin); 
    freopen("output.txt", "w", stdout); 
    #endif

    int t;
    cin >> t;
    while(t--) {
        ll n, p, parent;
        cin >> n >> p;

        vector<vector<ll>> v(n+1);
        for(int i = 2; i <= n; i++) {
            cin >> parent;
            v[parent].push_back(i);
        }

        vector<ll> store(n+1), ans(n+1);

        vector<ll> c(n+1);
        for(int i = 1; i <= n; i++) 
            cin >> c[i];

        ll total = 1;
        bool badcase = 0;
        for(int i = n; i >= 1; i--) {
            ll D = c[i];
            ll b = 0;
            for(auto& j: v[i]) {
                store[i] = (store[i] + store[j] + p)%p;
                D = (D + (store[j]*1ll*store[j]) + p)%p;
            }

            ll fromts = check(D, p);
            b = -1ll*store[i];

            if(D == 0) {
                ans[i] = (b + p)%p;
            } else if(fromts == -1) {
                badcase = 1;
                break;
            } else {
                total = (total*2ll)%MOD;
                ans[i] = (b + fromts + p)%p;
            }

            store[i] = (store[i] + ans[i] + p)%p;
        }

        if(badcase) {
            cout << 0 << endl;
            cout << -1 << endl;
        } else {
            cout << total << endl;
            for(int i = 1; i <= n; i++)
                cout << ans[i] << " ";
            cout << endl;
        }
    }

    return 0;
}