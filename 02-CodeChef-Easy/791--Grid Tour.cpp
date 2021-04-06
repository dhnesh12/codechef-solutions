#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

#define F first
#define S second

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	int te;	cin >> te;
	while (te--){
		int n, m, k; cin >> n >> m >> k;
		if (__gcd(n, k) > 1 || __gcd(m, k) > 1)
			cout << "-1\n";
		else
			cout << 1ll*n*m << "\n";
	}
	return 0;
}