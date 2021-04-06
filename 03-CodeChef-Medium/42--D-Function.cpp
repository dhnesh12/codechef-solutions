// In The Name Of The Queen
#include<bits/stdc++.h>
using namespace std;
const int N = 202, LG = 61, Mod = 1e9 + 7;
struct Matrix
{
	int n, m, A[N][N];
	inline Matrix(int _n = 0, int _m = 0) : n(_n), m(_m) {memset(A, 0, sizeof(A));}
	inline Matrix operator * (Matrix &X)
	{
	    Matrix R(n, X.m);
	    for (int i = 0; i < n; i ++)
	        for (int k = 0; k < m; k ++)
	            for (int j = 0; j < X.m; j ++)
	                R[i][j] = (R[i][j] + 1LL * A[i][k] * X[k][j]) % Mod;
	    return (R);
	}
	inline Matrix operator ^ (long long Pw)
	{
	    Matrix R(n, n), T = * this;
	    for (int i = 0; i < n; i ++)
	        R[i][i] = 1;
	    for (; Pw; Pw >>= 1, T = T * T)
	        if (Pw & 1)
	            R = R * T;
	    return (R);
	}
	inline int * operator [] (int i)
	{
	    return (A[i]);
	}
};
int m, k, X, W[N];
long long n, S[N];
int main()
{
	scanf("%d%d%d%lld", &X, &k, &m, &n);
	for (int i = 1; i <= k; i ++)
	    scanf("%lld", &S[i]);
	for (int i = 1; i <= m; i ++)
	    scanf("%d", &W[i]);
	sort(S + 1, S + k + 1);
	if (n == 0)
	    return !printf("%lld\n", X);
	if (S[k] == n)
	    return !printf("0\n");
	Matrix A(1, m), M[LG];
	for (int i = 0; i < LG; i ++)
	    M[i] = Matrix(m, m);
	A[0][m - 1] = X;
	for (int i = 0; i < m - 1; i ++)
	    M[0][i + 1][i] = 1;
	for (int i = 0; i < m; i ++)
	    M[0][i][m - 1] = W[m - i];
	M[0][0][m - 1] ++;
	for (int i = 1; i < LG; i ++)
	    M[i] = M[i - 1] * M[i - 1];
	for (int i = 1; i <= k; i ++)
	{
	    for (int b = 0; b < LG; b ++)
	        if ((S[i] - S[i - 1] - 1) >> b & 1LL)
	            A = A * M[b];
	    int temp = A[0][0];
	    for (int j = 1; j < m; j ++)
	        A[0][j - 1] = A[0][j];
	    A[0][m - 1] = temp;
	}
	for (int b = 0; b < LG; b ++)
	    if ((n - S[k] - 1) >> b & 1LL)
	        A = A * M[b];
	int Fn = 0;
	for (int i = 0; i < m; i ++)
	    Fn = (Fn + 1LL * A[0][i] * W[m - i]) % Mod;
	return !printf("%d\n", Fn);
}
