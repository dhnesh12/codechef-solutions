#include<cstdio>
#define fo(i, x, y) for(int i = x; i <= y; i ++)
using namespace std;

int T, n, a[6], b[6], u, v, x, y, z;

void gg() {
	printf("?");
	fo(i, 0, 4) printf(" %d", a[i]);
	printf("\n");
	fflush(stdout);
	int b0 = -1; scanf("%d %d", &u, &v);
	fo(i, 0, 4) if(a[i] != u && a[i] != v) {
		b[++ b0] = a[i];
	}
	fo(i, 0, 2) a[i] = b[i];
}

int ye(int x) {
	return a[0] != x && a[1] != x && a[2] != x;
}

int t[3][2];

void pd(int k) {
	a[0] = x; a[1] = y; a[2] = z;
	a[3] = b[0]; a[4] = b[1];
	a[k] = b[2];
	printf("?");
	fo(i, 0, 4) printf(" %d", a[i]);
	printf("\n");
	fflush(stdout);
	int b0 = -1; scanf("%d %d", &u, &v);
	t[k][0] = u; t[k][1] = v;
}

int cnt(int *a, int *b) {
	return a[0] != b[0] || a[1] != b[1];
}

int main() {
	for(scanf("%d", &T); T; T --) {
		scanf("%d", &n);
		fo(i, 1, 3) a[i - 1] = i;
		for(int i = 4; i < n; i += 2) {
			a[3] = i; a[4] = i + 1;
			gg();
		}
		if(n % 2 == 0) {
			a[3] = n;
			fo(i, 1, n - 1) if(ye(i)) {
				a[4] = i; break;
			}
			gg();
		}
		int b0 = -1;
		fo(i, 1, n) if(ye(i)) {
			b[++ b0] = i;
			if(b0 == 2) break;
		}
		x = a[0]; y = a[1]; z = a[2];
		pd(0); pd(1); pd(2);
		fo(i, 0, 2) {
			int s = 0;
			fo(j, 0, 2) if(i != j)
				s += cnt(t[i], t[j]);
			if(s == 2) {
				printf("! %d\n", i == 0 ? x : (i == 1 ? y : z));
				fflush(stdout);
				continue;
			}
		}
	}
}