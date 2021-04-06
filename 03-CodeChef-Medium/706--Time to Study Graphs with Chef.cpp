#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <complex>
#include <cstdio>
#include <vector>
#include <cctype>
#include <string>
#include <ctime>
#include <cmath>
#include <set>
#include <map>
 
typedef long double LD;
typedef long long LL;
 
using namespace std;
 
#define sz(A) (int)(A).size()
#define mp make_pair
#define pb push_back
#define y1 Y1
#define y2 Y2
 
const int MOD = int(1e9 + 7);
 
// binary exponentiantion
LL power(LL val, LL p) {
	if (!p)
		return 1;
	if (p & 1)
		return (val * power(val, p - 1)) % MOD;
	return power((val * val) % MOD, p / 2);
}
 
struct event {
	LL x;
	int y;
	bool end;
 
	event(LL x = 0, int y = 0, bool end = false) : x(x), y(y), end(end) {}
};
 
// comparator for the events
bool operator < (event a, event b) {
	if (a.x == b.x) {
		if (a.end == b.end)
			return a.y < b.y;
		return a.end < b.end;
	}	
	return a.x < b.x;
}
 
bool operator == (event a, event b) {
	return a.x == b.x && a.y == b.y && a.end == b.end;
}
 
vector<event> e;
 
// additional edges ending in particular vertex
map< pair<LL, int>, vector< pair<LL, int> > > calc_from;
 
// answer for particular vertex (which is an 'event')
map< pair<LL, int>, LL > ans;
 
int main() {
	LL n;
	int k, add_m;
	scanf("%lld%d%d", &n, &k, &add_m);
 
	// scan data
	for (int i = 0; i < add_m; i++) {
		LL x1, x2;
		int y1, y2;
		scanf("%lld%d%lld%d", &x1, &y1, &x2, &y2);
		assert(x1 < x2);
		e.pb(event(x1, y1, 0));
		e.pb(event(x2, y2, 1));
		calc_from[mp(x2, y2)].pb(mp(x1, y1));
	}
	// fictitious event created to simplify obtaining the answer
	e.pb(event(n + 1, 0, 0));
 
	// sort events and delete those one which are the same
	sort(e.begin(), e.end());
	e.resize(unique(e.begin(), e.end()) - e.begin());	
 
	LL cur_pos = 0;
	LL cur_ans = 1, sum = 1;
	for (int i = 0; i < sz(e); i++) {
	    // if jump was made
	    if (cur_pos < e[i].x) {
			cur_ans = (sum * power(k, e[i].x - cur_pos - 1)) % MOD;		
			cur_pos = e[i].x;
			sum = (cur_ans * k) % MOD;
		}		
 
		pair<LL, int> to = mp(e[i].x, e[i].y);
 
		// recalculate the answer for an event-vertex by adding the answers 
		// for the vertices from which it is possible 
		// to get to it via the additional edge
		if (e[i].end) {						    
			for (int j = 0; j < sz(calc_from[to]); j++) {
				pair<LL, int> from = calc_from[to][j];
				sum += ans[from];				
				sum %= MOD;
 
				//if (ans.count(to)) {
					ans[to] += ans[from];
					ans[to] %= MOD;
				//}
			}									
		}
		// if this is an initial vertex of an additional edge
		// nothing is to add to its layer's answer
		else {
		    if (!ans.count(to))
				ans[to] = cur_ans;
		}
	}	
 
	// answer is stored here thanks to the fictitious event
	cout << ans[ mp(n + 1, 0) ] << endl;
 
	// time stamp
	cerr << clock() / double(CLOCKS_PER_SEC) << endl;
 
	return 0;
} 