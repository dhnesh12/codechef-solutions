#include <bits/stdc++.h>
using namespace std;

long long int dp[1002];

// int util(int a[], int n, int m){
// 	// cout<<n<<" "<<a[n- 1]<<" "<<m<<" \n";
// 	if(m== 0){
// 		return 0;
// 	}
// 	// if(n== 0){
// 	// 	return INT_MAX;
// 	// }
// 	if(dp[m]!= -1){
// 		return dp[m];
// 	}
// 	int i, ans= INT_MAX;
// 	for(i= 0; i< n; i++){
// 		if(a[i]<= m){
// 			ans= min(ans, 1+ util(a, n, m- a[i]));
// 		}
// 	}
// 	return dp[m]= ans;
// }

int main(){
	int t;
	cin>>t;
	while(t--){
		memset(dp, -1, sizeof(dp));
		int n;
		cin>>n;
		int i, a[n], v[n], mx= 0;
		for(i= 0; i< n; i++){
			cin>>a[i];
			mx= max(mx, a[i]);
		}
		long long int s= 0, j;
		for(i= 0; i< n; i++){
			cin>>v[i];
		}
		for(i= 0; i<= 2*mx; i++){
			dp[i]= INT_MAX;
		}
		dp[0]= 0;
		for(i= 0; i< n; i++){
			for(j= v[i]; j<= 2*mx; j++){
				dp[j]= min(dp[j], 1+ dp[j- v[i]]);
			}
			// cout<<endl;
		}
		for(i= 0; i< n; i++){
			s+= dp[2*a[i]];
			// cout<<dp[2*a[i]]<<" ";
		}
		cout<<s<<endl;
	}
}