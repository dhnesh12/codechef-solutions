#include <stdio.h>
#include <memory.h>
#include <math.h>
#pragma optimization_level 3
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math,O3")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#pragma GCC optimize("Ofast")//Comment optimisations for interactive problems (use endl)
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimization ("unroll-loops")

#define ll long long
#define ac 100
#define ld double
double P[ac][ac];
double A[ac][ac];
double B[ac][ac];
int N;

void normalize()
{
	for (int i = 0; i < N; i++)
	{
		ld s = 0;
		for (int j = 0; j < N; j++)
			s += P[i][j];
		if (s < 1e-8)
		{
			P[i][i] = 1.l;
		}
		else
		{
			for (int j = 0; j < N; j++)
			P[i][j] /= s;
		}
	}
}

void mult()
{
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				P[i][j] += A[i][k] * A[k][j];
}

void expw(ll w)
{
	while (w--)
	{  memset(P, 0, sizeof(P)); mult(); normalize(); memcpy(A, P, sizeof(A)); }
}

int F[ac], IF[ac], O[ac];

int main()
{
	int n, m, s; 
	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < s; i++) scanf("%d", &(F[i])), F[i]--, IF[F[i]] = 1;
	N = 2 * n - s + 2;
	for (int i = 0; i < m; i++)
	{
		int a, b; scanf("%d %d", &a, &b); a--; b--;
		P[a][b] = 1;
	}
	normalize();
	memcpy(B, P, sizeof(B));
	
	for (int k = 0; k < s; k++)
	{
		memset(P, 0, sizeof(P));
		memset(O, 0, sizeof(O));
		int y = n;
		for (int i = 0; i < n; i++)
		{
			if (!IF[i] || F[k] == i) O[i] = y++;
			else O[i] = 2 * n - s + 1;
		}
		P[n - 1][n - 1] = P[O[n - 1]][O[n - 1]] = 1.l;

		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (F[k] == j)
				{
					P[i][O[j]] = B[i][j];
					P[O[i]][O[j]] = B[i][j];
				}
				else if (IF[j])
				{
					P[i][j] = B[i][j];
					P[O[i]][j] = B[i][j];
				}
				else
				{
					P[i][j] = B[i][j];
					P[O[i]][O[j]] = B[i][j];
				}
			}
		}

		normalize();

		memcpy(A, P, sizeof(A));
		memset(P, 0, sizeof(P));

		expw(111);
		printf("%.15lf\n", P[O[0] * (F[k] == 0)][O[n - 1]]);
	//	cout << '\n';
	}
}
