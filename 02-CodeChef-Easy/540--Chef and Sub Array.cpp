/******************************************
*    AUTHOR:         BHUVNESH JAIN        *
*    INSTITUITION:   BITS PILANI, PILANI  *
******************************************/
#include <bits/stdc++.h>
using namespace std;
 
typedef long long LL; 
typedef long double LD;
typedef pair<int,int> pii;
typedef pair<LL, LL> pll;
 
const int MAX = 2e5 + 5;
 
char s[MAX];
int a[MAX*2];
int dp[MAX*2];
int seg[MAX*4];
 
int main() {
	#ifndef ONLINE_JUDGE
		freopen("inp.txt", "r", stdin);
	#endif
	int n, k, p;
	scanf("%d %d %d", &n, &k, &p);
	for(int i = 0; i < n; ++i) {
		scanf("%d", &a[i+n]);
		a[i] = a[i+n];
	}
	for(int i = 2*n-1; i>= 0; --i) {
		dp[i] = dp[i+1] + a[i] - a[i+k];
	}
	for(int i = 2*n; i < 4*n; ++i) {
		seg[i] = dp[i-2*n];
	}
	for(int i = 2*n-1; i >= 0; --i) {
		seg[i] = max(seg[i*2], seg[i*2+1]);
	}
	scanf("%s", s);
	int pos = n, res;
	for(int i = 0; i < p; ++i) {
		if (s[i] == '?') {
			if (k >= n) {
				res = dp[n];
			}
			else {
				int l = pos, r = min(2*n, pos+n-k+1);
				res = 0;
				for(l += 2*n, r += 2*n; l < r; l /= 2, r /= 2) {
					if (l&1) res = max(res, seg[l++]);
					if (r&1) res = max(res, seg[--r]);
				}
			}
			printf("%d\n", res);
		}
		else {
			pos -= 1;
			if (pos == 0) {
				pos = n;
			}
		}
	}
	return 0;
} 