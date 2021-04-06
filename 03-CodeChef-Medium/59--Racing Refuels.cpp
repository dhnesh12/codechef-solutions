#include<cstdio>
#include<algorithm>
#define N_ 301000
using namespace std;
int n, Q;
long long w[N_], S[N_], K, P;
__int128 res;
bool Over(int mid) {
	long long a = S[mid] + P, b = S[mid + 1] + P;
	if (a / mid != b / (mid + 1)) {
		return a / mid < b / (mid + 1);
	}
	a %= mid, b %= mid + 1;
	return a*(mid + 1) <= b*mid;
}
void UDT2(int r, long long c1, long long c2) {
	if (r*c1 + (r + 1)*c2 != K)return;
	if (c1 < 0 || c2 < 0)return;
	if (c2 && r + 1 > n)return;
	if (c1 && r < 1)return;
	res = min(res, (__int128)(S[r] + P)*c1 + (__int128)(S[r + 1] + P)*c2 - P);
}
void UDT(int r) {
	if (r<1 || r>n)return;
	int t = K%r;
	UDT2(r, K / r - t, t);
	t = K % (r + 1);
	if (t == 0) {
		UDT2(r, 0, K / (r + 1));
	}
	else {
		int c = r + 1 - t;
		UDT2(r, c, K / (r + 1) + 1 - c);
	}
}
void Solve() {
	long long b = 1, e = n - 1, r = n, mid;
	while (b <= e) {
		mid = (b + e) >> 1;
		if (Over(mid)) {
			r = mid;
			e = mid - 1;
		}
		else b = mid + 1;
	}
	res = 1;
	res <<= 120;
	UDT(r - 1);
	UDT(r);
	long long t = K / r;
	for (long long i = t - 5; i <= t + 5; i++) {
		if (i <= 0 || i>K)continue;
		UDT(K / i);
	}
	printf("%lld\n", (long long)res);
}
int main() {
	int i;
	scanf("%d%d", &n, &Q);
	for (i = 1; i <= n; i++) {
		scanf("%lld", &w[i]);
		S[i] = S[i - 1] + w[i];
	}
	while (Q--) {
		scanf("%lld%lld", &K, &P);
		Solve();
	}
}