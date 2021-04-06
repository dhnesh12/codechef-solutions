#include <bits/stdc++.h>

using namespace std;

typedef long long LL;

class pt {
public:
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x;
		y = _y;
	}
	bool operator<(const pt &rhs) const {
		return make_pair(x, y) < make_pair(rhs.x, rhs.y);
	}
	pt operator-(const pt &rhs) const {
		return pt(x - rhs.x, y - rhs.y);
	}
};

LL cross(pt a, pt b) {
	return a.x * (LL) b.y - b.x * (LL) a.y;
}

LL cross(pt a, pt b, pt c) {
	return cross(b - a, c - b);
}

vector<pt> findHull(vector<pt> p, int lower = true) {
	sort(p.begin(), p.end());
	vector<pt> hull;
	for (int i = 0; i < p.size(); i++) {
		int sign = lower ? -1 : 1;
		while (hull.size() >= 2 && cross(hull[hull.size() - 2], hull[hull.size() - 1], p[i]) * sign >= 0) {
			hull.pop_back();
		}
		hull.push_back(p[i]);
	}
	return hull;
}

bool checkGood(vector<pt> &hull, int lower, pt p) {
	const int INF = 1e9 + 10;
	auto it = lower_bound(hull.begin(), hull.end(), p);
	if (it != hull.end()) {
		int idx = it - hull.begin();
		// printf("idx = %d, x = %d, y = %d\n", idx, hull[idx].x, hull[idx].y);
		if (idx != 0) {
			int sign = lower ? 1 : -1;
			return cross(hull[idx - 1], hull[idx], p) * sign > 0;
		}
	}
	return false;
}

bool pointStrictlyInPolyTest(vector<pt> &lower, vector<pt> &upper, pt p) {
	return checkGood(lower, true, p) && checkGood(upper, false, p);
}

void print(vector<pt> p) {
	cout << "{ " << endl;
	for (auto it: p) {
		printf("\t %d, %d\n", it.x, it.y);
	}
	cout << "}" << endl;
}

void test() {
	int n;
	scanf("%d", &n);
	vector<pt> p;
	for (int i = 0; i < n; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		p.push_back(pt(x, y));
	}

	vector<pt> lower = findHull(p, true);
	vector<pt> upper = findHull(p, false);
	
	print(lower);
	print(upper);

	while (true) {
		int x, y;
		scanf("%d %d", &x, &y);
		int ok = pointStrictlyInPolyTest(lower, upper, pt(x, y));
		printf("%d, %d = %d\n", x, y, ok);
	}
}

int main() {
	/*
	test();
	return 0;
	*/

	int T;
	scanf("%d", &T);
	while (T--) {
		int n;
		scanf("%d", &n);
		vector<pt> p;
		for (int i = 0; i < n; i++) {
			int x, y;
			scanf("%d %d", &x, &y);
			p.push_back(pt(x, y));
		}

		vector<pt> lower = findHull(p, true);
		vector<pt> upper = findHull(p, false);

		int requiredpts = n / 10;
		set<pt> resultSet;
		int right = 0;
		for (int idx = 0; ; idx++) {
			// cerr << "idx " << idx << endl;
			vector<pt> pts;
			for (int j = 0; right < n && j < 9; j++) {
				pts.push_back(p[right]);
				right++;
			}
			for (int i = 0; i < pts.size(); i++) {
				for (int j = i + 2; j < pts.size(); j++) {
					if (((pts[i].x + pts[j].x) % 2 == 0) 
						&& ((pts[i].y + pts[j].y) % 2 == 0)) {
						resultSet.insert(pt((pts[i].x + pts[j].x) / 2, (pts[i].y + pts[j].y) / 2));
						if (resultSet.size() == requiredpts) {
							goto DONE;
						}
					}
				}
			}
		}
		DONE:
			assert(resultSet.size() == requiredpts);
			for (auto it: resultSet) {
				int ok = pointStrictlyInPolyTest(lower, upper, it);
				printf("%d %d\n", it.x, it.y);		
				assert(ok);		
			}
	}
	return 0;
}