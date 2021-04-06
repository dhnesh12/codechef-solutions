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
 
typedef long long ll;
 
const int Maxn = 7500;
const int Maxl = 1000005;
const int Inf = 1000000001;
const int Maxm = 20;
 
char tmp[Maxl];
int n, k;
string str[Maxn];
vector <int> specL[Maxn], specR[Maxn];
vector <int> goodL[Maxn], goodR[Maxn];
vector <int> L[Maxn], R[Maxn];
vector <vector <int> > dp[Maxn];
ll res;
 
int getMax(const vector <vector <int> > &dp, int l, int r)
{
	int res = 0;
	for (int i = Maxm - 1; i >= 0; i--)
		if (l + (1 << i) <= r + 1) {
			res = max(res, dp[l][i]);
			l += 1 << i;
		}
	return res;
}
 
int Get(int ind, int a, int b)
{
	if (a > str[ind].length() || b > str[ind].length()) return Inf;
	int lef = specL[ind][a], rig = specR[ind][b];
	if (lef > rig) return Inf;
	lef = max(lef, goodR[ind][b]), rig = min(rig, goodL[ind][a]);
	if (lef > rig) return 0;
	return a + b - getMax(dp[ind], lef, rig);
}
 
int main()
{
	while (scanf("%d %d", &n, &k) == 2) {
		int mn = Maxl;
		for (int i = 0; i < n; i++) {
			scanf("%s", tmp);
			str[i] = tmp; mn = min(mn, int(str[i].length()));
			specL[i] = vector <int>(str[i].length() + 1, Inf); goodL[i] = vector <int>(str[i].length() + 1, Inf);
			L[i] = vector <int>(str[i].length() + 1);
			int spec = 0, good = 0;
			specL[i][0] = 0; goodL[i][0] = 0; L[i][0] = 0;
			for (int j = 0; j < str[i].length(); j++) {
				if (str[i][j] == '?' || str[i][j] == '4') { spec++; specL[i][spec] = j + 1; }
				if (str[i][j] == '4') { good++; goodL[i][good] = j + 1; }
				L[i][j + 1] = good;
			}
 
			specR[i] = vector <int>(str[i].length() + 1, -Inf); goodR[i] = vector <int>(str[i].length() + 1, -Inf);
			R[i] = vector <int>(str[i].length() + 1);
			spec = 0; good = 0;
			specR[i][0] = str[i].length(); goodR[i][0] = str[i].length(); R[i][str[i].length()] = 0;
			for (int j = int(str[i].length()) - 1; j >= 0; j--) {
				if (str[i][j] == '?' || str[i][j] == '7') { spec++; specR[i][spec] = j; }
				if (str[i][j] == '7') { good++; goodR[i][good] = j; }
				R[i][j] = good;
			}
 
			dp[i].resize(str[i].length() + 1);
			for (int j = 0; j <= str[i].length(); j++) {
				dp[i][j] = vector <int>(Maxm, 0); dp[i][j][0] = L[i][j] + R[i][j];
			}
			for (int k = 1; k < Maxm; k++)
				for (int j = 0; j + (1 << k) <= str[i].length() + 1; j++) {
					int nj = j + (1 << k - 1);
					dp[i][j][k] = max(dp[i][j][k - 1], dp[i][nj][k - 1]);
				}
		}
		res = 0;
		int pnt = 0;
		for (int i = mn; i >= 0; i--) {
			while (true) {
				ll cand = 0;
				for (int j = 0; j < n; j++)
					cand += Get(j, i, pnt);
				if (cand <= k) pnt++;
				else break;
			}
			res += pnt;
		}
		printf("%lld\n", res - 1ll);
	}
	return 0;
} 