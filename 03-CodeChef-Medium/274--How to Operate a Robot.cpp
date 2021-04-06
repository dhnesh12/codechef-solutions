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
 
const int Maxn = 1005;
 
int t;
int n;
char B[Maxn][Maxn];
int curr, curc;
 
void Move(int r2, int c2)
{
	if (curr < r2) { printf("D"); curr++; }
	else if (curr > r2) { printf("U"); curr--; }
	else if (curc < c2) { printf("R"); curc++; }
	else { printf("L"); curc--; }
}
 
void Down(int r, int dir)
{
	if (r >= n) r = n - 1;
	while (curr < r)
		if (B[curr + 1][curc] == '.') Move(curr + 1, curc);
		else {
			Move(curr, curc - dir);
			Move(curr + 1, curc);
			if (curr < n - 1) {
				Move(curr + 1, curc);
				Move(curr, curc + dir);
			}
		}
}
 
void Solve(int r1, int r2, int dir)
{
	while (true) {
		int targ = curr == r1? r2: r1;
		if (B[targ][curc] == '.') {
			Move(targ, curc);
			if (curc + dir < 0 || curc + dir >= n) return;
			if (B[curr][curc + dir] == '#') {
				Move(r1 + r2 - curr, curc);
				Move(curr, curc + dir);
			} else Move(curr, curc + dir);
		} else {
			if (curc + dir < 0 || curc + dir >= n) return;
			Move(curr, curc + dir);
		}
	}
}
 
int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%s", B[i]);
		curr = 0; curc = 0;
		int dir = -1;
		for (int i = 0; i + 1 < n; i += 2) {
			Down(i, dir);
			dir = -dir;
			Solve(i, i + 1, dir);
		}
		if (n % 2) {
			Down(n - 2, dir);
			dir = -dir;
			Solve(n - 2, n - 1, dir);
		}
		printf("\n");
	}
	return 0;
} 
