#include <bits/stdc++.h>
using namespace std;

typedef pair <int, int> ii;
typedef pair <ii, ii> iiii;

const int Maxr = 505;
const int day = 1440;
const int Maxl = 15;

int comparator;
int id[Maxr][Maxr];
vector <int> seq[Maxr]; 
int t;
int n, r;
char str[Maxl];
int fre[Maxr];
int lst;
int bef;

bool Less(const int &a, const int &b)
{
	return id[comparator][a] < id[comparator][b];
}

void Solve(const string &s, int tim, int g)
{
	int h = 0;
	for (int i = 0; i < s.length(); i++)
		h = (33 * h + int(tolower(s[i]) - 'a' + 1)) % r;
	h = (h + bef) % r;
	int mn = fre[h];
	for (int i = 0; i < seq[r].size(); i++) {
		int ind = seq[r][i];
		int got = (h + ind) % r;
		if (fre[got] <= tim) {
			fre[got] = tim + 60 * g;
			printf("%d\n", id[r][ind]);
			bef = (bef + id[r][ind]) % r;
			return;
		} else mn = min(mn, fre[got]);
	}
	int lose = mn - tim;
	printf("-%d\n", lose); bef = (bef + lose) % r; 
}

int main()
{
	for (int i = 0; i < Maxr; i++) if (i % 33 != 0) {
		fill(id[i], id[i] + i, -1);
		int cur = 0;
		int a = 0, b = 1, c = 0;
		int lft = i;
		int ind = 0;
		id[i][cur] = ind++; lft--;
		set <int> S;
		while (lft > 0) {
			int d = (a + b + c) % i;
			cur = (cur + d) % i;
			a = b; b = c; c = d;
			int mask = ((a * Maxr + b) * Maxr + c) * Maxr + cur;
			if (S.find(mask) != S.end()) break;
			S.insert(mask);
			if (id[i][cur] == -1) { lft--; id[i][cur] = ind; }
			ind++;
		}
		comparator = i;
		for (int j = 0; j < i; j++) if (id[i][j] != -1)
			seq[i].push_back(j);
		sort(seq[i].begin(), seq[i].end(), Less);
	}
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d", &n, &r);
		bef = 0;
		fill(fre, fre + r, 0);
		lst = 0;
		for (int i = 0; i < n; i++) {
			int h, m, g; scanf("%d %d %d", &h, &m, &g);
			int mins = h * 60 + m;
			if (mins < lst) mins += ((lst - 1 - mins) / day + 1) * day;
			lst = mins;
			scanf("%s", str);
			Solve(str, lst, g);
		}
	}
	return 0;
}