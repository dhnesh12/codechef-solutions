#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

#define n	505
#define	DB	double
#define I64	long long
#define u64	unsigned I64
#define For(i,a,b)	for(int i=a;i<=b;i++)

int		N, M, T1, T2, P[n], Q[n];
I64		U, V, Ax, Ay, Bx, By, Cx, Cy, X[n], Y[n], Sx[n], Sy[n];
char	s[n];

struct	Nod {
	int a, b,z;
	double jj;
	I64	x, y;
	Nod(I64 _x = 0, I64 _y = 0, int _a = 0, int _b = 0) {
		x = _x;
		y = _y;
		a = _a;
		b = _b;
		z = y > 0 || x >= 0 && y >= 0;
		jj=atan2(y,x);
		if(y<0)jj+=100;
	}
	bool	operator ==	(const Nod&a)const {
		return	z == a.z && x * a.y == y * a.x;
	}
} A[n * n], B[n * n];

struct	Val {
	u64	I;
	DB	D;
	Val	operator +	(const Val&a) {
		u64	x = I + a.I;
		DB	y = D + a.D;
		return	(Val) {
			x + ((int)y), y - ((int)y)
		};
	}
	bool	operator <	(const Val&a)const {
		return	I < a.I || I == a.I && D < a.D;
	}
} Ans;

bool	Cmp1(const Nod&a, const Nod&b) {
	return a.jj<b.jj;
}
bool	Cmp2(int a, int b) {
	return	U * X[a] + V * Y[a] > U * X[b] + V * Y[b];
}

u64		sqr(I64 x) {
	if(x < 0)	x = -x;
	u64 y = x;

	return	y * y;
}
Val		Sqrt(u64 x) {
	if(!x)
		return	(Val) {
		0, 0
	};

	u64	y = (u64)sqrt(x);

	for(; (y + 1) * (y + 1) <= x; y++);

	return	(Val) {
		y, (x - y * y) / (sqrt(x) + y)
	};
}
Val		Dis(I64 x, I64 y) {
	return	Sqrt(sqr(x - Bx) + sqr(y - By)) + Sqrt(sqr(x - Cx) + sqr(y - Cy)) + Sqrt(sqr(Bx - Cx) + sqr(By - Cy));
}

void	Swap(int x) {
	int u = P[x], v = P[x - 1];
	swap(P[x - 1], P[x]);
	swap(Q[u], Q[v]);
	Sx[x - 1] += X[u] - X[v];
	Sy[x - 1] += Y[u] - Y[v];
}
void	Work(int u) {
	for(; Q[u] > 1;) {
		int v = P[Q[u] - 1];

		if(U * X[u] + V * Y[u] >= U * X[v] + V * Y[v])
			Swap(Q[u]);
		else
			break;
	}
}
void	Calc() {
	int l = 0, r = M + 1;

	for(; l + 1 < r;) {
		int Mid = l + r >> 1;
		U*X[P[Mid]] + V*Y[P[Mid]] >= 0 ? l = Mid : r = Mid;
	}

	Ans = max(Ans, Dis(Ax + Sx[l], Ay + Sy[l]));
}

int		main() {
	//freopen("tr.in","r",stdin); freopen("tr.out","w",stdout);
	cin >> N >> M >> Ax >> Ay >> Bx >> By >> Cx >> Cy;
	For(i, 1, N)	cin >> X[i] >> Y[i];
	int tot = N;
	N = 0;

	For(i, 1, tot)if(X[i] || Y[i])
		N++, X[N] = X[i], Y[N] = Y[i];

	M = min(M, N);
	Ans = Dis(Ax, Ay);

	For(i, 1, N)	For(j, i + 1, N)

	if(X[i] != X[j] || Y[i] != Y[j]) {
		A[++T1] = Nod(Y[j] - Y[i], X[i] - X[j], i, j);
		A[++T1] = Nod(Y[i] - Y[j], X[j] - X[i], i, j);
	}

	For(i, 1, N)	{
		A[++T1] = Nod(Y[i], -X[i], 0, 0);
		A[++T1] = Nod(-Y[i], X[i], 0, 0);
	}

	A[++T1] = Nod(1, 0, 0, 0);
	A[++T1] = Nod(0, 1, 0, 0);
	A[++T1] = Nod(-1, 0, 0, 0);
	A[++T1] = Nod(0, -1, 0, 0);
	sort(A + 1, A + T1 + 1, Cmp1);
	A[T1 + 1] = A[1];

	B[++T2] = Nod(1, 0, 0, 0);

	for(int i = 1, j; i <= T1; i = j + 1) {
		for(j = i; j + 1 <= T1 && A[j + 1] == A[j]; j++);

		For(k, i, j)	B[++T2] = Nod(A[i].x + A[j + 1].x, A[i].y + A[j + 1].y, A[k].a, A[k].b);
	}

	For(i, 1, N)	P[i] = i;
	U = B[1].x, V = B[1].y;
	sort(P + 1, P + N + 1, Cmp2);
	For(i, 1, N)	Q[P[i]] = i, Sx[i] = Sx[i - 1] + X[P[i]], Sy[i] = Sy[i - 1] + Y[P[i]];

	For(i, 1, T2) {
		U = B[i].x, V = B[i].y;

		if(B[i].a)	Work(B[i].a), Work(B[i].b);
		Calc();
	}

	sprintf(s + 1, "%.13lf", Ans.D);
	printf("%llu%s\n", Ans.I, s + 2);
}
