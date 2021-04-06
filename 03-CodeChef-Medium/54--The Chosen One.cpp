// #define _GLIBCXX_DEBUG
#include <bits/stdc++.h>
using namespace std;

#define ll int64_t
#define ull unsigned long long
#define lld long double
#define FIO ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
#define pb push_back
#define eb emplace_back
#define ff first
#define ss second
#define vt vector
#define vll vt<ll>
#define pll pair<ll,ll>
#define vpll vt<pll>
#define vvll vt<vll>
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(), v.rend()
#define FOR(i,n) for(ll i=0;i<n;i++)
#define ffo(i,a,b) for(ll i=a;i<=b;i++)
#define rfo(i,a,b) for(ll i=a;i>=b;i--)
#define space cout<<"\n\n";
#define endl '\n' // comment this line in interactive prob
template <typename T> using mxpq = priority_queue<T>;
template <typename T> using mnpq = priority_queue<T, vt<T>, greater<T>>;
#define fps(x,y) fixed<<setprecision(y)<<x
#define merg(a,b,c) set_union(a.begin(),a.end(),b.begin(),b.end(),inserter(c,c.begin()))
#define mmss(arr,v) memset(arr,v,sizeof(arr))

const ll mod = 1e9 + 7;
const ll N = 1e6 + 6;
const ll maxN = 1e5 + 15;
const ll MAX_SIZE = 2e6 + 6;
const ll INF = 0x3f3f3f3f3f3f3f3fll;
const lld PI = 3.14159265359;

int dx[4] = { -1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
// up, right, down, left
//int dx[] = {+1,-1,+0,+0,-1,-1,+1,+1}; // Eight Directions
//int dy[] = {+0,+0,+1,-1,+1,-1,-1,+1}; // Eight Directions
//int dx[]= {-2,-2,-1,1,-1,1,2,2}; // Knight moves
//int dy[]= {1,-1,-2,-2,2,2,-1,1}; // Knight moves
// For taking a complete line as input: string s; getline(cin, s);
// For calculating inverse modulo, raise to the power mod-2.
// For (a^b)%mod, where b is large, replace b by b%(mod-1).

ll powerM(ll x, ll y, ll M = mod) { // default argument
	ll v = 1; x = x % M; while (y > 0) {if (y & 1)v = (v * x) % M; y = y >> 1; x = (x * x) % M;} return v;
}

ll power(ll x, ll y) {
	ll v = 1; while (y > 0) {if (y & 1)v = v * x; y = y >> 1; x = x * x;} return v;
}

int largest_bit(long long x) { // based on 0-indexing
	return x == 0 ? -1 : 63 - __builtin_clzll(x);
}

void solve() {
	ll n, k;
	cin >> n >> k;
	ll kk = 1 + (n * (n - 1)) / 2 - k;
	vll a(n);
	vll myhash(n + 1, 0);
	vt<ll> howMany(n + 1, 0);
	vvll position(n + 1);
	FOR(i, n) {
		cin >> a[i];
		myhash[a[i]]++;
		position[a[i]].pb(i + 1);
	}
	ll ans = 0;
	for (ll i = n; i >= 1; --i) {
		ll c = 0, rm = 0;
		for (ll j = i; j <= n; j += i) {
			c += myhash[j];
			rm += howMany[j];
		}
		ll tmp = ((c * (c - 1)) / 2 - rm);
		howMany[i] = tmp;
		kk -= tmp;
		if (kk <= 0) {
			ans = i;
			cout << i << endl;
			break;
		}
	}
	vector <int> spf(n + 1, 0);   // smallest prime factor
	myhash.assign(n + 1, 0);

	for (int i = 2; i <= n; i++) {
		if (!spf[i]) {
			spf[i] = i;
			if (n / i < i) continue;
			for (int j = i * i; j <= n; j += i) {
				if (!spf[j])
					spf[j] = i;
			}
		}
	}

	vector <pair <int, int> > req;
	map <int, int> same_cnt;  // Only 1 duplicate for each number is needed, rest copies can be discarded

	for (int i = 0; i < n; i++) {
		if (a[i] % ans == 0) {
			if (same_cnt[a[i]] > 1) continue;

			same_cnt[a[i]]++;
			req.push_back(make_pair(a[i] / ans, i));
		}
	}

	int first_index, second_index;
	// Now we have to search for a number such that atleast one number before it isn't divisible by any prime factors of our number.

	int first_num = -1;
	for (int i = 0; i < req.size(); i++) {
		int x = req[i].first;
		vector <int> primes;

		while (x > 1) {
			int small = spf[x];
			primes.push_back(small);
			while (x % small == 0)
				x /= small;
		}

		int sz = primes.size();
		int div_count = 0;
		for (int j = 1; j < (1 << sz); j++) {
			int curr_number = 1;
			for (int l = 0; l < sz; l++) {
				if (j >> l & 1)
					curr_number *= primes[l];
			}
			int bits = __builtin_popcount(j);
			div_count += (bits & 1 ? myhash[curr_number] : -myhash[curr_number]);
			myhash[curr_number]++;
		}

		if (div_count < i) {
			first_num = i;
			break;
		}
	}

	assert(first_num != -1);
	first_index = req[first_num].second;

	for (int i = first_num - 1; i >= 0; i--) {
		if (__gcd(req[first_num].first, req[i].first) == 1) {
			second_index = req[i].second;
			break;
		}
	}
	int curr_gcd = __gcd(a[first_index], a[second_index]);
	assert(ans == curr_gcd);
	cout << first_index + 1 << ' ' << second_index + 1 << '\n';
}

int main()
{
#ifdef LOCAL
	freopen("in1.txt", "r", stdin);
	freopen("out1.txt", "w", stdout);
#endif
	FIO;
	int testcases = 1;
	cin >> testcases;
	for (int caseno = 1; caseno <= testcases; ++caseno) {
		// cout << "Case #" << caseno << ": ";
		solve();
	}
	return 0;
}

// cerr << "Time : " << 1000 * ((double)clock()) / (double)CLOCKS_PER_SEC << "ms\n";
