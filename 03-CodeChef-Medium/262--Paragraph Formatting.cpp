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

const int Maxn = 50005;
const int Maxp = 225; 

int t;
int m, n;
int my[Maxn], sum[Maxn];

int main()
{
	scanf("%d", &t);
	for (int tc = 1; tc <= t; tc++) {
		scanf("%d %d", &m, &n); m++;
		for (int i = 0; i < n; i++) {
			scanf("%d", &my[i]); my[i]++;
			sum[i] = my[i];
			if (i % Maxp) sum[i] += sum[i - 1];
		}
		printf("Case #%d:\n", tc);
		while (true) {
			char typ; scanf(" %c", &typ);
			if (typ == 'I') {
				int ind; scanf("%d", &ind); ind--;
				int p = ind / Maxp * Maxp;
				int lft = m;
				int res = 0;
				for (int i = 0; i < p; i += Maxp) {
					int j = i;
					int cur = 0;
					while (true)
						if (lft >= sum[i + Maxp - 1] - cur) { lft -= sum[i + Maxp - 1] - cur; break; }
						else {
							int f = upper_bound(sum + j, sum + i + Maxp, lft + cur) - sum - 1;
							res++; lft = m;
							if (f >= j) cur = sum[f];
							j = f + 1;
						}
				}
				for (int i = p; i <= ind; i++)
					if (lft >= my[i]) lft -= my[i];
					else { lft = m - my[i]; res++; }
				printf("%d\n", res + 1);
			} else if (typ == 'C') {
				int ind, len; scanf("%d %d", &ind, &len); ind--;
				my[ind] = len + 1;
				int j = ind / Maxp * Maxp;
				for (int i = j; i < j + Maxp && i < n; i++) {
					sum[i] = my[i];
					if (i % Maxp) sum[i] += sum[i - 1];
				}
			} else if (typ == 'E') break;
		}
		printf("\n");
	}
	return 0;
}