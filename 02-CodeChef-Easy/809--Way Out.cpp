#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--) {
	    ll n,h;
	    cin>>n>>h;
	    vector<ll>arr(n+3,0);
	    int l,r;
	    for(int i=0;i<n;i++) {
	        cin>>l>>r;
	        arr[l+1]++;
	        arr[r+2]--;
	    }
	    for(int i=1;i<=n;i++) arr[i] += arr[i-1];
	    for(int i=1;i<=n;i++) {
	        arr[i] = n-arr[i];
	        arr[i] += arr[i-1];
	    }
	    ll ans = 1e16;
	    for(int i=1;i<=(n-h+1);i++) {
	        ans = min(ans,arr[i+h-1]-arr[i-1]);
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
