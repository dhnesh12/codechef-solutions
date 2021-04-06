#include <bits/stdc++.h>
#define FOR(k,a,b) for(int k(a); k < (b); ++k)
#define REP(k,a) for(int k=0; k < (a); ++k)
#define ABS(a) ((a)>0?(a):-(a))
using namespace std;

const double EPS = 1e-9;
double halfCirlceAngle;
double maxAngle;
double PIH = acos(0.0);
int L, R, D, N;

double calcAreaMinusCircle(double angle){
	double sa = sin(angle)*D / R;
	double ca = asin(min(1.0, sa));
	if (ca < PIH)
		ca = 2 * PIH - ca;
	double ra = PIH * 2 - angle - ca;
	double res = (sin(ra)*D - ra *R)* R / 2.0;
	assert(res >= 0);
	return res;
}

double calcSimpleArea(double start, double end){
	while (start + EPS < -PIH / 2 || start - EPS > PIH / 2){
		start += PIH;
		end += PIH;
		if (start + EPS > 2 * PIH)
		{
			start -= 4 * PIH;
			end -= 4 * PIH;
		}
	}
	if (end > PIH / 2 + EPS){
		return calcSimpleArea(start, PIH / 2) + calcSimpleArea(-PIH / 2, end - PIH);
	}
	double starty = tan(start)*L;
	double endy = tan(end)*L;
	double dist = ABS(endy - starty);
	return dist * L / 2;
}

double calcAngle(double startAngle, double circle1, double circle2, double& nextAngle){
	assert(startAngle + EPS > circle1);
	if (startAngle > circle2 - halfCirlceAngle - EPS && circle2 - startAngle < EPS + startAngle - circle1){
		nextAngle = min(circle2, maxAngle);
		return calcAreaMinusCircle(circle2 - startAngle);
	}
	else if (startAngle + EPS > circle1 + halfCirlceAngle && startAngle < EPS + circle2 - halfCirlceAngle){
		nextAngle = min(circle2 - halfCirlceAngle, maxAngle);
		return calcSimpleArea(startAngle, nextAngle);
	}
	else{
		if (circle2 - circle1 > 2 * halfCirlceAngle + EPS)
			nextAngle = circle1 + halfCirlceAngle;
		else
			nextAngle = (circle2 + circle1) / 2;
		nextAngle = min(nextAngle, maxAngle);
		return calcAreaMinusCircle(nextAngle - startAngle);
	}
}

int main() {

	int T,sumN = 0;
	scanf("%d", &T);
	REP(tc, T){
		scanf("%d %d %d %d", &N, &R, &D, &L);
		sumN += N;
		assert(R <= D);
		assert(R + D < L);
		vector<double> angles;
		REP(i, N){
			double x, y;
			scanf("%lf %lf", &x, &y);
			double a = atan2(y, x);
			angles.push_back(a);
		}
		sort(angles.begin(), angles.end());
		angles.erase(unique(angles.begin(), angles.end()), angles.end());
		halfCirlceAngle = asin(static_cast<double>(R) / D);
		double res = 0, actAngle = angles.back() - 4 * PIH, circle1 = angles.back() - 4 * PIH, circle2 = angles[0], nextAngle;
		maxAngle = angles.back();
		int actIndex = 0;
		while (actAngle + EPS < maxAngle){
			res += calcAngle(actAngle, circle1, circle2, nextAngle);
			if (nextAngle + EPS > circle2){
				++actIndex;
				circle1 = circle2;
				if (actIndex == angles.size()){
					circle2 = angles[0] + 4 * PIH;
				}
				else{
					circle2 = angles[actIndex];
				}
			}
			actAngle = nextAngle;
		}
		printf("%.7f\n", res);
	}
	assert(sumN <= 5000000);
	return 0;
}

