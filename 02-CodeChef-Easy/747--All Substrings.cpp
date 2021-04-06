#include<bits/stdc++.h>
using namespace std;
#define fastIO ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL)
typedef long long int lli;
typedef long long int ll;
typedef long double ld;
typedef pair<ll, ll> pll;
typedef vector<pll> vop;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<int> vi;
typedef pair<int, int> pii;
#define REP(i,a,b) for( long long i=a;i<b;i++)
#define REPR(i,a,b) for(long long i=a;i>=b;i--)
#define adb(a) for(auto ii:a) cout << ii << " "; cout << endl
#define adp(a) for(auto ii:a) cout << ii.F << " " << ii.S << endl;
#define PB push_back
#define MP make_pair
#define F first
#define S second
#define all(x) (x).begin(),(x).end()
#define endl "\n"
#define mem(a,b) memset(a,b,sizeof(a))
#define mod 1000000007
#define PI 3.14159265358979323846
const ll MAXN = 1000001;
//const ll p = 1000000007;
#define N 200005
#define INF INTMAX_MAX

struct hash_pair {
	template <class T1, class T2>
	size_t operator()(const pair<T1, T2>& p) const
	{
		auto hash1 = hash<T1> {}(p.first);
		auto hash2 = hash<T2> {}(p.second);
		return hash1 ^ hash2;
	}
};
struct cmp
{
	bool operator()(const pll &a, const pll &b)
	{
		if (a.F == b.F) return a.S > b.S;
		return a.F > b.F;
	}
};

ll dx[] = {1, -1, 0, 0};
ll dy[] = {0, 0, 1, -1};

ll power(ll a, ll b, ll m) { ll ans = 1; a = a % m; while (b) { if (b & 1) ans = (ans * a) % m; b /= 2; a = (a * a) % m; } return ans; }

ll lcm(ll a, ll b) { return (a * b) / __gcd(a, b); }

ll modInverse(ll a, ll m) { ll g = __gcd(a, m); return power(a, m - 2, m); }

// bool check(ll i, ll j)
// {
//     if (i >= 0 && i < n && j >= 0 && j < m && a[i][j] != '#')
//         return true;
//     return false;
// }
// ll nCrModPFermat(ll n, ll r, ll p)
// {
//     if (n < r)
//         return 0;
//     if (r == 0)
//         return 1;
//     return (fac[n] * modInverse(fac[r], p) % p * modInverse(fac[n - r], p) % p) % p;
// }

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	fastIO;
	int test = 1, num = 1;
	cin >> test;
	while (test--)
	{
		string s, t;
		cin >> s >> t;
		ll c[26] = {0}, d[26] = {0};
		REP(i, 0, s.size()) c[s[i] - 'a']++;
		REP(i, 0, t.size()) d[t[i] - 'a']++;
		int f = 0;
		REP(i, 0, 26)
		{
			if (d[i] < c[i]) {
				f = 1;
				cout << "Impossible\n";
				break;
			}
			d[i] -= c[i];
		}
		if (f) continue;
		string ans = "", x = "";
		REP(i, 0, 26)
		{
			REP(j, 0, d[i]) ans += char(i + 'a');
		}
		//cout << ans << endl;
		REP(i, 0, ans.size())
		{
			if (!f && ans[i] > s[0]) {
				x += s;
				f = 1;
			}
			x += ans[i];
		}
		if (x.size() < t.size()) x += s;
		string y = "";
		f = 0;
		REP(i, 0, ans.size())
		{
			if (!f && ans[i] >= s[0]) {
				y += s;
				f = 1;
			}
			y += ans[i];
		}
		if (y.size() < t.size()) y += s;
		//cout << x << " " << y << endl;
		cout << min(x, y) << endl;
	}
	return 0;
}
