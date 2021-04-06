#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5005;
long long dp[2][N], Or[N][N];

void compute(int id, int l, int r, int optl, int optr) {
    if(l > r) return;
    int mid = (l + r) >> 1;
    int opt = optl;
    long long best = -1e9;
    for(int k = optl; k <= min(optr, mid); k++) {
    	if(dp[id ^ 1][k - 1] + Or[k][mid] >= best) {
    		best = dp[id ^ 1][k - 1] + Or[k][mid];
    		opt = k;
    	}
    }
    dp[id][mid] = best;
    compute(id, l, mid - 1, optl, opt);
    compute(id, mid + 1, r, opt, optr);
}

int solve(long long a[], int n, int k) { 
	for(int i = 1; i <= n; i++) {
		Or[i][i] = a[i];
		for(int j = i + 1; j <= n; j++) 
			Or[i][j] = Or[i][j - 1] | a[j];
	}
	dp[0][0] = 0; dp[1][0] = 0;
	for(int i = 1; i <= n; i++)
		dp[0][i] = Or[1][i];
	int id = 1;
	for(int i = 2; i <= k; i++) {
		compute(id, 1, n, 1, n);
		id ^= 1;
	}
	cout << dp[id ^ 1][n] << endl;
}

void testCase() {
	int n, k;
	cin >> n >> k;
	long long a[n + 1];
	for(int i = 1; i <= n; i++)
		cin >> a[i];
	solve(a, n, k);
}

int main()
{
	#ifdef NST
	clock_t tStart = clock();         
	freopen("/IO/input.txt", "r", stdin);         
	freopen("/IO/output.txt", "w", stdout);     
	#endif

	int t = 1;
	cin >> t;
	while(t--) {
		testCase();
	}
	
	#ifdef NST        
	fprintf(stderr, "\n>> Runtime: %.10fs\n", (double) (clock() - tStart) / CLOCKS_PER_SEC);     
	#endif
}