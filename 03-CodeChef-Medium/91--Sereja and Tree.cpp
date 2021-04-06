#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9+7;
int add(int a, int b) { return (a+b)%MOD; }
int mult(int a, int b) { return ((ll) a*b)%MOD; }
int inv(int x) {
	int p = MOD-2;
	int ans = 1;
	for (int i=0;i<30;i++) {
		if (p&(1<<i)) ans = mult(ans,x);
		x = mult(x,x);
	}
	return ans;
}

int N;
int C[88];
int fact[88];
int cnt[88];

int main() {
	ios::sync_with_stdio(false);

	fact[0] = 1;
	for (int i=1;i<88;i++) fact[i] = mult(i,fact[i-1]);

	cin >> N;
	for (int i=0;i<N;i++) cin >> C[i];
    sort(C,C+N);

    if (N==1 && C[0]==0) {
		cout << 1 << endl;
		return 0;
	}

    if (N==2 && C[0]==1 && C[1]==1) {
		cout << 2 << endl;
		return 0;
	}

    int sum = 0;
    for (int i=0;i<N;i++) sum+=C[i];
    if (C[0]==0 || sum!=2*N-2) {
		cout << 0 << endl;
		return 0;
	}

	int ways = fact[N-2];
	for (int i=0;i<N;i++) ways = mult(ways,inv(fact[C[i]-1]));
	int ans = 0;
	for (int i=0;i<N;i++) if (C[i]!=C[i+1]) {
		int cur = ways;
		cur = mult(cur,fact[C[i]]);
		for (int j=0;j<N;j++) if (j!=i) cur = mult(cur,fact[C[j]-1]);
		cur = mult(cur,fact[N]);
		for (int j=0;j<N;j++) cnt[j] = 0;
		for (int j=0;j<N;j++) if (j!=i) cnt[C[j]]+=1;
		for (int j=0;j<N;j++) cur = mult(cur,inv(fact[cnt[j]]));
		ans = add(ans,cur);
	}

	cout << ans << endl;
	
	return 0;
}
