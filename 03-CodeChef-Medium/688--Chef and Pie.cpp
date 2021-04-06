#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int mod = 1e9+7;

//ll pref[300005],visited[300005],arr[300005];

ll dp[5000005][2],arr[2001],n;
int sz = 1;

void insert(ll x){
    int pos = 0;
    for(int i=30;i>=0;i--) {
        if(!dp[pos][x>>i & 1]) {
            dp[pos][x>>i & 1] = sz++;
        }
        pos = dp[pos][x>>i & 1];
    }
}

ll query(ll x) {
    int pos = 0;
    ll ans = 0;
    for(int i=30;i>=0;i--) {
        int bt = x>>i & 1;
        if(dp[pos][!bt]) {
            pos = dp[pos][!bt];
            ans |= (1<<i);
        }
        else {
            //ans |= (1<<i);
            pos = dp[pos][bt];
        }
    }
    return ans;
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--) {
	    cin>>n;
	    memset(dp,0,sizeof(dp));
	    sz = 1;
	    //ll ans = 0;
	    //map<ll,ll>cnt;
	    for(int i=0;i<n;i++) {
	        cin>>arr[i];
	        //cnt[arr[i]]++;
	        
	    }
	    ll ans = 0;
	    for(int i=1;i<n;i++){
	        insert(arr[i-1]);
	        for(int j=i+1;j<n;j++) {
	            ll temp = arr[i]^arr[j];
	            ll x = query(temp);
	            //bool 
	            ans = max(ans,x);
	        }
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
