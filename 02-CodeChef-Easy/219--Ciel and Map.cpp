#include<bits/stdc++.h>
using namespace std;

//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")


#define pb push_back
#define fi first
#define se second
#define ll long long
#define tp top()
#define fr front()
#define vi vector<int>
#define sz size()
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,  b) memset(a,  (b),  sizeof(a))
#define clr(a) memset(a,  0,  sizeof(a))
#define sqr(x) ( (x) * (x) )
#define all(v) v.begin(),  v.end()

typedef pair<int, int> pii;
typedef pair<int,pii> pip;
typedef pair<pii,int> ppi;
typedef pair<pii,pii> ppp;



void base(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
}


const double EPS=1E-9;
const double PI = acos(-1.0);
const double INF=1E9;

double between_d(double x,double l, double r){
	return (min(l,r)<=x+EPS && x<=max(l,r)+EPS);
}
double same_d(double x, double y){
	return between_d(x,y,y);
}

struct point {
	double x,y;
	point() {x=y=0.0;}
	point(double _x, double _y) {x=_x;y=_y;}
	bool operator< (point other){
		if (x<other.x+EPS) return true;
		if (x+EPS>other.x) return false;
		return y<other.y+EPS;		
	}
	bool operator== (point other){
		return same_d(x,other.x) && same_d(y,other.y);
	}
};

double e_dist(point p1, point p2){
	return hypot(p1.x-p2.x, p1.y-p2.y);
}

struct vec{
	double x,y;
	vec(point a, point b){
		x=b.x-a.x;
		y=b.y-a.y;
	}
};

double cross(vec u, vec v){
	return (u.x*v.y-u.y*v.x);
}

int orientation(point p, point q, point r){
	vec pq(p,q), pr(p,r);
	double c=cross(pq,pr);
	if (c<-EPS) return -1;
	if (c>EPS) return 1;
	return 0;
}

struct line {
	double a,b,c;
	line(){
		a=b=c=0.0;
	}
	
	line(point p1, point p2){
		if (p2<p1) swap(p1,p2);
		if (same_d(p1.x,p2.x)) a=1.0, b=0.0, c=-p1.x;
		else a=-(p1.y-p2.y)/(p1.x-p2.x), b=1.0, c=-(a*p1.x)-p1.y;
	}
	
};

struct segment {
	point p,q;
	line l;
	segment(point _p, point _q){
		if (_q<_p) swap(_p,_q);
		p=_p; q=_q;
		line t2(_p,_q); l=t2;
	}
};

bool onSegment(point p, segment s){
	if (orientation(s.p,s.q,p)!=0) return false;
	return between_d(p.x,s.p.x,s.q.x) && between_d(p.y,s.p.y,s.q.y);
}

bool s_intersection(segment s1, segment s2){
	double o1 = orientation(s1.p,s1.q,s2.p);
	double o2 = orientation(s1.p,s1.q,s2.q);
	double o3 = orientation(s2.p,s2.q,s1.p);
	double o4 = orientation(s2.p,s2.q,s1.q);
	if (o1!=o2 && o3!=o4) return true;
	if (o1==0 && onSegment(s2.p,s1)) return true;
	if (o2==0 && onSegment(s2.q,s1)) return true;
	if (o3==0 && onSegment(s1.p,s2)) return true;
	if (o4==0 && onSegment(s2.q,s2)) return true;
	return false;
}

void solve(){
	int n;
	cin>>n;
	vector<point> np;	
	rep(i,0,n) {
		double x,y;
		cin>>x>>y;
		np.pb({point(x,y)});
	}
	double maks=0;
	if (n>4){
		rep(i,0,n) rep(j,i+1,n) maks=max(maks, e_dist(np[i],np[j]));		
	} else {
		rep(i,0,n) rep(j,i+1,n){
			rep(k,0,n) {
				if (k==i || k==j) continue;
				rep(l,k+1,n) {
					if (l==i || l==j) continue;
					if (s_intersection(segment(np[i],np[j]),segment(np[k],np[l]))) continue;
					maks=max(maks,e_dist(np[i],np[j]));
				}
			}
		}
		
	}
	cout<<fixed<<setprecision(20)<<maks<<"\n";
}

int main()
{
//	base();
//  freopen("input.txt", "r", stdin);
//  freopen("output.txt", "w", stdout);
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}




