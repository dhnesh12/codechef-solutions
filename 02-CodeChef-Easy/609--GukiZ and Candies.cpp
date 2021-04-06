#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define pb push_back

const int mod = 1e9+7;

//ll pref[300005],visited[300005],arr[300005];
ll n,k,x,arr[200005];

ll f1(ll a,ll b){
    return (a*(a-1))/2 - ((a-b)*(a-b-1))/2;
}

int main() {
	// your code goes here
	int t;
	cin>>t;
	while(t--) {
	    cin>>n>>k>>x;
	    ll ans = 0;
	    for(int i=0;i<k;i++) {
	        cin>>arr[i];
	        ans += arr[i];
	    }
	    if(n==k) {
	        cout<<ans<<endl;
	        continue;
	    }
	    sort(arr,arr+k);
	    n-=k;
	    if(arr[k-1]!=arr[0]+x) {
	        k++;
	        arr[k-1] = arr[0]+x;
	        ans += arr[k-1];
	        n--;
	    }
	    for(int i = k-1;i>0;i--) {
	        ll diff = min(n,max(0LL,arr[i]-arr[i-1]-1));
	        ans += f1(arr[i],diff);
	        n-=diff;
	    }
	    cout<<ans<<endl;
	}
	return 0;
}
