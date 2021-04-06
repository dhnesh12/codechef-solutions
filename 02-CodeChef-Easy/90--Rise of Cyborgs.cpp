#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <bitset>
#include <iomanip>
#define ll long long
#define mod 1000000007

// templates
#define all(v) v.begin(),v.end()
#define F first
#define S second
#define sz(x) (int)x.size()
#define ps(x,y)   fixed<<setprecision(y)<<x
#define fo(i,a,b) for(int i=a;i<b;i++)
#define vi vector<int>
#define vl vector<ll>
#define sc(n) scanf("%d",&n)
#define sl(n) scanf("%lld",&n)
#define pr(n) printf("%d\n",n)
#define pl(n) printf("%lld\n",n)
#define prs(n) printf("%d ",n)
#define pls(n) printf("%lld ",n)
using namespace std;

const ll INF = (ll)1e15 + 10;

ll sumSubarray(vl &c, int n) {

	vl left(n), right(n);
	vector<pair<int, int>>s1, s2;

	for (int i = 0; i < n; ++i)
	{
		int cnt = 1;
		while (!s1.empty() && s1.back().F > c[i]) {
			cnt += s1.back().S;
			s1.pop_back();
		}
		s1.push_back({c[i], cnt});
		left[i] = cnt;
	}
	for (int i = n - 1; i >= 0; --i)
	{
		int cnt = 1;
		while (!s2.empty() && s2.back().F >= c[i]) {
			cnt += s2.back().S;
			s2.pop_back();
		}
		s2.push_back({c[i], cnt});
		right[i] = cnt;
	}
	ll res = 0;
	for (int i = 0; i < n; ++i)
	{
		res = (res + (c[i] * left[i] * right[i]));
	}
	return res;
}

void solve()
{
	int n, m;
	sc(n), sc(m);
	vl a(n);
	vi b(m);
	vl c;
	ll ans = 0;
	for (int i = 0; i < n; ++i)
	{
		sl(a[i]);
	}
	for (int i = 0; i < m; ++i)
	{
		sc(b[i]);
		b[i] -= 1;
		ans += a[b[i]];
	}
	for (int i = 0; i < m - 1; ++i)
	{
		int l = b[i], r = b[i + 1];
		ll mn = INF;
		for (int j = l; j <= r; ++j)
		{
			mn = min(mn, a[j]);
		}
		c.push_back(mn);
	}
	ans += sumSubarray(c, sz(c));
	pl(ans);
}

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t = 1;
	scanf("%d", &t);
	while (t--) {
		solve();
	}
}