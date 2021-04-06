#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
const int mod = 1e9 + 7;

struct BIT {
	int n;
	vector<int> a;
	BIT(int sz):n(sz + 1), a(n){}
	void add(int x, int p) {
		for(; x < n; x += x&-x) a[x] += p;
	}
	int sum(int x) {
		int ret = 0;
		for(; x; x -= x&-x) ret += a[x];
		return ret;
	}
	int query(int l, int r) {
		if(l > r) return 0;
		r = min(r, n - 1);
		l = max(l, 1);
		return sum(r) - sum(l - 1);
	}
};

int main() {
	int _; cin >> _;
	while(_--) {
		int n, t;
		cin >> n >> t;
		vector<pii> seg(n);
		vector<ll> disc(n * 8);
		int cur = 0;
		t *= 2;
		for(auto &e : seg) {
			cin >> e.fi >> e.se;
			e.fi *= 2;
			e.se *= 2;
			
			disc[cur++] = e.fi;
			disc[cur++] = (ll) e.fi + t;
			disc[cur++] = e.fi - 1;
			disc[cur++] = (ll) e.fi - 1 + t;
			
			
			disc[cur++] = e.se;
			disc[cur++] = (ll) e.se + t;
			disc[cur++] = e.se - 1;
			disc[cur++] = (ll) e.se - 1 + t;
		}
		sort(all(disc));
		disc.erase(unique(all(disc)), disc.end());
		for(auto &e : seg) {
			e.fi = lower_bound(all(disc), e.fi) - disc.begin() + 1;
			e.se = lower_bound(all(disc), e.se) - disc.begin() + 1;
		}
		int sz = disc.size();
		BIT t1(sz), t2(sz);
		vector<vector<int> > aux(sz + 1);
		for(auto &e : seg) {
			aux[e.fi].emplace_back(e.se);
			t1.add(e.se, 1);
		}
		int ans = 0;
		//for(auto &e : disc) cout << e << ' '; cout << endl;
		for(int i = 0; i < sz; i++) {
			for(auto &e : aux[i + 1]) {
				t1.add(e, -1);
			}
			int r1 = lower_bound(all(disc), (ll) disc[i] + t) - disc.begin();
			int r2 = upper_bound(all(disc), (ll) disc[i] + t) - disc.begin() + 1;
			//cout << r1 << ' ' << r2 << ' ' << disc[i] - 1 + t << endl;
			
			int x = t1.query(1, r1);
			int y = t2.query(r2, sz);
			ans = max(ans, x - y);
			for(auto &e : aux[i + 1]) {
				t2.add(e, 1);
			}
		}
		cout << ans << '\n';
	}
	return 0;
}