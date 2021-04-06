#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
 
#define x first
#define y second
 
typedef pair<double, double> point;
int n, m;
vector<point> nails, rubber;
 
int x_sorted[10000], x_order[10000];
bool comp_x(int i, int j) {
	double i_x = (i > n ? rubber[i - n].x : nails[i].x);
	double j_x = (j > n ? rubber[j - n].x : nails[j].x);
	return i_x < j_x;
}
 
double ccw(point &p, point &q, point &r) {
	return (q.x - p.x) * (r.y - p.y) - (q.y - p.y) * (r.x - p.x);
}
 
int stac[3000000], tp = 0;
 
int main() {
	int T;
	scanf("%d", &T);
	while (T--) {
		scanf("%d", &n);
		nails.resize(n + 1);
		for (int i = 1; i <= n; i++)
			scanf("%lf %lf", &nails[i].x, &nails[i].y);
 
		scanf("%d", &m);
		rubber.resize(m + 1);
		for (int i = 1; i <= m; i++)
			scanf("%lf %lf", &rubber[i].x, &rubber[i].y);
 
		// sort nails and rubber verticies
		for (int i = 1; i <= n + m; i++)
			x_sorted[i] = i;
		sort(x_sorted + 1, x_sorted + n + m + 1, comp_x);
		for (int i = 1; i <= n + m; i++)
			x_order[x_sorted[i]] = i;
 
		// we fix the x-order of nails and rubbers as above for consistency
 
		// compute the fundamental group element
		vector<int> word;
		for (int i = 1; i <= m; i++) {
			point &st = rubber[i], &ed = (i == m ? rubber[1] : rubber[i + 1]);
			int st_index = n + i, ed_index = n + (i == m ? 1 : i + 1);
			if (x_order[st_index] < x_order[ed_index]) {
				for (int j = x_order[st_index] + 1;
						j <= x_order[ed_index] - 1;
						j++) {
					if (x_sorted[j] <= n && ccw(st, ed, nails[x_sorted[j]]) > 0.0) {
						word.push_back(x_sorted[j]);
					}
				}
			} else {
				for (int j = x_order[st_index] - 1;
						j >= x_order[ed_index] + 1;
						j--) {
					if (x_sorted[j] <= n && ccw(ed, st, nails[x_sorted[j]]) > 0.0) {
						word.push_back(-x_sorted[j]);
					}
				}
			}
		}
 
		tp = 0;
		for (int v : word) {
			if (tp > 0 && stac[tp - 1] + v == 0)
				tp--;
			else
				stac[tp++] = v;
			// printf("%d\n", tp);
		}
 
		if (tp == 0)
			printf("YES\n");
		else
			printf("NO\n");
	}
 
	return 0;
}