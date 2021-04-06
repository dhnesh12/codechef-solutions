#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main(){
	ll t;
	cin >> t;
	while (t--){
		ll N, k;
		cin >> N >> k;
		vector <ll> A(N);
		for (int i = 0; i < N; i ++)
			cin >> A[i];
		vector <ll> dp1(N, -2e9), dp2(N, -2e9);
		dp1[0] = max(dp1[0], A[0]);
		for (int i = 1; i < N; i ++)
			dp1[i] = max({dp1[i], A[i], A[i] + dp1[i - 1]});
		dp2[N - 1] = max(dp2[N - 1], A[N - 1]);
		for (int i = N - 2; i >= 0; i --)
			dp2[i] = max({dp2[i], A[i], A[i] + dp2[i + 1]});
		vector <ll> dpp1(N), dpp2(N);
		ll curr = -2e9;
		for (int i = 0; i < N; i ++){
			curr = max(curr, dp1[i]);
			dpp1[i] = curr;
		}
		curr = -2e9;
		for (int i = N - 1; i >= 0; i --){
			curr = max(curr, dp2[i]);
			dpp2[i] = curr;
		}
		// for (auto d : dpp1)
		// 	cout << d << ' ';
		// cout << '\n';
		// for (auto d : dpp2)
		// 	cout << d << ' ';
		// cout << '\n';
		ll res = -2e9;
		for (int i = k + 1; i < N; i ++)
			res = max(dpp2[i] + dpp1[i - k - 1], res);
		cout << res << '\n';
	}
}

// 1
// 8 3
// 5 5 -1 -2 3 -1 2 -2
