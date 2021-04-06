#include <cstdio>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <string>
#include <cstring>
#include <sstream>
#include <cassert>
#include <algorithm>
using namespace std;
 
const int Maxk = 200005;
 
int t;
int toland, tofly, m, n, k;
int cnt[Maxk];
int wasland, wasfly;
 
int main()
{
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d %d %d", &toland, &tofly, &m, &n, &k);
		assert(m && n);
		fill(cnt, cnt + k + n + 2, 0);
		wasland = wasfly = 0;
		for (int i = 0; i <= k; i++) {
			if (i > 0 && i % m == 0) toland++;
			tofly += cnt[i];
			//if (i < k)
				if (toland > 0) { 
					wasland++; 
					cnt[i + n]++; 
					toland--;
				} else if (tofly > 0) { wasfly++; tofly--; }
		}
		for (int i = k + 1; i <= k + n + 1; i++)
			tofly += cnt[i];
		if ((k + 1) % m == 0) toland++;
		printf("%d %d %d %d\n", wasland, wasfly, toland, tofly);
	}
	return 0;
} 