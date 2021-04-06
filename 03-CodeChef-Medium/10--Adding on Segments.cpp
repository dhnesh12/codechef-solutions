#include <bits/stdc++.h>
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include<cassert>
#include<algorithm>
#include<random>
#include<map>
#include<set>
#include <bitset>
#include<queue>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<char> vc;
typedef vector<string> vs;
typedef vector<vector<int>> vvi;
typedef vector<vector<char>> vvc;
typedef vector<vector<ll>> vvl;
typedef vector<pair<ll, ll>> vpll;
typedef vector<pair<ld, ld>> vpld;
typedef vector<pair<int, int>> vpi;
typedef pair<ld, ld> pld;
#define mp make_pair
#define pb push_back

int mod = 998244353;
//int mod = 1e9 + 7;

int sum(int a, int b)
{
	int c = a + b;
	if (c >= mod)
	{
		c -= mod;
	}
	return c;
}

int dif(int a, int b)
{
	int c = a - b;
	if (c < 0)
	{
		c += mod;
	}
	return c;
}

int mlt(int a, int b)
{
	ll c = a * 1LL * b;
	return c % mod;
}

int ibit(int n, int i)
{
	return ((n >> i) & 1);
}

void outp1(vl &ou, string s = " ")
{
	cerr << s << endl;
	for (int i = 0; i < ou.size(); i++)
	{
		cerr << ou[i] << ' ';
	}
	cerr << endl;
}

void outp1(vi &ou, string s = " ")
{
	cerr << s << endl;
	for (int i = 0; i < ou.size(); i++)
	{
		cerr << ou[i] << ' ';
	}
	cerr << endl;
}

void outp2(vector<vector<int>> &ou, string s = " ")
{
	cerr << s << endl;
	for (int i = 0; i < ou.size(); i++)
	{
		for (int j = 0; j < ou[i].size(); j++)
		{
			cerr << ou[i][j] << ' ';
		}
		cerr << '\n';
	}
}

int bp(int x, int y)
{
	if (y == 0)
	{
		return 1;
	}
	int a = 0;
	if (!(y % 2))
	{
		a = bp(x, y / 2);
	}
	return (y % 2) ? mlt(bp(x, y - 1), x) : mlt(a, a);
}

int obr(int x)
{
	return bp(x, mod - 2);
}

const int maxn = 301;
int fact[maxn], ofact[maxn];

void prec()
{
	fact[0] = 1;
	ofact[0] = 1;
	for (int i = 1; i < maxn; i++)
	{
		fact[i] = mlt(fact[i - 1], i);
	}
	//cerr << "sdsds" << endl;
	ofact[maxn - 1] = obr(fact[maxn - 1]);
	for (int i = maxn - 2; i > 0; i--)
	{
		ofact[i] = mlt(ofact[i + 1], i + 1);
	}
}

int c(int a, int b)
{
	return ((a <= b) && (a >= 0)) ? mlt(fact[b], mlt(ofact[a], ofact[b - a])) : 0;
}

int gcd(int a, int b)
{
	if (b > a)
		return gcd(b, a);
	if (b == 0)
		return a;
	return gcd(b, a % b);
}

bool solve(istream &cin = std::cin, ostream &cout = std::cout)
{
	int n;
	cin >> n;
	vector<int> a(n), b(n + 1), d(n + 1), g(n + 1);
	for (int i = 0; i < n; i++)
		cin >> a[i];
	for (int i = 1; i <= n; i++)
		cin >> b[i];
	for (int i = 1; i <= n; i++)
	{
		if (n % i == 0)
		{
			for (int j = 1; j <= n; j++)
			{
				if (j % i == 0)
				{
					int val = (j / i) * b[j];
					g[i] = gcd(g[i], val);
				}
				else
				{
					d[i] = gcd(d[i], b[j]);
				}
			}
			g[i] = gcd(g[i], d[i]);
		//	cerr<<i<<' '<<g[i]<<' '<<d[i]<<endl;
			vector<int> v;
			for (int j = 0; j < i; j++)
			{
				int val = 0;
				for (int h = j; h < n; h+=i)
					val += a[h];
				v.push_back(val);
			}
			for (int j = 0; j < v.size(); j++)
			{
				if (g[i] == 0)
					if (v[j] != 0)
						return false;
				if (g[i] != 0)
					if (v[j] % g[i] != 0)
						return false;
			}
			for (int j = 0; j < v.size() - 1; j++)
			{
				if (d[i] == 0)
					if (v[j] != v[j+1])
						return false;
				if (d[i] != 0)
					if (v[j] % d[i] != v[j+1]%d[i])
						return false;
			}
		}
	}
	return true;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	int tests = 1;
	cin >> tests;
	for (int i = 0; i < tests; i++)
	{
		if (solve())
			cout << "YES" << '\n';
		else
			cout << "NO" << '\n';
	}
}