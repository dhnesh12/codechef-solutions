#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
// #define MOD 1000000007LL
#define INF 1000000000000000018LL
#define F first
#define S second
#define ll long long
#define ld long double
#define eps 1e-9

ll gcd(ll a, ll b)
{
	if(a == 0LL)
		return b;
	if(b == 0LL)
		return a;
	return gcd(b, a%b);
}

typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int N = 100005;
ll pre[N], suf[N], pw10[N];
ll MOD;
ll contri[10];
ll mul[10][10];
ll dig[N];

void init(int n)
{
	pw10[0] = 1LL % MOD;
	for(int i = 1; i<=n; i++)
		pw10[i] = (pw10[i-1] * 10LL) % MOD;

	pre[0] = 0LL;
	for(int i = 1; i<=n; i++)
		pre[i] = (dig[i] + pre[i-1]*10LL) % MOD;
	suf[n+1] = 0LL;
	for(int i = n; i>0; i--)
		suf[i] = (pw10[n - i]*dig[i] + suf[i+1]) % MOD;

	for(int i = 1; i<10; i++)
		contri[i] = 0LL;

	return;
}

void contribution(int n)
{
	for(int i = 1; i<=n; i++)
	{
		for(int d = 1; d<10; d++)
		{
			if(d < dig[i])
			{
				contri[d] += (pre[i-1] + 1LL) * ((pw10[n - i] * pw10[n - i]) % MOD);
				contri[d] %= MOD;

				continue;
			}
			if(d == dig[i])
			{
				contri[d] += pre[i-1] * ((pw10[n - i] * pw10[n - i]) % MOD);
				contri[d] %= MOD;

				contri[d] += (suf[i+1] + 1LL) * pw10[n - i];
				contri[d] %= MOD;

				continue;
			}
			else
			{
				contri[d] += pre[i-1] * ((pw10[n - i] * pw10[n - i]) % MOD);
				contri[d] %= MOD;

				continue;
			}
		}
	}
	return;
}

void solve()
{
	string s;
	cin >> s;
	cin >> MOD;
	int n = s.size();

	for(int i = 1; i<=n; i++)
		dig[i] = s[i-1] - '0';
	
	init(n);
	contribution(n);

	/*cout << "pre\n";
	for(int i = 1; i<=n; i++)
		cout << i << " : " << pre[i] << "\n";

	cout << "suf\n";
	for(int i = 1; i<=n; i++)
		cout << i << " : " << suf[i] << "\n";

	cout << "Contri\n";
	for(int i = 1; i<10; i++)
		cout << i << " : " << contri[i] << "\n";*/

	ll ans = 0LL;
	for(int i = 1; i<10; i++)
		for(int j = 1; j<10; j++)
			ans = (ans + mul[i][j] * ((contri[i] * contri[j]) % MOD)) % MOD;

	cout << ans << "\n";

	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	// freopen("in.in", "r", stdin);
	// freopen("out.out", "w", stdout);

	clock_t clk = clock();

	for(int i = 1; i<10; i++)
		for(int j = 1; j<10; j++)
			cin >> mul[i][j];
	
	int t = 1;
	cin >> t;
	for(int tests = 1; tests <= t; tests++)
	{
		// cout << "Case #" << tests << ": ";
		solve();
	}

	clk = clock() - clk;
	cerr << "Time Elapsed: " << fixed << setprecision(10) << ((long double)clk)/CLOCKS_PER_SEC << "\n";

	return 0;
}