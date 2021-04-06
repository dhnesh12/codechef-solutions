#include <bits/stdc++.h>
using namespace std;

#define sq(x) ((x)*(x))
#define N 50

typedef long double ld;
int n;
ld x[N], y[N], z[N], r[N], rr[N], in[N], out[N];

struct circle{
    circle(){
        x = y = r = 0;
    }
    circle(ld x_, ld y_, ld r_){
        x = x_; y = y_; r = r_;
    }
    ld x,y,r;
    bool operator <(const circle t)const{
        if (x != t.x) return x < t.x;
        if (y != t.y) return y < t.y;
        return r < t.r;
    }
    bool operator ==(const circle t)const{
        return x == t.x && y == t.y && r == t.r;
    }
}C[2][N];

int CN[2];

const ld pi = acos(-1.0);

ld norm(ld a) {
    while (a < 0) a += 2 * pi;
    while (a >= 2 * pi) a -= 2 * pi;
    return a;
}

void push(vector<pair<ld, int> > &v, ld s, ld e) {
    s = norm(s);
    e = norm(e);
    v.push_back(make_pair(s,1));
    v.push_back(make_pair(e,-1));
    if (s > e) {
        v.push_back(make_pair(0,1));
        v.push_back(make_pair(2*pi,-1));
    }
}

ld solve(ld zz) {
	ld ans = 0;
	for (int i=0; i<2; i++) {
		CN[i] = n;
		sort(C[i],C[i]+CN[i]);
		CN[i] = unique(C[i],C[i]+CN[i]) - C[i];
	}
	for (int i=0; i<n; i++) {
		ld d = fabs(zz - z[i]);
		if (d >= r[i]) {
			in[i] = out[i] = 0;
		}
		else {
			in[i] = rr[i] - sqrt(sq(r[i]) - sq(d));
			out[i] = rr[i] + sqrt(sq(r[i]) - sq(d));
		}
		C[0][i] = circle(x[i],y[i],out[i]);
		C[1][i] = circle(x[i],y[i],in[i]);
	}
	for (int k=0; k<2; k++) {
		for (int c=0; c<CN[k]; c++) {
			if (C[k][c].r <= 0) continue;
			vector<pair<ld, int> > intv;
			intv.push_back(make_pair(0.,0));
			intv.push_back(make_pair(2*pi,0));

			for (int i=0; i<n; i++) {
				ld d2 = sq(x[i] - C[k][c].x) + sq(y[i] - C[k][c].y);
				ld orp2 = sq(out[i] + C[k][c].r);
				ld orm2 = sq(out[i] - C[k][c].r);
				ld irp2 = sq(in[i] + C[k][c].r);
				ld irm2 = sq(in[i] - C[k][c].r);

				if (d2 >= orp2) continue;
				if (in[i] >= C[k][c].r && d2 <= irm2) continue;
				if (C[k][c].r >= out[i] && d2 <= orm2) continue;
				if ((out[i] >= C[k][c].r && C[k][c].r >= in[i] && d2 <= irm2 && d2 <= orm2) || (d2 >= irp2 && out[i] >= C[k][c].r && d2 <= orm2)) {
					intv.push_back(make_pair(0.,1));
					break;
				}

				ld base = atan2(y[i]-C[k][c].y,x[i]-C[k][c].x);
				ld dif1 = (sq(C[k][c].r) + d2 - sq(out[i])) / (2 * C[k][c].r * sqrt(d2));
				ld dif2 = (sq(C[k][c].r) + d2 - sq(in[i])) / (2 * C[k][c].r * sqrt(d2));
				bool oseg = orp2 > d2 && d2 > orm2;
				bool iseg = irp2 > d2 && d2 > irm2;
				if (oseg && !iseg) {
					dif1 = acos(dif1);
					push(intv,base-dif1,base+dif1);
				} else if (iseg && !oseg) {
					dif2 = acos(dif2);
					push(intv,base+dif2,base-dif2);
				} else {
					dif1 = acos(dif1);
					dif2 = acos(dif2);
					push(intv,base-dif1,base-dif2);
					push(intv,base+dif2,base+dif1);
				}
			}
			sort(intv.begin(),intv.end());
			ld last = intv[0].first;
			vector<pair<ld, int> > tmp = {intv[0]};
			for (int u=1; u<intv.size(); u++) {
				if (fabs(last-intv[u].first) < 1e-8) {
					tmp.back().second += intv[u].second;
				}
				else {
					last = intv[u].first;
					tmp.push_back(intv[u]);
				}
			}
			intv = tmp;
			int cnt = intv[0].second;

			for (int u=1; u<intv.size(); u++) {
				if (cnt == 0) {
					ld st = intv[u-1].first, ed = intv[u].first;
					ld d = C[k][c].r * (C[k][c].r * (ed - st) + C[k][c].x * (sin(ed) - sin(st)) - C[k][c].y * (cos(ed) - cos(st))) / 2;
					if (k == 0) ans += d;
					else ans -= d;
				}
				cnt += intv[u].second;
			}
		}
	}
    return ans;
}


const ld ep = 1e-5;

inline int sgn(ld a) {
    return (a > ep) - (a < -ep);
}
inline ld func(ld a, ld b) {
    return (solve(a) + 4 * solve((a + b) / 2) + solve(b)) * (b - a) / 6;
}
ld calc(ld a, ld b) {
    ld c = (a + b) / 2;
    ld l = func(a, c);
    ld r = func(c, b);
    ld t = func(a, b);
    return sgn(l + r - t) ? calc(a, c) + calc(c, b) : t;
}

double tmp;
void scanld(ld &x) {
	scanf("%lf", &tmp);
    x = tmp;
    return;
}

void printld(ld x) {
	printf("%.12lf\n", (double) x);
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i ++) {
		scanld(x[i]), scanld(y[i]), scanld(z[i]), scanld(rr[i]), scanld(r[i]);
    }
    vector <ld> v;
    for (int i = 0; i < n; i ++) v.push_back(z[i] - r[i]), v.push_back(z[i] + r[i]);
    sort(v.begin(), v.end());
    ld sum = 0;
    for (int i = 1; i < v.size(); i ++) {

		vector<int> ins;
		for (int j = 0; j < n; j ++) {
			if (z[j] - r[j] <= v[i-1] && v[i] <= z[j] + r[j]) {
				ins.push_back(j);
			}
		}
		if (ins.size() == 1) {
			int j = ins[0];
			ld vol = 2 * pi * rr[j] * sq(r[j]);
			ld up = asin((v[i] - z[j]) / r[j]), low = asin((v[i-1] - z[j]) / r[j]);
			vol *= (up - low + 0.5 * (sin(2 * up) - sin(2 * low)));
			sum += vol;
			continue;
		}
		if (ins.size() == 0) continue;
		sum += calc(v[i-1], v[i]);
    }
    printld(sum);
    return 0;
}
