#include <cstdio>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;
const int MAX_N = 1e6 + 1;
struct _d { int a, b; };
bool operator<(const _d& a, const _d& b) {
	if (a.a == b.a) return a.b < b.b;
	if (a.b == b.b) return a.a < b.a;
	return a.a * a.b < b.a * b.b;
}
int main() {
	int K, N, i, A[MAX_N], B[MAX_N], l, r, cA = 1, cB = 1;
	map<_d, int> m;
	scanf("%d%d", &N, &K);
	A[N] = B[N] = 1;
	for (i = 0; i < N; i++)
		scanf("%d%d", &A[i], &B[i]);
	for (i = 0; i < K; i++)
		m[_d{A[i], B[i]}]++;
	l = 0, r = K;
	while (r <= N) {
		A[r] = max(A[r], m.begin()->first.a);
		B[r] = max(B[r], m.begin()->first.b);
		
		auto t = m.find(_d{ A[l], B[l] });
		t->second--;
		if (!t->second) m.erase(t);

		m[_d{ A[r], B[r] }]++;
		l++, r++;
	}
	printf("%d", A[N] * B[N]);
	return 0;
}