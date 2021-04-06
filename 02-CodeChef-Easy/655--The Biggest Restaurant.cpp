#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int mod = 1e9+7;

//ll pref[300005],visited[300005],arr[300005];
ll n,x[200005],h[200005];

ll f1(ll a,ll b){
    return (a*(a-1))/2 - ((a-b)*(a-b-1))/2;
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--) {
	    cin>>n;
	    //ll ans = 0;
	    for(int i=0;i<n;i++) {
	        cin>>x[i]>>h[i];
	        //ans += arr[i];
	    }
	    sort(h,h+n);
	    vector<ll>x_arr;
	    x_arr.pb(x[1]-x[0]);
	    x_arr.pb(x[n-1]-x[n-2]);
	    for(int i=1;i<n-1;i++) {
	        x_arr.pb(x[i+1]-x[i-1]);
	    }
	    sort(x_arr.begin(),x_arr.end());
	    ll ans = 0;
	    for(int i=0;i<n;i++) {
	        ans += (x_arr[i]*h[i]);
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
