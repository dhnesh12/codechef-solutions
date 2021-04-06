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

const int Maxn = 100005;
const int Maxp = 2;
const int Maxv = 2;

int t;
int n;
int cnt[Maxn];
int my[Maxp][Maxv];
int res;
int best[Maxp][Maxv];

void Gen(int lvl)
{
	if (lvl >= 2) {
		int mn = Maxn, mx = -Maxn;
		for (int i = 1; i <= n; i++) {
			mn = min(mn, cnt[i]);
			mx = max(mx, cnt[i]);
		}
		int cand = (mn < cnt[n - 1] && cnt[n - 1] < mx) + (mn < cnt[n] && cnt[n] < mx);
		if (cand > res) {
			res = cand;
			for (int i = 0; i < Maxp; i++)
				for (int j = 0; j < Maxv; j++)
					best[i][j] = my[i][j];
		}
	} else for (my[lvl][0] = 1; my[lvl][0] <= n; my[lvl][0]++) if (my[lvl][0] != n - 1 + lvl)
			 for (my[lvl][1] = my[lvl][0] + 1; my[lvl][1] <= n; my[lvl][1]++) if (my[lvl][1] != n - 1 + lvl) {
			 	cnt[my[lvl][0]]++; cnt[my[lvl][1]]++;
			 	Gen(lvl + 1);
			 	cnt[my[lvl][0]]--; cnt[my[lvl][1]]--;
			 }
}

bool savBoth()
{
	int mn = Maxn, mnind, mx = -Maxn, mxind;
	for (int i = 1; i <= n - 2; i++) {
		if (cnt[i] < mn) { mn = cnt[i]; mnind = i; }
		if (cnt[i] > mx) { mx = cnt[i]; mxind = i; }
	}
	int a = cnt[n - 1], b = cnt[n];
	int sav = 1;
	while (sav == mnind || sav == mxind) sav++;
	if (a == mn) { a++; best[1][0] = n - 1; }
	else best[1][0] = sav;
	if (b == mn) { b++; best[0][0] = n; }
	else best[0][0] = sav;
	mx += 2;
	best[1][1] = mxind; best[0][1] = mxind;
	return mn < a && a < mx && mn < b && b < mx;
}

bool savOne(bool sec)
{
	int mn = Maxn, mnind, mx = -Maxn, mxind;
	for (int i = 1; i <= n - 2; i++) {
		if (cnt[i] < mn) { mn = cnt[i]; mnind = i; }
		if (cnt[i] > mx) { mx = cnt[i]; mxind = i; }
	}
	int befmxind = mxind;
	int a = cnt[n - 1], b = cnt[n];
	int sav = 1;
	while (sav == mnind || sav == mxind) sav++;
	int oth1 = n, oth2 = n - 1;
	if (sec) { swap(a, b); swap(oth1, oth2); }
	if (a < mn) { mn = a; mnind = oth2; }
	if (a > mx) { mx = a; mxind = oth2; }
	if (b == mn) { b++; best[0][0] = oth1; }
	else best[0][0] = sav;
	best[1][1] = mxind; mx++;
	best[1][0] = sav;
	if (mxind == oth2) best[0][1] = befmxind;
	else { best[0][1] = mxind; mx++; }
	return mn < b && b < mx;
}

int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		fill(cnt, cnt + n + 1, 0);
		for (int i = 0; i < n - 2; i++) {
			int a; scanf("%d", &a);
			cnt[a]++;
		}
		for (int i = 0; i < n - 2; i++) {
			int a; scanf("%d", &a);
			cnt[a]++;
		}
		if (n <= 4) {
			res = -1;
			Gen(0);
			if (res == 0) printf("none\n");
			else if (res == 1) printf("one\n");
			else printf("both\n");
		} else if (savBoth()) printf("both\n");
		  else if (savOne(false)) printf("one\n");
		  else if (savOne(true)) {
		  	for (int i = 0; i < Maxv; i++)
		  		swap(best[0][i], best[1][i]);
		  	printf("one\n");
		  } else {
		  	printf("none\n");
		  	best[0][0] = 1; best[0][1] = n;
		  	best[1][0] = 1; best[1][1] = n - 1;
		  }
		printf("%d %d\n", best[0][0], best[0][1]);
		printf("%d %d\n", best[1][0], best[1][1]);
	}
	return 0;
}