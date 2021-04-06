#include <bits/stdc++.h>
using namespace std;

const int Maxn = 105;

int T;
int n;
vector <int> seq;
int bot, tp;
int res[Maxn];

int Ask(int k, int x)
{
	printf("? %d %d\n", k, x); fflush(stdout);
	int res; scanf("%d", &res);
	return res;
}

void Solve(int l, int r, int A, int B)
{
	if (l == r)
		while (seq.size() < B - bot)
			seq.push_back(l);
	else {
		int m = (l + r + 1) >> 1;
		int C = Ask(1, m);
		if (C > A) Solve(l, m - 1, A, C);
		if (C < B) Solve(m, r, C, B);
	}
}

int main()
{
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		bot = Ask(1, 1);
		tp = Ask(1, 1000000);
		seq.clear();
		if (bot < tp) Solve(1, 1000000 - 1, bot, tp);
		while (seq.size() < n) seq.push_back(1000000);
		vector <int> un = seq;
		un.erase(unique(un.begin(), un.end()), un.end());
		for (int i = 0; i < n; i++) {
			int l = 0, r = int(un.size()) - 1;
			while (l <= r) {
				int mid = l + r >> 1;
				int inv = bot;
				for (int j = 0; j < i; j++)
					if (res[j] > un[mid]) inv++;
				for (int j = 0; j < seq.size(); j++)
					if (un[mid] > seq[j]) inv++;
				if (Ask(i + 2, un[mid]) >= inv) l = mid + 1;
				else r = mid - 1;
			}
			l--;
			res[i] = un[l];
			int ind = lower_bound(seq.begin(), seq.end(), res[i]) - seq.begin();
			seq.erase(seq.begin() + ind);
		}
		printf("!");
		for (int i = 0; i < n; i++)
			printf(" %d", res[i]);
		printf("\n");
		fflush(stdout);
	}
    return 0;
}
