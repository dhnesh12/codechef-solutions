#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;
 
typedef long double ld;
 
const int Maxm = 6;
const int Maxn = 105;
 
int Va, Vb, Sa, Sb, Ma;
ld dp[Maxm][Maxn][Maxn];
ld B[Maxm][Maxn][Maxn];
 
ld Get(int d, int r1, int c1, int r2, int c2)
{
	if (r1 <= 0) r1 = 1;
	if (c1 <= 0) c1 = 1;
	return B[d][r2][c2] - B[d][r1 - 1][c2] - B[d][r2][c1 - 1] + B[d][r1 - 1][c1 - 1];
}
 
ld Get(ld x)
{
	for (int i = 0; i <= Ma; i++)
		for (int r = 1; r <= Va; r++)
			for (int c = 1; c <= Vb; c++) {
				dp[i][r][c] = 0;
				B[i][r][c] = B[i][r - 1][c] + B[i][r][c - 1] - B[i][r - 1][c - 1];
				if (i > 0) dp[i][r][c] = max(dp[i][r][c], dp[i - 1][(r + 1) / 2][(c + 1) / 2]);
				int tot = (Sa + 1) * (Sb + 1);
				int both = r <= Sb && c <= Sa? (Sb - r + 1) * (Sa - c + 1): 0;
				int w1 = c <= Sa? (Sa - c + 1) * (Sb + 1): 0; w1 -= both;
				int w2 = r <= Sb? (Sb - r + 1) * (Sa + 1): 0; w2 -= both;
				int lft = tot - (both + w1 + w2);
				ld f = (w1 / ld(tot) + both / ld(tot) * x + Get(i, r - Sb, c - Sa, r, c) / ld(tot)) / ld(1.0 - 1.0l / ld(tot));
				dp[i][r][c] = max(dp[i][r][c], f);
				B[i][r][c] += dp[i][r][c];
			}
	return dp[Ma][Va][Vb];
}
 
int main()
{
	scanf("%d %d %d %d %d", &Va, &Vb, &Sa, &Sb, &Ma);
	ld lef = 0, rig = 1;
	for (int i = 0; i < 30; i++) {
		ld mid = (lef + rig) / 2;
		if (Get(mid) >= mid) lef = mid;
		else rig = mid;
	}
	cout << fixed << setprecision(10) << lef << endl;
	return 0;
} 