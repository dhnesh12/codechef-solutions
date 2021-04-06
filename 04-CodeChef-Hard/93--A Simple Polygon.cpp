#include <bits/stdc++.h>
using namespace std;

#define mp make_pair
#define pb push_back
#define MOD 1000000007LL
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

const int N = 50005;
const int K = 500;
ll X[N], Y[N];

int k;
vector<pii> segs;

ll cross(int a, int b, int c)
{
	ll x1 = X[b] - X[a];
	ll y1 = Y[b] - Y[a];
	ll x2 = X[c] - X[a];
	ll y2 = Y[c] - Y[a];

	return (x1*y2 - x2*y1);
}

ll area(vector<int> P)
{
	ll ans = 0LL;
	for(int i = 2; i<P.size(); i++)
		ans += cross(P[0], P[i-1], P[i]);
	return ans;
}

bool inside_triangle(int ind1, int ind2, int ind3, int ind4)
{
	ll total = abs(cross(ind1, ind2, ind3));
	ll sum = 0LL;
	sum += abs(cross(ind1, ind2, ind4));
	sum += abs(cross(ind3, ind2, ind4));
	sum += abs(cross(ind1, ind3, ind4));

	return (total == sum);
}

void solve1(vector<int> H)
{
	if(H.size() < 4)
		return;
	if(k == 0)
		return;

	vector<int> H1, H2;
	H1.clear();
	H2.clear();

	int ind = -1, _prev, nxt;
	for(int i = 0; i<H.size(); i++)
		if(cross(H[(i-1+H.size()) % H.size()], H[i], H[(i+1) % H.size()]) > 0)
		{
			ind = i;
			break;
		}

	assert(ind != -1);
	_prev = (ind - 1 + H.size()) % H.size();
	nxt = (ind + 1) % H.size();

	bool found = false;
	ll maxy = -1, val;
	int pt;
	for(int i = 0; i<H.size(); i++)
	{
		if(i == ind || i == _prev || i == nxt)
			continue;
		if(inside_triangle(H[_prev], H[ind], H[nxt], H[i]))
		{
			val = abs(cross(H[_prev], H[nxt], H[i]));
			if(maxy < val)
			{
				found = true;
				maxy = val;
				pt = i;
			}
		}
	}

	if(found)
	{
		_prev = ind;
		nxt = pt;	
	}

	segs.pb(mp(H[_prev], H[nxt]));
	k--;

	if(_prev > nxt) 
		swap(_prev, nxt);

	for(int i = _prev; i<=nxt; i++)
		H1.pb(H[i]);
	for(int i = nxt; i<H.size(); i++)
		H2.pb(H[i]);
	for(int i = 0; i<=_prev; i++)
		H2.pb(H[i]);

	assert(H1.size() > 2 && H2.size() > 2);

	solve1(H1);
	solve1(H2);

	return;
}

void solve()
{
	k = K;
	segs.clear();

	int n, x, y;
	cin >> n;

	vector<int> H;
	H.clear();

	for(int i = 1; i<=n; i++)
	{
		cin >> X[i] >> Y[i];
		H.pb(i);
	}
	ll temp = area(H);
	assert(abs(temp) > 0);
	if(temp < 0)
		reverse(H.begin(), H.end());
	solve1(H);
	assert(segs.size() == K);
	for(int i = 0; i<segs.size(); i++)
		cout << segs[i].F << " " << segs[i].S << "\n";

	return;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	// freopen("in.in", "r", stdin);
	// freopen("out.out", "w", stdout);

	clock_t clk = clock();
	
	int t = 1;
	cin >> t;
	for(int tests = 1; tests <= t; tests++)
	{
		// cout << "Case #" << tests << ": ";
		solve();
	}

	clk = clock() - clk;
	cerr << "Time Elapsed: " << fixed << setprecision(10) << ((long double)clk)/CLOCKS_PER_SEC << "\n";

}