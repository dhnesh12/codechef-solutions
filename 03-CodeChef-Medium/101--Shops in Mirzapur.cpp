// #include <iostream>
// #include <cstdio>
// #include <cstdlib>
// #include <cmath>
// #include <algorithm>
// #include <vector>
// #include <map>
// #include <set>
// #include <bitset>
// #include <queue>
// #include <stack>
// #include <sstream>
// #include <cstring>
// #include <numeric>
// #include <ctime>
// #include <cassert>
#include<bits/stdc++.h>
#ifndef LOCAL_BOBER
#define endl "\n"
#endif
#define re return
#define fi first
#define se second
#define mp make_pair
#define pb emplace_back
#define all(x) (x).begin(), (x).end()
#define sz(x) ((int) (x).size())
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rrep(i, n) for (int i = (n) - 1; i >= 0; i--)
#define y0 y32479
#define y1 y95874
#define next next239
#define prev prev239
#define fill(x, y) memset(x, y, sizeof(x))
#define sqr(x) ((x) * (x))
#define sqrt(x) sqrt(abs(x))
#define unq(x) (x.resize(unique(all(x)) - x.begin()))
#define spc(i,n) " \n"[i == n - 1]
#define ba back()
#define last(x) x[sz(x) - 1]
#define deb(x) cout << #x << " = " << (x) << endl
#define deba(x) do { cout << #x << " (size: " << sz(x) << ") = " << \
	"{"; for (auto o : x) cout << o << ","; cout << "}" << endl;} while (0)
#define fastIO() do {ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);} while (0)
using namespace std;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<string> vs;
typedef long long ll;
typedef pair<ll, ll> pll;
typedef vector<ll> vll;
typedef pair<double, double> pdd;
typedef long double LD;
template<class T> string toString(T x)
{
	ostringstream sout;
	sout << x;
	return sout.str();
}
int nint()
{
	int x;
	scanf("%d", &x);
	re x;
}
const ll mod = 1000000000 + 7;
int m;
int n;
ll ans;
int a[50500], b[50500];
int g;
const int D = 250;
bool f(int x, int y)
{
	re b[x] > b[y];
}
inline ll get(int i, int x)
{
	re (ll)x * a[i] + b[i];
}
int find2(int x, int y)
{
	int l = 0, r = 100500;
	int ans = -1;
	while (l <= r)
	{
		int c = (l + r) / 2;
		if (get(x, c) > get(y, c))
		{
			ans = c;
			r = c - 1;
		}
		else
		l = c + 1;
	}
	re ans;
}
class botva
{
public:
	botva *ne;
	vi v;
	vii pro;
	botva()
	{
		ne = 0;
	}
	void split()
	{
		botva* bu = new botva();
		bu->ne = ne;
		ne = bu;
		int p = sz(v) / 2;
		for (int i = p; i < sz(v); i++)
		bu->v.pb(this->v[i]);
		bu->rebuild();
		v.resize(p);
		rebuild();
	}
	void rebuild()
	{
		pro.clear();
		if (!sz(v))
		re;
		vi u = v;
		sort(all(u), f);
		pro.pb(0, u[0]);
		for (int i = 1; i < sz(u); i++)
		{
			int id = u[i];
			if (a[id] <= a[pro.ba.se])
			continue;
			while (sz(pro))
			{
				int id2 = pro.ba.se;
				int tmp = find2(id, id2);
				if (tmp == -1)
				break;
				if (tmp > pro.ba.fi)
				{
					pro.pb(tmp, id);
					break;
				}
				else
				pro.pop_back();
			}
			if (!sz(pro))
			pro.pb(0, id);
		}
	}
	void remove(int p)
	{
		rotate(&v[p], &v[p + 1], &v[sz(v)]);
		v.pop_back();
		rebuild();
	}
	void add(int p, int x)
	{
		v.push_back(0);
		for (int i = sz(v) - 1; i > p; i--)
		v[i] = v[i - 1];
		assert(p < sz(v));
		v[p] = x;
		if (sz(v) >= 2 * D)
		split();
		else
		rebuild();
	}
	ll getans(int x)
	{
		if (!sz(v))
		re 0;
		int o = (int)(lower_bound(all(pro), mp(x, (int)mod)) - pro.begin());
		o--;
		ll ans = get(pro[o].se, x);
		re ans;
	}
};
botva *root;
botva bb[100500 / D];
void init()
{
	rep(i, n)
	bb[i / D].v.pb(i);
	bb[n / D].v.pb(n);
	rep(i, n / D + 1)
	bb[i].rebuild();
	rep(i, n / D)
	bb[i].ne = &bb[i + 1];
	root = &bb[0];
}
ll getans(int l, int r, int x)
{
	ll ans = 0;
	botva *b = root;
	while (sz(b->v) <= l)
	{
		l -= sz(b->v);
		r -= sz(b->v);
		b = b->ne;
	}
	while (l < sz(b->v) && l <= r)
	{
		ans = max(ans, get(b->v[l], x));
		l++;
	}
	if (l > r)
	re ans;
	while (sz(b->v) <= r)
	{
		ans = max(ans, b->getans(x));
		r -= sz(b->v);
		b = b->ne;
	}
	if (b)
	{
		rep(i, r + 1)
		ans = max(ans, get(b->v[i], x));
	}
	re ans;
}
void shift(int l, int r)
{
	if (l == r)
	re;
	botva *b = root;
	while (sz(b->v) <= l)
	{
		l -= sz(b->v);
		r -= sz(b->v);
		b = b->ne;
	}
	int x = b->v[l];
	b->remove(l);
	while (sz(b->v) <= r)
	{
		r -= sz(b->v);
		b = b->ne;
	}
	b->add(r, x);
}
int main()
{
#ifdef LOCAL_BOBER
	freopen("input.txt", "r", stdin);
	srand(3);
#else
#endif
	fastIO();
	cin >> n;
	rep(i, n)
		cin >> a[i] >> b[i];
	init();
	cin >> m;
	rep(i, m)
	{
		int t;
		cin >> t;
		if (t == 2)
		{
			int l, r, x;
			cin >> l >> r >> x;
			l--;
			r--;
			cout << getans(l, r, x) << endl;
		}
		else
		{
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			shift(l, r);
		}
	}
}