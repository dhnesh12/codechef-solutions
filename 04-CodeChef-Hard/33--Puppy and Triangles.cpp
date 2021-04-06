    #include <algorithm>
    #include <cassert>
    #include <cmath>
    #include <complex>
    #include <set>
    #include <map>
    #include <utility>
    #include <vector>
     
    using namespace std;
     
    const double E = 1e-8;
     
    typedef long long lint;
    typedef complex<double> point;
    typedef vector<point> triangle;
    typedef vector<point> quadrangle;
     
    struct line {
      point p, v;
      line(point from, point to): p(from), v(to-from) {}
    };
     
    point normal(const point &p) { return p / abs(p); }
    double cross(const point &a, const point &b) { return a.real() * b.imag() - a.imag() * b.real(); }
    double cross(const point &a, const point &b, const point &c) { return cross(b-a, c-a); }
     
    double area(const vector<point> &poly) {
      double result = 0.0;
      for (int i = 0; i < (int)poly.size(); ++i)
        result += cross(poly[i], poly[(i+1)%poly.size()])/2;
      return result;
    }
     
    point intersection(line a, line b) {
      double t = cross(b.p-a.p, b.v) / cross(a.v, b.v);
      return a.p + t*a.v;
    }
     
    double dist(const point &a, const point &b) { return abs(a-b); }
     
    bool matches(triangle t1, triangle t2) {
      vector<double> dists[2];
      for (int i = 0; i < 2; ++i) {
        triangle &t = i == 0 ? t1 : t2;
        for (int a = 0; a < 3; ++a)
          for (int b = a+1; b < 3; ++b)
    	dists[i].push_back(dist(t[a], t[b]));
        sort(dists[i].begin(), dists[i].end());
      }
      for (int j = 0; j < 3; ++j)
        if (abs(dists[0][j] - dists[1][j]) > E)
          return false;
      return true;
    }
     
    bool matches(triangle need1, triangle need2, triangle have1, triangle have2) {
      return matches(need1, have1) && matches(need2, have2) || matches(need1, have2) && matches(need2, have1);
    }
     
    bool merge2(triangle t1, triangle t2, triangle big) {
      for (int first = 0; first < 2; ++first) {
        for (int rot = 0; rot < 3; ++rot) {
          assert(area(big) > 0);
          double height = 2*area(big) / dist(big[0], big[1]);
          double width = area(t1) * 2 / height;
     
          point dir = normal(big[1] - big[0]);
          point p = big[0] + dir * width;
          
          if (matches(t1, t2, {big[0], p, big[2]}, {p, big[1], big[2]}))
    	return true;
        
          rotate(big.begin(), big.begin()+1, big.end());
        }
        swap(t1, t2);
      }
      return false;
    }
     
    bool merge(triangle t1, triangle t2, quadrangle quad) {
      for (int i = 0; i < 4; ++i) {
        int l = (i-1+4)%4, r = (i+1)%4, m = (i+2)%4;
        const double c = cross(quad[l], quad[r], quad[i]);
        if (c > E) {
          if (matches(t1, t2, {quad[l], quad[i], quad[m]}, {quad[i], quad[r], quad[m]}))
    	return true;
          point left = intersection(line(quad[i], quad[r]), line(quad[l], quad[m]));
          if (matches(t1, t2, {left, quad[r], quad[m]}, {left, quad[l], quad[i]}))
    	return true;
          point right = intersection(line(quad[l], quad[i]), line(quad[r], quad[m]));
          if (matches(t1, t2, {right, quad[i], quad[r]}, {right, quad[m], quad[l]}))
    	return true;
          return false;
        } else if (abs(c) < E) {
          triangle big = {quad[r], quad[m], quad[l]};
          return merge2(t1, t2, big);
        }
      }
      if (matches(t1, t2, {quad[0], quad[1], quad[2]}, {quad[0], quad[2], quad[3]}))
        return true;
      if (matches(t1, t2, {quad[1], quad[2], quad[3]}, {quad[1], quad[3], quad[0]}))
        return true;
      return false;
    }
     
    point read_point() {
      double x, y;
      scanf("%lf %lf", &x, &y);
      return {x, y};
    }
     
    vector<point> read_poly(int size) {
      vector<point> result(size);
      for (int i = 0; i < size; ++i) result[i] = read_point();
      if (area(result) < 0) reverse(result.begin(), result.end());
      return result;
    }
     
    int main() {
      int ntest;
      scanf("%d", &ntest);
      for (int t = 0; t < ntest; ++t) {
        triangle t1 = read_poly(3), t2 = read_poly(3);
        quadrangle quad = read_poly(4);
        if (merge(t1, t2, quad)) printf("Yes\n");
        else printf("No\n");
      }
      
      return 0;
    }
     