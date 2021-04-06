#include <bits/stdc++.h>
using namespace std; 
typedef long long ll;
#define N 5005
const ll INF = -(1LL << 50);
int n,k,d,m;
int a[N];

ll dp1[N][N], dp2[N][N];
ll pref[N];
int main () {
	int t; scanf("%d", &t); 
	while(t--) {
		scanf("%d%d%d%d", &n,&k,&d,&m);
		
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]), pref[i] = pref[i - 1] + a[i];
		
		
		
		for(int i = 1; i <= n + 1; i++) for(int kk = 0; kk <= k; kk++) dp1[i][kk] = dp2[i][kk] = INF;
		for(int i = n; i>= 1; i--) dp2[i][0] = pref[n] - pref[i - 1];
		dp1[n + 1][0] = dp2[n + 1][0] = 0;
		
		for(int kk = 1; kk <= k; kk++) {
			deque<pair<ll,ll> > dq;
			for(int i = n; i >= 1; i--) {
				while(!dq.empty() && dq.front().second > i + d) {
					dq.pop_front();
				}
				
				
				dp1[i][kk] = dp2[i][kk] = INF;
				if (!dq.empty()) dp1[i][kk] = dq.front().first - m*pref[i];
				dp1[i][kk] = max(dp1[i][kk], dp2[min(i + d + 1, n + 1)][kk - 1] + pref[min(i + d + 1, n + 1) - 1]*m - pref[i ] * m);
				
				dp2[i][kk] = max(dp2[i + 1][kk] + a[i], dp1[i][kk]);
				
				while(!dq.empty() && dq.back().first <= dp1[i][kk - 1] + m*pref[i - 1])
					dq.pop_back();
				dq.push_back(make_pair(dp1[i][kk - 1] + m*pref[i - 1], i));
			}		
		}
		
		printf("%lld\n", dp2[1][k]);
	}
	return 0;
}