#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cassert>

using namespace std;

const int kMaxn = 3e3 + 10, kMaxq = 1e5 + 10;
int ans[kMaxq], pos[kMaxn], tar[kMaxn];
long long b[kMaxn];
pair<int, int> a[kMaxn];
struct ques {
	int t, k, id;
} q[kMaxq];

int main() {
	double start = clock();
	int t;
	scanf("%d", &t);
	int n;
	for (; scanf("%d", &n) == 1; ) {
		assert(n <= 3000);
		for (int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].first, &a[i].second);
			//assert(a[i].first <= 20000 && a[i].second <= 1000000000);
		}
//		for (int i = 1; i <= n; ++i) {
//			for (int j = i + 1; j <= n; ++j) {
//				if (a[i].first != a[j].first) {
//					int dltv = a[j].first - a[i].first;
//					ts[++ts[0]] = (a[i].second - a[j].second + dltv - 1) / dltv;
//				}
//			}
//		}
//		sort(ts + 1, ts + ts[0] + 1);
//		ts[0] = unique(ts + 1, ts + ts[0] + 1) - (ts + 1);
		int Q;
		scanf("%d", &Q);
		assert(Q <= 100000);
		for (int i = 1; i <= Q; ++i) {
			scanf("%d%d", &q[i].t, &q[i].k);
			//assert(q[i].t <= 1000000000 && q[i].k <= n);
			q[i].id = i;
		}
		sort(q + 1, q + Q + 1,
			[](const ques &a, const ques &b) {
				return a.t < b.t;
			}
		);
		for (int i = 1; i <= n; ++i) {
			pos[i] = tar[i] = i;
		}
		sort(tar + 1, tar + n + 1,
			[&](const int x, const int y) {
				return a[x].first < a[y].first
					|| (a[x].first == a[y].first && x > y);
			}
		);
		int st = 1;
		for (int i = 1; i <= Q; ++i) {
			for (int j = st; j <= n; ++j) {
				b[j] = a[j].second + 1ll * a[j].first * q[i].t;
			}
			for (int j = st + 1; j <= n; ++j) {
				for (int k = j; k > st && (b[pos[k]] < b[pos[k - 1]]
						|| (b[pos[k]] == b[pos[k - 1]] && pos[k] > pos[k - 1])); --k) {
					swap(pos[k], pos[k - 1]);
				}
			}
			ans[q[i].id] = pos[n - q[i].k + 1];
			for (; st <= n && pos[st] == tar[st]; ++st) {}
		}
		for (int i = 1; i <= Q; ++i) {
			printf("%d\n", ans[i]);
		}
	}
	//printf("%.4fs\n", (clock() - start) / CLOCKS_PER_SEC);
	return 0;
}
