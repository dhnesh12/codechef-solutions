#include <bits/stdc++.h>
using namespace std;
long long ans[1000*1005];
long long sq(long long a) { return a * a; }
struct P {
	int x, y, id;
	long long dist(const P & other) {
		return sq(x - other.x) + sq(y - other.y);
	}
	long long cross(const P & B, const P & C) {
		return (long long) (B.x - x) * (C.y - y)
			- (long long) (B.y - y) * (C.x - x);
	}
	bool convex(P & B, P & C) { return cross(B, C) < 0; }
};
long long distToLine(P & a, P & b, P & c) {
	// Actually this function returns the area of a triangle.
	// We can use it because we compare distances to the same line.
	return abs(a.cross(b, c));
}
void rec(vector<P> w) {
	if((int) w.size() == 1) return;
	
	// find the convex hull
	vector<P> hull;
	for(int rep = 0; rep < 2; ++rep) {
		int rep_hack = hull.size();
		for(P C : w) {
			while((int) hull.size() >= rep_hack + 2) {
				P & A = hull[hull.size() - 2];
				P & B = hull[hull.size() - 1];
				if(A.convex(B, C)) break;
				hull.pop_back();
			}
			hull.push_back(C);
		}
		hull.pop_back();
		reverse(w.begin(), w.end());
	}
	cerr << hull.size() << "\n";
	
	pair<long long, pair<int, int>> best = {0, {0, 0}};
	
	// two pointers
	const int H = hull.size();
	assert(H >= 2);
	
	auto consider = [&] (int i, int j) {
		i %= H; j %= H;
		best = max(best, {hull[i].dist(hull[j]), {hull[i].id, hull[j].id}}); // maybe minimize indices to be safe
	};
	
	int j = 0;
	for(int i = 0; i < H; ++i) {
		j = max(j, i + 1);
		while(distToLine(hull[i], hull[(i+1)%H], hull[j%H])
			< distToLine(hull[i], hull[(i+1)%H], hull[(j+1)%H])) {
				consider(i, j);
				consider(i + 1, j);
				++j;
			}
		consider(i, j);
		consider(i + 1, j);
	}
	
	int big = max(best.second.first, best.second.second);
	for(int i = big; i < (int) w.size(); ++i)
		ans[i] = best.first;
	vector<P> w2;
	for(P & a : w) if(a.id < big) w2.push_back(a);
	rec(w2);
}

int main() {
	int n;
	scanf("%d", &n);
	vector<P> w;
	for(int i = 0; i < n; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		w.push_back(P{x, y, i});
	}
	sort(w.begin(), w.end(), [](P & a, P & b) {
		return make_pair(a.x, a.y) < make_pair(b.x, b.y); });
	rec(w);
	for(int i = 0; i < n; ++i) printf("%lld\n", ans[i]);
}