#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define ar array

const int M=1e9+7;
ll dp[1000001][11], dp2[1000001];

ll solve(bool r) {
	string s;
	cin >> s;
	ll ans=0;
	//count #digits < s
	for(int i=1; i<s.size(); ++i) {
		ans+=dp2[i];
		//cout << dp2[i] << endl;
	}
	//cout << ans << endl;
	int cm=0;
	for(int i=0; i<s.size(); ++i) {
		for(int j=!i; j<s[i]-'0'; ++j) {
			ans+=dp[s.size()-i-1][__builtin_popcount(cm^1<<j)];
			//for(int k=0; k<10; ++k)
				//ans+=dp[s.size()-i-1][__builtin_popcount(cm^1<<j^1<<k)];
		}
		//cout << i << " " << ans << endl;
		cm^=1<<(s[i]-'0');
	}
	//cout << ans << endl;
	//see if s works
	if(r&&__builtin_popcount(cm)<2)
		++ans;
	return ans%M;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	dp[0][0]=dp[0][1]=1;
	//dp[0][0]=1;
	for(int i=1; i<=1e6; ++i) {
		for(int j=0; j<=10; ++j) {
			//use single
			if(j)
				dp[i][j]+=dp[i-1][j-1]*j%M;
			if(j<10)
				dp[i][j]+=dp[i-1][j+1]*(10-j)%M;
			//use pair
			//if(i>1)
				//dp[i][j]+=dp[i-2][j]*(10-j)*(i-1)%M;
			dp[i][j]%=M;
			//if(i==1)
				//cout << dp[i][j] << endl;
		}
		//dp2[i]=9*dp[i-1][1]%M;
		for(int j=1; j<10; ++j) {
			dp2[i]=(dp2[i]+dp[i-1][1])%M;
			//for(int k=0; k<10; ++k)
				//dp2[i]=(dp2[i]+dp[i-1][__builtin_popcount(1<<j^1<<k)])%M;
		}
	}
	//cout << dp[2][1] << endl;

	int t;
	cin >> t;
	while(t--) {
		ll al=solve(0);
		ll ar=solve(1);
		cout << (ar+M-al)%M << "\n";
	}
}
