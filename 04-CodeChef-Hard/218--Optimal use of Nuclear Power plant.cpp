#include<bits/stdc++.h>
using namespace std;
typedef double db;
typedef long long ll;
typedef pair<int, int> pii;
const db eps = 1e-3;
const db eps2 = 1e-6;
const db pi = acos(-1.0);

db nowr, d;
db sqr(db x) { return x * x;}
db f(db x) {
	db y = sqrt(sqr(nowr) - sqr(x)), nd = d + nowr - x;
	return sqr(nd) * log(y / nd + sqrt(1 + sqr(y / nd))) + y * sqrt(sqr(nd) + sqr(y));
}
db simpson(db l, db r) {
	return (f(l) + f((l + r) / 2) * 4 + f(r)) * (r - l) / 6;
}
db Int(db l, db r, db v, db EPS) {
	db mid = (l + r) / 2;
	db al = simpson(l, mid), ar = simpson(mid, r);
	if(fabs(v - al - ar) < 15 * EPS) return al + ar + (al + ar - v) / 15;
	return Int(l, mid, al, EPS / 2) + Int(mid, r, ar, EPS / 2);
}
db calc(db l, db r) { return Int(l, r, simpson(l, r), eps);}


int sign(db x) { return (x > eps) - (x < -eps);}
int dcmp(db x, db y) { return sign(x - y);}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cout << fixed << setprecision(10);
	int _; cin >> _;
	const int times = 30;
	while(_--) {
		db D; cin >> D >> d;
		db l = (D - d) / 2, r = D - d;
		for(int i = 0; i < times; i++) {
			nowr = (l + r) / 2;
			if(calc(-nowr, nowr) - pi * nowr * nowr * D > -eps2) {
				r = nowr;
			} else {
				l = nowr;
			}
		}
		cout << nowr << '\n';
	}
	return 0;
}