#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
typedef vector<vi> vvi;
typedef vector<double> vd;
typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef vector<pii> vii;
typedef vector<string> vs;

struct P {
  ld x, y;
  P (ld x, ld y): x(x), y(y) {}
  P() {}
  P(const P& v): x(v.x), y(v.y) {}
  P operator*(ld p) const { return P(p * x, p * y); }
  double operator&(P p) const { return p.x * x + p.y * y; }
  P operator-(void) const { return P(-x, -y); }
  P operator+(const P& p) const { return P(x + p.x, y + p.y); }
  P operator-(const P& p) const { return P(x - p.x, y - p.y); }
  ld norm() { return sqrt(x * x + y * y); }
};

ld vect(const P& a, const P& b) {
  return a.x*b.y - a.y*b.x;
}

ld p2(ld x) {
  return x * x;
}

ld f(ld r, ld a) {
  a = max(a, (ld)0.);
  ld alp = 2 * asin(min(ld(1.), a / r));
  return (alp * r * r - r * r * sin(alp)) / 2;
}

const ld eps = 1e-10;

ld g(ld r0, ld rr1, ld d) {
  if (d >= r0 + rr1 - eps) return 0;
  ld r1 = min(r0, rr1), r2 = max(r0, rr1);
  if (d + r1 <= r2 + eps) {
    return M_PI * r1 * r1;
  }
		ld a1 = acosl((r1 * r1 + d * d - r2 * r2) / 2 / r1 / d);
		ld a2 = acosl((r2 * r2 + d * d - r1 * r1) / 2 / r2 / d);
		return (a1 - 0.5 * sinl(2 * a1)) * r1 * r1 + (a2 - 0.5 * sinl(2 * a2)) * r2 * r2;
/*  ld x = (p2(d) + p2(r2) - p2(r1)) / 2 / d;
  ld a = sqrt(max((ld)0., p2(r2) - p2(x)));
  if (d >= x) {
    return f(r1, a) + f(r2, a);
  } else {
    return M_PI * r1 * r1 - f(r1, a) + f(r2, a);
  }*/
}

int main() {
  int T;
  scanf("%d", &T); 
  for (int test = 1; test <= T; ++test) {
    P x[2], v[2];
    ld r[2];
    for (int i = 0; i < 2; ++i) {
      scanf("%Lf%Lf%Lf%Lf%Lf", &x[i].x, &x[i].y, &v[i].x, &v[i].y, &r[i]);
    }
    P l[2];
    for (int i = 0; i < 2; ++i) {
      scanf("%Lf%Lf", &l[i].x, &l[i].y);
    }
    P dir = l[1] - l[0];
    P ndir(-dir.y, dir.x);
    vd t(1, 0);
    t.push_back(1e100);
    vd chtime(2, t.back());
    vector<P> x1(2), v1(2);
    for (int i = 0; i < 2; ++i) {
//      cerr << vect(dir, v[i]) << ' ' << dir.x << ' ' << dir.y << ' ' << v[i].x << ' ' << v[i].y << endl;
      if (fabs(vect(dir, v[i])) > eps) {
        double projv = (v[i] & ndir) * (1. / ndir.norm());
        double projx = ((l[0] - x[i]) & ndir) * (1. / ndir.norm());
//        cerr << projx << ' ' << projv << endl;
        if (projv * projx < 0) continue;
        t.push_back((fabs(projx) - r[i]) / fabs(projv));
        chtime[i] = t.back();
        x1[i] = x[i] + v[i] * t.back();
        v1[i] = v[i] - ndir * (2 * projv / ndir.norm());
      }
    }
    sort(t.begin(), t.end());
    ld res = 0;
    for (int i = 0; i + 1 < (int)t.size(); ++i) {
      ld L = t[i], R = t[i + 1];
      P y[2], u[2];
      for (int j = 0; j < 2; ++j) {
        u[j] = (L < chtime[j]) ? v[j] : v1[j];
        y[j] = (L < chtime[j]) ? x[j] + v[j] * L : x1[j] + v1[j] * (L - chtime[j]);
      }
      P dx = y[1] - y[0], dv = u[1] - u[0];
      ld A = (dv & dv), B = (dx & dv) * 2., C = (dx & dx);
      ld mi = min(A * L * L + B * L + C, A * R * R + B * R + C);
      ld opt = L;
      if (fabs(A) > eps) {
        opt = -B / 2. / A;
        if (opt >= 0 && opt <= R - L) {
          mi = min(mi, A * opt * opt + B * opt + C);
        }
      }
//      cerr << L << ' ' << R << ' ' << opt << ' ' << dx.x << endl;
      ld d = sqrt(max((ld)0., mi));
      res = max(res, g(r[0], r[1], d));
    }
    printf("%.10lf\n", (double)res);
  }
  return 0;
}
