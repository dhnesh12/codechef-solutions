#include <bits/stdc++.h>
#define LL long long
#define eps 1e-8
using namespace std;

template<class T> inline
void read(T& x) {
	int f = 1; x = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9')   {if (ch == '-') f = -1; ch = getchar();}
	while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
	x *= f;
}

/*============ Header Template ============*/

double sqr(double x) {return x * x;}

int T, n, P, M, B;
double r[5];
double R, L1, L2, L, A, D;

int main() {
	read(T);
	read(n), read(P), read(M), read(B);
	scanf("%lf%lf%lf%lf", &r[1], &r[2], &r[3], &r[4]);
	R = 2 * r[2];
	L1 = sqr(R) / (2 * r[1]);
	L2 = sqr(R) / (2 * r[2]);
	L = (L1 + L2) / 2.0;
	A = (L2 - L1) / 2.0;
	double x3 = sqrt(sqr(A) - sqr(L) + A * sqr(R) / r[3]);
	if (fabs(r[4] - (A * sqr(R) / (sqr(L) + sqr(x3 + 2 * A) - sqr(A)))) < eps) D = 2 * A;
	else D = -2 * A;
	double ans = 0;
	while (T--) {
		n = 1LL * n * P % M + B;
		if (n <= 4) {
			ans += r[n];
		} else {
			double x = x3 + D * (n - 3);
			double rn = A * sqr(R) / (sqr(L) + sqr(x) - sqr(A));
			ans += rn;
		}
	}
	printf("%.6lf\n", ans);
	return 0;
}