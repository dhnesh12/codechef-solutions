#include<bits/stdc++.h>
#define pb push_back
#define fast ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
#define ll long long
#define pii pair<int,int>
#define pll pair<ll,ll>
#define double long double
#define pdd pair<double,double>
#define f first
#define s second
#define int long long
#define sz(x) (ll)(x.size())
#define ftype double
using namespace std;


const int mod = 1e9+7;

int expo_pow(int x,int y){
 if(y == 0) return 1;
  y=y%(mod-1);
  x%=mod;
  if(y==0) y=mod-1;
  int res=1;
  while(y){
    if(y&1) res=(res*x)%mod;
    x=(x*x)%mod;
    y>>=1; 
  }
  return res;
}

ll add()
{
    return 0;
}

template <typename T, typename... Types>
T add(T var1, Types... var2){
    return (((((ll)(var1)) % mod + (ll)(add(var2...))) % mod) + mod) % mod;
}

ll mul(){
    return 1;
}

template <typename T, typename... Types>
T mul(T var1, Types... var2){
    return (((ll)(var1)) % mod * (ll)(mul(var2...))) % mod;
}

const double EPS = 1E-9;
const double PI = acos(-1);

struct point2d {
    ftype x, y;
    point2d() {}
    point2d(ftype x, ftype y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ftype t) {
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ftype t) {
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(ftype t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(ftype t) const {
        return point2d(*this) /= t;
    }
};

point2d operator*(ftype a, point2d b) {
    return b * a;
}

ftype dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}

ftype norm(point2d a) {
    return dot(a, a);
}

double abs(point2d a) {
    return sqrt(norm(a));
}

double proj(point2d a, point2d b) {
    return dot(a, b) / abs(b);
}

double angle(point2d a, point2d b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}

//point2d get_direction(point2d a1,point2d a2) {
//  point2d res = a2 - a1;
//  int tmp = __gcd(res.x,res.y);
//  res/=tmp;
//  return res;
//}


struct line {
    double a, b, c;

    line() {}
    line(point2d p, point2d q)
    {
        a = p.y - q.y;
        b = q.x - p.x;
        c = -a * p.x - b * p.y;
        norm();
    }
    line (double a,double b,double c) {
      this->a = a;
      this->b = b;
      this->c = c;
    }

    void norm()
    {
        double z = sqrt(a * a + b * b);
        if (abs(z) > EPS)
            a /= z, b /= z, c /= z;
    }

    double dist(point2d p) const { return a * p.x + b * p.y + c; }
};

struct circle {
  double r;
  circle() {};
  circle (double r) {
    this->r = r;
  }
};

bool line_circle(line L,circle C,point2d& r1,point2d& r2){
  double r = C.r;
  double a = L.a;
  double b = L.b;
  double c = L.c;
  double x0 = -a*c/(a*a+b*b), y0 = -b*c/(a*a+b*b);

  if (c*c > r*r*(a*a+b*b)+EPS) {
    return false;
  }
  else if (abs (c*c - r*r*(a*a+b*b)) < EPS) {
    return false;
  }
  else {
    double d = r*r - c*c/(a*a+b*b);
    double mult = sqrt (d / (a*a+b*b));
    double ax, ay, bx, by;
    ax = x0 + b * mult;
    bx = x0 - b * mult;
    ay = y0 - a * mult;
    by = y0 + a * mult;
    r1.x = ax;
    r1.y = ay;
    r2.x = bx;
    r2.y = by;
    if (r1.x > r2.x) {
      swap(r1,r2);
    }
    else if (r1.x == r2.x and r1.y > r2.y) {
      swap(r1,r2);
    }
    return true;
  }
}

//c1 is centered at origin and x1 and x2 are centers of C2 when C1 is shifted to origin
bool circle_circle(circle C1,double r2,double x2,double y2,point2d& res1,point2d& res2) {
  line l(-2*x2,-2*y2,x2*x2 + y2*y2 +C1.r*C1.r - r2*r2);
  return line_circle(l,C1,res1,res2);
}

double dist(double x1,double y1,double x2,double y2) {
  return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double get_angle(point2d x) {
  double tmp = angle(point2d(0,1),x);
  if (x.x < 0) {
    tmp = 2*PI - tmp;
  }
  return tmp;
}

void solve(){
  int w,h,n;
  cin >> w >> h >> n;
  w *= 100;
  h *= 100;
  
  vector<pair<pdd,double>> a(n);
  for (int i = 0; i < n; ++i) {
    cin >> a[i].f.f >> a[i].f.s >> a[i].s;
    int x = a[i].f.f * 100 + 0.5;
    int y = a[i].f.s * 100 + 0.5;
    int r = a[i].s * 100 + 0.5;
    a[i].f.f = x;
    a[i].f.s = y;
    a[i].s = r;
  }

  double ans = 0;
  for (int i = 0; i < n; ++i) {

    double add_x = a[i].f.f;
    double add_y = a[i].f.s;
    
    if ((add_x < 0 and abs(add_x) >= a[i].s) or (add_x > w and abs(add_x - w) >= a[i].s)) {
      continue;
    }
    if ((add_y < 0 and abs(add_y) >= a[i].s) or (add_y > h and abs(add_y - h) >= a[i].s)) {
      continue;
    }


    circle C(a[i].s);
    int full_ignore = 0;
    vector<pair<double,double>> points;
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      double new_x = a[j].f.f - add_x;
      double new_y = a[j].f.s - add_y;
      point2d pt1,pt2;
      if(!circle_circle(C,a[j].s,new_x,new_y,pt1,pt2)){
        if (dist(new_x,new_y,0,0) <= a[j].s and a[j].s > a[i].s) {
          full_ignore = 1;
          break;
        }
        continue;
      }
      // other circle to the lower left of current 
      double a1,a2;
      if (new_x <= 0 and new_y < 0) {
        a1 = get_angle(pt2);
        a2 = get_angle(pt1);
      }
      else if (new_y >= 0 and new_x <= 0) {
        a1 = get_angle(pt1);
        a2 = get_angle(pt2);
      }
      else if (new_y > 0 and new_x > 0) {
        a1 = get_angle(pt1);
        a2 = get_angle(pt2);
      }
      else if (new_y <= 0 and new_x > 0) {
        a1 = get_angle(pt2);
        a2 = get_angle(pt1);
      }
      //sort(points.begin() + 1,points.end(),cmp);
      if (a2 > a1) points.pb({a1,a2});
      else {
        points.pb({a1,2*PI});
        points.pb({0,a2});
      }
    }



    if (full_ignore == 1) continue;
    //cout << " before\n";
    //for (auto u:points) {
    //  cout << u.f << " " << u.s << "\n";
    //}
    //cout << "Angles printed\n";
    // for line x = -add_x
    line l(1,0,add_x);
    double a1,a2;
    point2d pt1,pt2;
    if (line_circle(l,C,pt1,pt2)) {
      a1 = get_angle(pt1);
      a2 = get_angle(pt2);
      if (a2 > a1) points.pb({a1,a2});
      else {
        points.pb({a1,2*PI});
        points.pb({0,a2});
      }

    }
    l.c = add_x  - w;
    if (line_circle(l,C,pt1,pt2)) {
      a1 = get_angle(pt2);
      a2 = get_angle(pt1);
      if (a2 > a1) points.pb({a1,a2});
      else {
        points.pb({a1,2*PI});
        points.pb({0,a2});
      }
    }
    l.a = 0;
    l.b = 1;
    l.c = add_y;
    if (line_circle(l,C,pt1,pt2)) {
      a1 = get_angle(pt2);
      a2 = get_angle(pt1);
      if (a2 > a1) points.pb({a1,a2});
      else {
        points.pb({a1,2*PI});
        points.pb({0,a2});
      }
    }
    l.c = add_y - h;
    if (line_circle(l,C,pt1,pt2)) {
      a1 = get_angle(pt1);
      a2 = get_angle(pt2);
      if (a2 > a1) points.pb({a1,a2});
      else {
        points.pb({a1,2*PI});
        points.pb({0,a2});
      }
    }
    if (points.empty()){
      ans += 2*PI*a[i].s;
      continue;
    }

    sort(points.begin(),points.end());

    //cout << i << "starting\n";
    //for (auto u:points) {
    //  cout << u.f << " " << u.s << "\n";
    //}
    //cout << "Angles printed\n";
    double angle = 2*PI;

    for (int i = 0; i < points.size(); ++i) {
      int j = i;
      double mx_end = points[i].s;
      while ( j < points.size() and points[j].f <= mx_end) {
        mx_end = max(mx_end,points[j].s);
        j++;
      }
      angle -= mx_end - points[i].f;
      i = j - 1;
    }

    //cout << angle << " " << " adding here " << angle*a[i].s << "\n";
    ans += angle*a[i].s;
  }
  cout << setprecision(7) << fixed << ans/100 << "\n";
}


signed main(){
  fast;
  int test = 1;
  //cout << acos(-1) << "\n";
  //point2d p1,p2;
  //circle c(2);
  //circle_circle(c,2,2,0,p1,p2);
  //cout << p1.x << " " << p1.y << "\n";
  //cout << p2.x << " " << p2.y << "\n";
  //line l(-4,-0,4);
  //line_circle(l,c,p1,p2);
  //cout << p1.x << " " << p1.y << "\n";
  //cout << p2.x << " " << p2.y << "\n";
  cin>>test;
  int i=1;
  while(test--){
    solve();
  }
}



