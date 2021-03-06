#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <complex>
#include <utility>
#include <set>
#include <queue>
 
using namespace std;
 
typedef complex<double> point;
typedef pair<double, int> PDI;
 
const double INF = 1E100;
const int MAX_P = 26;
 
struct edge {
  int a, b; double fuel;
  edge(int a_, int b_, double fuel_) : a(a_), b(b_), fuel(fuel_) {}
  };
 
point getUV(double t, const point &p, const point &q, const point &r) {
  point pp = p-q, rp = r-q;
  point rh = rp / abs(rp);
 
  point dc = conj(pp) * rh;
  double u = dc.real() + dc.imag()/tan(t);
  double v = dc.real() - dc.imag()/tan(t);
  u /= abs(rp); v /= abs(rp);
 
  if (u > v) swap(u, v);
  return point(u, v);
  }
 
int main() {
  cout << fixed << setprecision(3);
  int n, f, cNum = 0;
  while ((cin >> n >> f) && n) {
    double theta = acos(1.0 / f);
 
    vector<point> verts;
    for (int i = 0; i <= n; ++i) {
      int x, y; cin >> x >> y;
      verts.push_back(point(x, y));
      }
 
    vector<edge> edges;
    for (int i = 0; i <= n; ++i)
      for (int j = 0; j <= n; ++j)
        if (j != i+1)
          edges.push_back(edge(i, j, f*abs(verts[j]-verts[i])));
 
    for (int j = 0; j < n; ++j) {
      set<PDI> jumpPts;
      for (int i = 0; i <= n; ++i) {
        point uv = getUV(theta, verts[i], verts[j], verts[j+1]);
        double u = uv.real(), v = uv.imag();
        if ((0 < u) && (u < 1)) {
          point t = verts[j] + u*(verts[j+1] - verts[j]);
          int ti = verts.size();
 
          verts.push_back(t); jumpPts.insert(PDI(u, ti));
          edges.push_back(edge(ti, i, f*abs(verts[i] - t)));
          }
        if ((0 < v) && (v < 1)) {
          point t = verts[j] + v*(verts[j+1] - verts[j]);
          int ti = verts.size();
 
          verts.push_back(t); jumpPts.insert(PDI(v, ti));
          edges.push_back(edge(i, ti, f*abs(t - verts[i])));
          }
        }
 
      int prev = j;
      for (set<PDI>::const_iterator k = jumpPts.begin(); k != jumpPts.end(); ++k) {
        edges.push_back(edge(prev, k->second, abs(verts[k->second] - verts[prev])));
        prev = k->second;
        }
      edges.push_back(edge(prev, j+1, abs(verts[j+1] - verts[prev])));
      }
 
    int nV = verts.size();
    vector< vector<edge> > g(nV);
    for (vector<edge>::const_iterator i = edges.begin(); i != edges.end(); ++i)
      g[i->a].push_back(*i);
 
    vector<double> fuelTo(nV, INF); fuelTo[0] = 0;
    priority_queue<PDI> q; q.push(PDI(0, 0));
 
    while (!q.empty()) {
      PDI t = q.top(); q.pop();
 
      if (t.first == -fuelTo[t.second]) {
        for (vector<edge>::const_iterator i = g[t.second].begin(); i != g[t.second].end(); ++i)
          if (fuelTo[t.second] + i->fuel < fuelTo[i->b]) {
            fuelTo[i->b] = fuelTo[t.second] + i->fuel;
            q.push(PDI(-fuelTo[i->b], i->b));
            }
        }
      }
 
    cout << "Case " << ++cNum << ": " << fuelTo[n] << '\n';
    }
  }
 