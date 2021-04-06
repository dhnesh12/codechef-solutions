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

typedef pair <int, int> ii;

const int Maxn = 2005;
const int Maxk = 21;

int nim[Maxk][Maxn];
int tk[Maxn * Maxk];
int t;
int n, k;
char str[Maxn];
vector <ii> seq;

int main()
{
	int my = 0;
	for (int i = 1; i < Maxk; i++) {
		fill(tk, tk + Maxn * Maxk, -Maxn);
		nim[i][0] = 0; tk[0] = 0;
		for (int j = 1; j < Maxn; j++) {
			while (tk[nim[i][j]] >= j - i) nim[i][j]++;
			for (int z = 0; z <= j - z; z++)
				tk[nim[i][z] ^ nim[i][j - z]] = j;
		}
	}
	scanf("%d", &t);
	while (t--) {
		seq.clear();
		scanf("%d %d", &n, &k);
		scanf("%s", str);
		for (int i = 0; i < n; i++)
			if (str[i] == '1')
				if (seq.empty() || seq.back().second + 1 < i) seq.push_back(ii(i, i));
				else seq.back().second++;
		int res = 0;
		for (int i = 0; i < seq.size(); i++)
			res ^= nim[k][seq[i].second - seq[i].first + 1];
		if (res == 0) printf("Johnny wins\n");
		else {
			bool br = false;
			int lef, rig;
			for (int i = k; i > 0 && !br; i--)
				for (int j = 0; j < seq.size() && !br; j++) {
					int len = seq[j].second - seq[j].first + 1;
					for (int z = 0; z + i <= len && !br; z++) {
						int cand = res ^ nim[k][len] ^ nim[k][z] ^ nim[k][len - i - z];
						if (cand == 0) { br = true; lef = seq[j].first + z; rig = seq[j].first + z + i - 1; }
					}
				}
			for (int i = lef; i <= rig; i++)
				str[i] = '0';
			printf("Mary wins\n");
			printf("%s\n", str);
		}
		printf("\n");
	}
	return 0;
}