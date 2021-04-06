#include <bits/stdc++.h>
#define int int64_t
using namespace std;
/*

  pi+1 - pi * p - pi
  y/x > y1/x1
	xy1 - x1y < 0

 */
struct P {
	int x, y;
	P() : x(0), y(0) {}
	P(int _x, int _y) : x(_x) , y(_y) {}
	void read() {
		cin >> x >> y;
	}
	P operator -(const P &p) const {
		return P{p.x - x, p.y - y};
	}
	int operator *(const P &p) const {
		return x * p.y - y * p.x;
	}
	int cross (const P& p1, const P& p2) const {
		return (p1-*this) * (p2-*this);
	}
	bool operator <(const P &a) const {
		return make_pair(x, y) < make_pair(a.x, a.y);
	}
	friend ostream& operator <<(ostream& out, const P &p) {
		out << p.x << ' ' << p.y;
		return out;
	}
};

int n, m;
vector<P> points;
vector<P> queries;
vector<vector<P>> hulls;
vector<bool> taken;


void init() {
	points.clear();
	points.resize(n);
	queries.clear();
	queries.resize(m);
	taken.clear();
	taken.assign(n, false);
	hulls.clear();
}

template<class T>
ostream & operator << (ostream &out, const vector<T> v) {
	for(T t : v)
		out << '[' << t << "] ";
	return out;
}

void compute() {
	int got = 0;
	bool done = false;
	while(!done) {
		//done = !done;
		if(points.size() < 2)
			return;
		vector<pair<int, P>> hull;
		sort(points.begin(), points.end());
		vector<P> temp (points.begin(), points.end());
		points.clear();
		taken.clear();
		taken.assign(temp.size(), false);
		for(int rep = 0; rep < 2; rep++) {
			const int S = hull.size();
			int index;
			for(size_t i = 0; i < temp.size(); i++) {
				P C = temp[i];
				index = rep ? temp.size()-1 - i : i;
				while((int) hull.size() - S >= 2) {
					P A = hull.end()[-2].second;
					P B = hull.end()[-1].second;
					if(A.cross(B, C) <= 0) {
						break;
					}
					hull.pop_back();
				}
				hull.push_back({index, C});
			}
			hull.pop_back();
			reverse(temp.begin(), temp.end());
		}
		for(auto e : hull) {
			taken[e.first] = true;
		}
		for(size_t i = 0; i < temp.size(); i++) {
			if(!taken[i])
				points.emplace_back(temp[i]);
		}
		size_t hs = hull.size();
		vector<P> hf(hs);
		for(size_t i = 0; i < hs; ++i)
			hf[i] = hull[i].second;
		hulls.emplace_back(hf);
		if(points.size() == 3) {
			if(points[0].cross(points[1], points[2]) == 0) {
				//hulls.push_back({points[0], points[1], points[2]});
				done = true;
			}
		}
		if(points.size() == 2) {
			//hulls.push_back({points[0], points[1]});
			done = true;
		}
	}
}


bool inside(P p, const vector<P> &poly) {
	int ps = poly.size();
	for(int i = 0; i < ps; i++) {
		if(poly[i].cross(poly[(i+1)%ps], p) >= 0)
			return false;
	}
	return true;
}

void solve() {
	cin >> n;
	cin >> m;
	init();
	for(int i = 0; i < n; i++) {
		points[i].read();
	}
	for(int i = 0; i < m; i++) {
		queries[i].read();
	}
	sort(points.begin(), points.end());
	compute();
	int hs = hulls.size();
	for(P p : queries) {
		bool got = false;
		for(int i = hs - 1; i >= 0; i--) {
			bool in = inside(p, hulls[i]);
			if(in) {
				got = true;
				cout << (i+1) << '\n';
				break;
			}
		}
		if(!got) {
			cout << 0 << '\n';
		}
	}
}

int32_t main() {
	int T = 1;
	cin >> T;
	while(T--) {
		solve();
	}
	return 0;
}

