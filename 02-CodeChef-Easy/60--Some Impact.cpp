#include "bits/stdc++.h"
using namespace std;
signed main(){ios_base :: sync_with_stdio(false);cin.tie(0);cout.tie(0);int t;cin >> t;
	while(t--){int n,k,x0;long long m;cin>>n>>k>>m>>x0; if (k == 1){cout << (m == n ? "yes\n" : "no\n");}
		else if (k == 2){int cnt = __builtin_popcountll(m); if(cnt > n){cout << "no\n";}
			else{int z = 0;for(int j = 0; j <= 60; j++){if(m & 1LL << j){cnt--; if(j <= 1) n--, z = 0;
						else{int f = 1;for(; z > 0; --z){if (n - 1 - z >= cnt){f = 0;n -= 1 + z;break;}}
							n -= f;z = 1 - f;}}else if(j) ++z;}cout << (n == 0 ? "yes\n" : "no\n");}}
		else{bool ok = m % k <= 1; int S = 0;
			for(; m>0; m/=k){ok = ok && (m % k) <= 2;S += m % k;}cout << (S == n && ok ? "yes\n" : "no\n");}}}