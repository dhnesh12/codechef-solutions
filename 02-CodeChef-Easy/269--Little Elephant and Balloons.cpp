// by xcwgf666
// initially was written for the version with N = 100

#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
using namespace std;

long double cost[100 + 5], ret, expected[100 + 5], prob, all_ways, t_ways, subsets[100 + 5], pb[100 + 5][100 + 5], pb2[100 + 5][100 + 5]; // prefix, last taken, different colors
int Tn, n, m, i, j, clr[100 + 5], amount[100 + 5], nonzero, cost_i;

long double get_wo (int idx, int am) {
	long double ret = 0;
	for(int left = 0; left <= am; left++) ret += pb[idx - 1][left] * pb2[idx + 1][am - left];
	return ret;
}

int main (int argc, char * const argv[]) {
	scanf("%d", &Tn);
	assert(1 <= Tn && Tn <= 40);
	for(; Tn; Tn--) {
		scanf("%d %d", &n, &m);
		assert(1 <= n && n <= 40);
		for(i = 1; i <= 100; i++) cost[i] = amount[i] = expected[i] = clr[i] = subsets[i] = 0;
		nonzero = ret = prob = all_ways = t_ways = 0;
		for(i = 1; i <= n; i++) {
			scanf("%d %d", &clr[i], &cost_i);
			assert(1 <= clr[i] && clr[i] <= 100);
			assert(1 <= cost_i && cost_i <= 1000000);
			nonzero += (!amount[clr[i]]);
			cost[clr[i]] += cost_i;
			++amount[clr[i]];
		}
		if (m == 0) { // degenerate case when every subset (even the empty one) is appropriate
			double sum = 0.0;
			// for a single item the expectation is 0.5 * item's cost 
			// and the answer is the sum of the expectations due to linearity of mathematical expectation
			for(i = 1; i <= 100; i++) sum += cost[i]; 
			printf("%.10lf\n", sum * 0.5);
			continue;
		}
		assert(1 <= m && m <= nonzero);
		// calculate the expectation for every single color
		// basically it is 2^(n-1) / 2^n-1 * sum of costs i.e. probability multiplyed by costs
		for(i = 1; i <= 100; i++) if (amount[i]) { 
			if (amount[i] < 50) {
				expected[i] = 1;
				for(j = 1; j < amount[i]; j++) expected[i] *= 2.0;
				expected[i] /= (expected[i] * 2.0 - 1.0);
			} else expected[i] = 1.0 / 2.0;
			expected[i] *= cost[i];
			subsets[i] = 1;
			for(j = 0; j < amount[i]; j++) subsets[i] *= 2;
			subsets[i] -= 1.0;
		}		
		for(i = 0; i <= 101; i++) for(j = 0; j <= 101; j++) pb[i][j] = pb2[i][j] = 0;		
		pb[0][0] = 1.0;
		for(i = 0; i < 100; i++) for(j = 0; j < 100; j++) {
			pb[i + 1][j] += pb[i][j];
			pb[i + 1][j + 1] += pb[i][j] * subsets[i + 1];
		}		
		pb2[101][0] = 1.0;
		for(i = 101; i >= 1; i--) for(j = 0; j < 100; j++) {
			pb2[i - 1][j] += pb2[i][j];
			pb2[i - 1][j + 1] += pb2[i][j] * subsets[i - 1];
		}				
		ret = 0.0;
		all_ways = 0;
		for(i = m; i <= nonzero; i++) all_ways += pb[100][i];
		for(i = m; i <= nonzero; i++) { // decide on the size of the subset
			// calculate the mathematical expectation for this subset size as the sum of expectations for the colors
			for(j = 1; j <= 100; j++) if (amount[j]) ret += (get_wo(j, i - 1) * subsets[j]) / all_ways * expected[j]; 
		}
		printf("%.10lf\n", (double)ret);
	}
    return 0;
}