#include <iostream>
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

#define mod 1000000007
#define maxn 100000

int n, k, a[maxn], i, helper[maxn];
double dp[maxn];
priority_queue<pair<double, int> > pq;

int main () {
    
	scanf("%d %d", &n, &k);
	assert(1 <= n && n <= 100000);
	assert(1 <= k && k <= n);
	for(i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		assert(1 <= a[i] && a[i] <= 100000);
	}
	dp[0] = log(a[0]);
    helper[0] = a[0];
	pq.push(make_pair(-dp[0], 0));
	for(i = 1; i < n; i++) {
		while (i - pq.top().second > k){ 
            pq.pop();
        }
		dp[i] = dp[pq.top().second] + log(a[i]);
        helper[i] = (helper[pq.top().second] * 1LL * a[i]) % mod;
		pq.push(make_pair(-dp[i], i));
	}
	printf("%d\n", helper[n - 1]);
    return 0;
}