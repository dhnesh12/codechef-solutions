#include <bits/stdc++.h>
#define MAXN 2097152
#define pi acos(-1)
using namespace std;
typedef long long ll;
typedef long double ld;

int n;
ll a[100005];
ll lsum = 0, rsum = 0, sum = 0;
int rl[100005], rr[100005], m;
int dl[100005], dr[100005]; ll ans = 0;

void dfs(int x, int N){
	int l = rand() % (n / 2) + 1;
	int r = rand() % (n / 2) + (n / 2) + 1;
	if(r - l + 1 > N) return;
	for(int i = l; i < r; i ++) swap(a[i], a[i + 1]);
	dl[x] = l; dr[x] = r;
	lsum = rsum = sum = 0;
	for(int i = 1; i <= n / 2; i ++) lsum += a[i];
	for(int i = n / 2 + 1; i <= n; i ++) rsum += a[i];
	sum = lsum - rsum; if(sum < 0) sum = -sum;
	if(sum < ans){
		m = x; ans = sum;
		for(int i = 1; i <= x; i ++) rl[i] = dl[i], rr[i] = dr[i];
	}
	dfs(x + 1, N - (r - l + 1));
	for(int i = r - 1; i >= l; i --) swap(a[i], a[i + 1]);
}

int main(){
	scanf("%d", &n); srand(114514);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n / 2; i ++) lsum += a[i];
	for(int i = n / 2 + 1; i <= n; i ++) rsum += a[i];
	sum = lsum - rsum; if(sum < 0) sum = -sum; ans = sum;
	for(int i = 1; i <= 1000; i ++) dfs(1, n * 2);
	
	printf("%d\n", m);
	for(int i = 1; i <= m; i ++) printf("%d %d\n", rl[i], rr[i]);
	return 0;
}