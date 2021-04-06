#include "bits/stdc++.h"
using namespace std;
const int N = 5e3 + 3;
int t;
int n , q;
int a , b;
vector < int > v[N];
int arr[N];
int subtree[N];
void dfs1(int node , int parent){
	subtree[node] = 1;
	for(int next : v[node]){
		if(next != parent){
			dfs1(next , node);
			subtree[node] += subtree[next];
		}
	}
}
int ans[N];
int dp[N][N];
void dfs2(int node , int parent){
	dp[node][0] = 0;
	dp[node][1] = arr[node];
	int mx = subtree[node];
	for(int i = 2 ; i <= mx ; ++i){
		dp[node][i] = 0;
	}
	mx = 1;
	for(int next : v[node]){
		if(next == parent){
			continue;
		}
		dfs2(next , node);
		int mn = subtree[next];
		for(int j = mx ; j >= 1 ; --j){
			for(int k = 1 ; k <= mn ; ++k){
				dp[node][j + k] = max(dp[node][j + k] , dp[node][j] + dp[next][k]);
			}
		}
		mx += mn;
	}
}
bool cmp(int a, int b){
	return subtree[a] < subtree[b];
}
void solve(){
	dfs2(1 , 0);
	for(int i = 1 ; i <= n ; ++i){
		ans[i] = 0;
	}
	for(int i = 1 ; i <= n ; ++i){
		int mx = subtree[i];
		for(int j = 1 ; j <= mx ; ++j){
			ans[j] = max(ans[j] , dp[i][j]);
		}
	}
}
int ql[N];
int qr[N];
int main(){
	scanf("%d" , &t);
	while(t--){
		scanf("%d %d" , &n , &q);
		for(int i = 1 ; i <= n ; ++i){
			v[i].clear();
		}
		for(int i = 1 ; i < n ; ++i){
			scanf("%d %d" , &a , &b);
			v[a].emplace_back(b);
			v[b].emplace_back(a);
		}
		for(int i = 1 ; i <= n ; ++i){
			scanf("%d" , arr + i);
		}
		dfs1(1 , 0);
		for(int x = 1; x<=n; x++){
			sort(v[x].begin(), v[x].end(), cmp);
		}
		solve();
		for(int i = 1 ; i <= n ; ++i){
			qr[i] = ans[i];
			arr[i] ^= 1;
		}
		solve();
		for(int i = 1 ; i <= n ; ++i){
			ql[i] = i - ans[i];
		}
		while(q--){
			scanf("%d %d" , &a , &b);
			if(b >= ql[a] && b <= qr[a]){
				printf("Yes\n");
			}
			else{
				printf("No\n");
			}
		}
	}	
}