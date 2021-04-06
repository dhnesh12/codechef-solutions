#include <bits/stdc++.h>

using namespace std;

const long double eps = 1e-7;
const long double PI = acos(-1);

bool zero(long double d = 0){
	return abs(d) < eps;
}
struct point{
	long double x, y;

	point() {}
	point(long double x_, long double y_) {x = x_; y = y_;}
	// Distance Squared
	long double dist2(point p = {0, 0}){
		return (p.x - x) * (p.x - x) + (p.y - y) * (p.y - y);
	}
	// Distance, by default from origin
	long double dist(point p = {0, 0}) {
		return sqrt(dist2(p));
	}

	point operator + (const point & p) const {
		return {x + p.x, y + p.y};
	}

	point operator - (const point & p) const {
		return {x - p.x, y - p.y};
	}
	point operator * (const long double mul) const {
		return {x * mul, y * mul};
	}

	bool operator < (const point& p) const{
		if(p.x == x) return y < p.y;
		return x < p.x;
	}
	bool operator == (const point & p) const{
		return x == p.x && y == p.y;
	}

	// return a point after rotating b by angle t wrt this
	point rotate(point b, long double t){
		long double xx = b.x - x;
		long double yy = b.y - y;
		return {xx * cos(t) - yy * sin(t) + x,
				yy * cos(t) + xx * sin(t) + y};
	}
};


struct circle
{
	long double xc, yc, r;

	circle() {}
	circle(long double x, long double y, long double r_) {xc = x, yc = y, r = r_;}

	long double valueAt(long double x) {
		if (x <= xc - r || x >= xc + r) return 0;
		return sqrt(r * r - (xc - x) * (xc - x));
	}

	bool inside(point p) {
		return r * r > (p.x - xc) * (p.x - xc) + (p.y - yc) * (p.y - yc);
	}

	// return vector of points of intesection of the circles
	vector<point> intersect(circle c){
		long double x1 = xc, y1 = yc, r1 = r;
		long double x2 = c.xc, y2 = c.yc, r2 = c.r;

		if(r1 < r2) return c.intersect((circle){x1, y1, r1});

		point c1 = {x1, y1};
		point c2 = {x2, y2};

		long double d = c1.dist(c2);

		// one intesecting point
		if(zero(c1.dist2(c2) - (r1+r2)*(r1+r2)) || zero(c1.dist2(c2) - (r1-r2)*(r1-r2))){
			return {{x1 + (x2-x1) * r1 / d,
					y1 + (y2-y1) * r1 / d}};
		}

		// no intesection point
		if(c1.dist2(c2)+eps > (r1+r2)*(r1+r2) || c1.dist2(c2) < (r1-r2)*(r1-r2) + eps){
			return {};
		}

		long double Cos_t = (r1*r1 + d*d - r2*r2)*0.5/d/r1;
		long double t = acos(Cos_t);

		point p = {x1 + (x2-x1)*r1/d,
					y1 + (y2-y1)*r1/d};

		point p1 = c1.rotate(p, t);
		point p2 = c1.rotate(p, -t);
		return {p1, p2};
	}
};

circle discs[100100];

const int L_LIM = -100001;
const int R_LIM = 200001;

struct seg
{
	int idx;
	long double l, r;

	seg(int idx_, long double l_, long double r_) {
		idx = idx_;
		l = l_;
		r = r_;
	}
	seg(){}

	bool operator < (const seg & o) const {
		return l < o.l;
	}
};

void updateRes(int i1, int i2, long double l, long double r, vector<seg> & res, bool f = false) {
	// two semi-discs can intersect at-most one point
	// prove this !!!
	if (!f){
		if (i1 == 0) {
			return res.push_back(seg(i2, l, r));
		}
		if (i2 == 0) {
			return res.push_back(seg(i1, l, r));
		}
		long double v1 = discs[i1].valueAt(l) - discs[i2].valueAt(l);
		long double v2 = discs[i1].valueAt(r) - discs[i2].valueAt(r);
		if (v1 >= 0 && v2 >= 0) {
			res.push_back(seg(i1, l, r));
			return ;
		}
		if (v1 <= 0 && v2 <= 0) {
			res.push_back(seg(i2, l, r));
			return ;
		}
		if (v1 < 0) return updateRes(i2, i1, l, r, res, true);
	}

	int iter = 500;
	long double low = l, high = r, mid = (l + r) * 0.5;
	while(iter--) {
		mid = (low + high) * 0.5;
		long double val = discs[i1].valueAt(mid) - discs[i2].valueAt(mid);
		if (val >= 0) low = mid;
		else high = mid;
	}
	res.push_back(seg(i1, l, mid));
	res.push_back(seg(i2, mid, r));
}

void compress(vector<seg> & res) {
	int j = 0;
	for (int i = 1; i < res.size(); ++i) {
		if (res[i].idx == res[j].idx) {
			res[j].r = res[i].r;
			continue;
		}
		res[++j] = res[i];
	}
	res.resize(j + 1);
}

vector<seg> recurse(int i, int j) {
	vector<seg> res;
	if (i == j) {
		circle & c = discs[i];
		res.push_back(seg(0, L_LIM, c.xc - c.r));
		res.push_back(seg(i, c.xc - c.r, c.xc + c.r));
		res.push_back(seg(0, c.xc + c.r, R_LIM));
		return res;
	}

	int mid = (i + j) / 2;
	vector<seg> res1 = recurse(i, mid);
	vector<seg> res2 = recurse(mid+1, j);

	long double l = L_LIM;
	int i1 = 0, i2 = 0;
	while(l < R_LIM) {
		while(i1 < res1.size() && res1[i1].r <= l + eps) ++i1;
		while(i2 < res2.size() && res2[i2].r <= l + eps) ++i2;
		long double r = min(res1[i1].r, res2[i2].r);
		updateRes(res1[i1].idx, res2[i2].idx, l, r, res);
		l = r;
	}
	compress(res);
	return res;
}

long double computeHalfCircleArea(circle c, long double l, long double r, bool upper = true) {
	l -= c.xc; r -= c.xc;
	if (l >= c.r || r <= -c.r) return 0;
	l = max(-c.r, l);
	r = min(c.r, r);
	long double ar = r * sqrt(max<long double>(0, c.r * c.r - r * r));
	ar += c.r * c.r * asin(max<long double>(-1, min<long double>(1, r/c.r)));

	ar -= l * sqrt(max<long double>(0, c.r * c.r - l * l));
	ar -= c.r * c.r * asin(max<long double>(-1, min<long double>(1, l/c.r)));
	ar *= upper ? 0.5 : -0.5;
	ar += (r - l) * c.yc;
	return ar;
}

long double computeArea(seg & s, circle c) {
	if (s.idx == 0) return 0;
	long double R = discs[s.idx].r;
	long double r = c.r;
	long double dx = discs[s.idx].xc - c.xc;
	long double dy = discs[s.idx].yc - c.yc;
	// if c is inside seg
	if ((R - r) * (R - r) >= dx * dx + dy * dy) {
		long double ar = computeHalfCircleArea(c, s.l, s.r, true);
		ar -= computeHalfCircleArea(c, s.l, s.r, false);
		assert(ar + eps >= 0);
		return ar;
	}
	// c is outside
	if ((R + r) * (R + r) <= dx * dx + dy * dy) {
		return 0;
	}
	// intersects at two points
	vector<point> pts = c.intersect(discs[s.idx]);
	if (pts.size() != 2) return 0;
	long double l = pts[0].x; r = pts[1].x;
	if (l > r) swap(l, r);
	if (l >= s.r || r <= s.l) return 0;
	l = max(l, s.l);
	r = min(r, s.r);
	long double ar = computeHalfCircleArea(discs[s.idx], l, r, true);
	ar -= computeHalfCircleArea(c, l, r, false);
	circle d = discs[s.idx];

	// create counter cases, if someone miss following conditions
	if (d.inside(point(c.xc + c.r, c.yc))) {
		ar += computeHalfCircleArea(c, r, min(s.r, c.xc + c.r), true);
		ar -= computeHalfCircleArea(c, r, min(s.r, c.xc + c.r), false);
	}
	if (d.inside(point(c.xc - c.r, c.yc))) {
		ar += computeHalfCircleArea(c, max(s.l, c.xc - c.r), l, true);
		ar -= computeHalfCircleArea(c, max(s.l, c.xc - c.r), l, false);
	}
	return ar;
}

bool isInside(point p, vector<seg> & v) {
	auto it = upper_bound(v.begin(), v.end(), seg(0, p.x, p.y));
	if (it == v.begin()) return false;
	--it;
	return discs[it -> idx].inside(p);
}

std::random_device rd;
std::mt19937 gen(rd()); // mersene twister
std::uniform_real_distribution<long double> dis(0, 1);

point getRandomPoint(circle & c) {
	long double r = sqrt(dis(gen) * c.r * c.r);
	long double t = dis(gen) * 2*PI;
	return {c.xc + r * cos(t), c.yc + r * sin(t)};
}

long double monteCarloArea(vector<seg> & v, circle & c) {
	int iter = 2000000, correct = 0;
	for (int ii = 0; ii < iter; ++ii) {
		point p = getRandomPoint(c);
		correct += isInside(p, v);
	}
	return correct * PI * c.r * c.r / iter;
}

void solve(int& nSum, int& qSum) {
	int n, q;
	scanf("%d%d", &n, &q);
	nSum += n;
	qSum += q;

	assert(1 <= n && n <= 100000);
//	assert(20 <= q && q <= 200);
	assert(1 <= nSum && nSum <= 100000);
	assert(1 <= qSum && qSum <= 100000);

	for (int i = 1; i <= n; ++i) {
		int x, y = 0, r;
		scanf("%d%d", &x, &r);
		assert(1 <= x && x <= 100000);
		assert(1 <= r && r <= 100000);

		discs[i] = circle(x, y, r);
	}
	vector<seg> arcs = recurse(1, n);

	while (q--) {
		int x, y, r;
		scanf("%d%d%d", &x, &y, &r);

		assert(1 <= x && x <= 100000);
		assert(1 <= y && y <= 100000);
		assert(1 <= r && r <= 100000);
		assert(r <= y);

		circle queryCircle = circle(x, y, r);
		long double totalArea = 0;
		for (seg & s : arcs) {
			long double ar = computeArea(s, queryCircle);
			totalArea += ar;
		}
//		 long double mCArea = monteCarloArea(arcs, queryCircle);
		printf("%.10Lf", totalArea);
//		printf("%.10Lf", mCArea);
		// fprintf(stderr, "%.10f| ", mCArea);
		// fflush(stderr);
		putchar(10);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	assert(1 <= T && T <= 10);
	int nSum = 0, qSum = 0;
	while(T--) {
		solve(nSum, qSum);
	}
	assert(nSum <= 100000 && qSum <= 100000);
	return 0;
}