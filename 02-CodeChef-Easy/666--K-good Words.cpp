#include <bits/stdc++.h>
using namespace std;

int main() {
	int t;
	cin>>t;
	while(t--) {
	    string w;
	    cin>>w;
	    int n = w.length();
	    int k;
	    cin>>k;
	    vector<int>dp(26,0);
	    for(int i=0;i<n;i++){
	        dp[w[i]-'a']++;
	    }
	    int ans = n;
	    for(int i=0;i<=n;i++) {
	        int temp = 0;
	        for(int j=0;j<26;j++) {
	            if(dp[j]>0) {
	                if(dp[j]<i) temp += dp[j];
	                else if(dp[j]>i+k) temp += (dp[j]-(i+k));
	            }
	        }
	        ans = min(ans,temp);
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
