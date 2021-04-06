#include <bits/stdc++.h>
using namespace std;

const int SIZE = 1e2 + 5;

int tmp, n, top;
int ls[SIZE], sta[SIZE], fa[SIZE];

int query(int x, int l, int r) {
	printf("Q %d %d %d\n", x, l, r);
	fflush(stdout);
	char s[10]; scanf("%s", s);
	return s[0] == 'Y';
}

int main() {
	scanf("%d", &tmp);
	while (tmp --) {
		scanf("%d", &n); top = 0;
		memset(sta, 0, sizeof(sta)); memset(fa, 0, sizeof(fa));
		for (int i = 1, lson = 0; i <= n; sta[++ top] = i ++, lson = 0) {
			for ( ; top && query(sta[top], ls[sta[top]], i - 1); -- top)
				lson = sta[top], fa[sta[top]] = sta[top - 1];
			if (ls[i] = i, lson) fa[lson] = i, ls[i] = ls[lson];
		}
		while (top > 1) fa[sta[top]] = sta[top - 1], -- top;
		fa[sta[1]] = -1;
		printf("A ");
		for (int i = 1; i <= n; ++ i) printf("%d ", fa[i]);
		puts("");
		fflush(stdout);
	}
}